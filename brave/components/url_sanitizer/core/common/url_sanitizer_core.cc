/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core's URLSanitizerService at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 */

#include "brave/components/url_sanitizer/core/common/url_sanitizer_core.h"

#include <optional>
#include <utility>

#include "base/json/json_reader.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "base/values.h"
#include "extensions/common/url_pattern.h"

namespace community_url_sanitizer {
namespace {

std::optional<extensions::URLPatternSet> CreateURLPatternSetFromList(
    const base::ListValue* value) {
  if (!value) {
    return std::nullopt;
  }

  extensions::URLPatternSet result;
  std::string error;
  if (!result.Populate(*value,
                       URLPattern::SCHEME_HTTP | URLPattern::SCHEME_HTTPS,
                       false, &error)) {
    return std::nullopt;
  }
  return result;
}

std::optional<base::flat_set<std::string>> CreateParamsList(
    const base::ListValue* value) {
  if (!value) {
    return std::nullopt;
  }

  base::flat_set<std::string> result;
  for (const auto& param : *value) {
    if (!param.is_string()) {
      return std::nullopt;
    }
    result.insert(param.GetString());
  }
  return result;
}

}  // namespace

MatchItem::MatchItem() = default;
MatchItem::MatchItem(extensions::URLPatternSet include_patterns,
                     extensions::URLPatternSet exclude_patterns,
                     base::flat_set<std::string> blocked_params)
    : include(std::move(include_patterns)),
      exclude(std::move(exclude_patterns)),
      params(std::move(blocked_params)) {}
MatchItem::MatchItem(MatchItem&&) = default;
MatchItem& MatchItem::operator=(MatchItem&&) = default;
MatchItem::~MatchItem() = default;

base::expected<std::vector<MatchItem>, std::string> ParseMatchers(
    std::string_view json) {
  auto parsed = base::JSONReader::ReadAndReturnValueWithError(
      json, base::JSON_PARSE_CHROMIUM_EXTENSIONS);
  if (!parsed.has_value()) {
    return base::unexpected(parsed.error().message);
  }

  const base::ListValue* list = parsed->GetIfList();
  if (!list) {
    return base::unexpected("URL sanitizer matcher root must be a list");
  }

  std::vector<MatchItem> matchers;
  matchers.reserve(list->size());

  for (const auto& item : *list) {
    const base::DictValue* dict = item.GetIfDict();
    if (!dict) {
      continue;
    }

    auto include = CreateURLPatternSetFromList(dict->FindList("include"));
    auto params = CreateParamsList(dict->FindList("params"));
    if (!include || !params) {
      continue;
    }

    auto exclude =
        CreateURLPatternSetFromList(dict->FindList("exclude"))
            .value_or(extensions::URLPatternSet());

    matchers.emplace_back(std::move(*include), std::move(exclude),
                          std::move(*params));
  }

  return matchers;
}

std::string StripQueryParameter(
    std::string_view query,
    const base::flat_set<std::string>& blocked_params) {
  const std::vector<std::string_view> input =
      base::SplitStringPiece(query, "&", base::KEEP_WHITESPACE,
                             base::SPLIT_WANT_ALL);
  std::vector<std::string> output;
  bool stripped = false;

  for (const std::string_view kv : input) {
    const std::vector<std::string_view> pieces =
        base::SplitStringPiece(kv, "=", base::KEEP_WHITESPACE,
                               base::SPLIT_WANT_NONEMPTY);
    const std::string_view key =
        pieces.empty() ? std::string_view() : pieces[0];

    if (pieces.size() >= 2 && blocked_params.contains(std::string(key))) {
      stripped = true;
      continue;
    }
    output.emplace_back(kv);
  }

  return stripped ? base::JoinString(output, "&") : std::string(query);
}

GURL SanitizeURL(const GURL& initial_url,
                 const std::vector<MatchItem>& matchers) {
  if (!initial_url.SchemeIsHTTPOrHTTPS()) {
    return initial_url;
  }

  GURL url = initial_url;
  for (const auto& matcher : matchers) {
    if (!matcher.include.MatchesURL(url) || matcher.exclude.MatchesURL(url)) {
      continue;
    }

    const std::string sanitized_query =
        StripQueryParameter(url.query(), matcher.params);

    GURL::Replacements replacements;
    if (sanitized_query.empty()) {
      replacements.ClearQuery();
    } else {
      replacements.SetQueryStr(sanitized_query);
    }
    url = url.ReplaceComponents(replacements);
  }

  return url;
}

}  // namespace community_url_sanitizer
