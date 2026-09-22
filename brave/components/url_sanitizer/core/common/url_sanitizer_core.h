/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core's URLSanitizerService at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 * Brave component-updater, Mojo, and product-service plumbing are intentionally
 * excluded. This file contains only the reusable URL matcher/sanitizer logic.
 */

#ifndef KITECH_COMMUNITY_URL_SANITIZER_CORE_H_
#define KITECH_COMMUNITY_URL_SANITIZER_CORE_H_

#include <string>
#include <string_view>
#include <vector>

#include "base/containers/flat_set.h"
#include "base/types/expected.h"
#include "extensions/common/url_pattern_set.h"
#include "url/gurl.h"

namespace community_url_sanitizer {

struct MatchItem {
  MatchItem();
  MatchItem(extensions::URLPatternSet include_patterns,
            extensions::URLPatternSet exclude_patterns,
            base::flat_set<std::string> blocked_params);
  MatchItem(MatchItem&&);
  MatchItem& operator=(MatchItem&&);
  ~MatchItem();

  extensions::URLPatternSet include;
  extensions::URLPatternSet exclude;
  base::flat_set<std::string> params;
};

base::expected<std::vector<MatchItem>, std::string> ParseMatchers(
    std::string_view json);

std::string StripQueryParameter(
    std::string_view query,
    const base::flat_set<std::string>& blocked_params);

GURL SanitizeURL(const GURL& initial_url,
                 const std::vector<MatchItem>& matchers);

}  // namespace community_url_sanitizer

#endif  // KITECH_COMMUNITY_URL_SANITIZER_CORE_H_
