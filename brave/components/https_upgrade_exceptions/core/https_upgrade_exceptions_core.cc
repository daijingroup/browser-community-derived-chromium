/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core HttpsUpgradeExceptionsService at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 */

#include "brave/components/https_upgrade_exceptions/core/https_upgrade_exceptions_core.h"

#include <utility>
#include <vector>

#include "base/strings/string_split.h"

namespace community_https_upgrade {

Exceptions::Exceptions() = default;
Exceptions::~Exceptions() = default;

void Exceptions::LoadFromText(std::string_view contents) {
  exceptional_domains_.clear();

  const std::vector<std::string> lines =
      base::SplitString(contents, "\n", base::TRIM_WHITESPACE,
                        base::SPLIT_WANT_NONEMPTY);

  for (const auto& line : lines) {
    exceptional_domains_.insert(line);
  }
  ready_ = true;
}

bool Exceptions::IsExceptionHost(std::string_view host) const {
  return exceptional_domains_.contains(host);
}

bool Exceptions::CanUpgradeToHTTPS(const GURL& url) const {
  if (!url.is_valid() || !url.SchemeIsHTTPOrHTTPS()) {
    return false;
  }

  // Preserve Brave's fail-safe behavior: until the authenticated exception
  // list has been loaded, do not force an HTTPS upgrade.
  if (!ready_) {
    return false;
  }

  return !IsExceptionHost(url.host());
}

}  // namespace community_https_upgrade
