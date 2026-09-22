/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core de_amp_util at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 */

#include "brave/components/de_amp/core/de_amp_parser.h"

#include <utility>

#include "base/no_destructor.h"
#include "third_party/re2/src/re2/re2.h"

namespace community_de_amp {
namespace {

constexpr char kGetHtmlTagPattern[] = "(<\\s*?html\\s.*?>)";
constexpr char kDetectAmpPattern[] =
    "(?:<.*?\\s.*?(amp|⚡|⚡=\"(?:true|\\s*)\"|⚡=\\'(?:true|\\s*)\\'|amp=\"(?:"
    "true|\\s*)\"|amp='(?:true|\\s*)')(?:\\s.*?>|>|/>))";
constexpr char kFindCanonicalLinkTagPattern[] =
    "(<\\s*?link\\s[^>]*?rel=(?:\"|')?canonical(?:\"|')?(?:\\s[^>]*?>|>|/>))";
constexpr char kFindCanonicalHrefInTagPattern[] =
    "href=(?:\"|')?(.*?)(?:\"|')?(?:\\s[^>]*?>|>|/>)";

RE2::Options InitRegexOptions() {
  RE2::Options options;
  options.set_case_sensitive(false);
  options.set_dot_nl(true);
  return options;
}

}  // namespace

bool CheckIfAmpPage(std::string_view body) {
  auto options = InitRegexOptions();
  static const base::NoDestructor<re2::RE2> html_regex(kGetHtmlTagPattern,
                                                       options);
  static const base::NoDestructor<re2::RE2> amp_regex(kDetectAmpPattern,
                                                      options);

  std::string html_tag;
  return RE2::PartialMatch(body, *html_regex, &html_tag) &&
         RE2::PartialMatch(html_tag, *amp_regex);
}

base::expected<std::string, std::string> FindCanonicalAmpUrl(
    std::string_view body) {
  auto options = InitRegexOptions();
  static const base::NoDestructor<re2::RE2> link_regex(
      kFindCanonicalLinkTagPattern, options);
  static const base::NoDestructor<re2::RE2> href_regex(
      kFindCanonicalHrefInTagPattern, options);

  std::string link_tag;
  if (!RE2::PartialMatch(body, *link_regex, &link_tag)) {
    return base::unexpected("Couldn't find canonical link tag");
  }

  std::string canonical_url;
  if (!RE2::PartialMatch(link_tag, *href_regex, &canonical_url)) {
    return base::unexpected("Couldn't find canonical URL");
  }

  return base::ok(std::move(canonical_url));
}

bool VerifyCanonicalAmpUrl(const GURL& canonical_url,
                           const GURL& original_url) {
  return canonical_url.is_valid() && canonical_url.SchemeIsHTTPOrHTTPS() &&
         canonical_url != original_url;
}

}  // namespace community_de_amp
