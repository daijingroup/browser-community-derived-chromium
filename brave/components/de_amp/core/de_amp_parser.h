/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core de_amp_util at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 * Brave preferences, feature flags, body sniffer, and browser interception
 * plumbing are intentionally excluded.
 */

#ifndef KITECH_COMMUNITY_DE_AMP_PARSER_H_
#define KITECH_COMMUNITY_DE_AMP_PARSER_H_

#include <string>
#include <string_view>

#include "base/types/expected.h"
#include "url/gurl.h"

namespace community_de_amp {

bool CheckIfAmpPage(std::string_view body);

base::expected<std::string, std::string> FindCanonicalAmpUrl(
    std::string_view body);

bool VerifyCanonicalAmpUrl(const GURL& canonical_url,
                           const GURL& original_url);

}  // namespace community_de_amp

#endif  // KITECH_COMMUNITY_DE_AMP_PARSER_H_
