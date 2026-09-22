/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * Modifications Copyright (c) 2026 KiTech Software.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Derived from Brave Core HttpsUpgradeExceptionsService at
 * brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35.
 */

#ifndef KITECH_COMMUNITY_HTTPS_UPGRADE_EXCEPTIONS_CORE_H_
#define KITECH_COMMUNITY_HTTPS_UPGRADE_EXCEPTIONS_CORE_H_

#include <set>
#include <string>
#include <string_view>

#include "url/gurl.h"

namespace community_https_upgrade {

class Exceptions {
 public:
  Exceptions();
  ~Exceptions();

  void LoadFromText(std::string_view contents);
  bool ready() const { return ready_; }
  bool IsExceptionHost(std::string_view host) const;
  bool CanUpgradeToHTTPS(const GURL& url) const;

 private:
  std::set<std::string, std::less<>> exceptional_domains_;
  bool ready_ = false;
};

}  // namespace community_https_upgrade

#endif  // KITECH_COMMUNITY_HTTPS_UPGRADE_EXCEPTIONS_CORE_H_
