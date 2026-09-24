/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_GLOBAL_PRIVACY_CONTROL_PREF_NAMES_H_
#define BRAVE_COMPONENTS_GLOBAL_PRIVACY_CONTROL_PREF_NAMES_H_

namespace global_privacy_control {

// Kiryra-owned preference name. Adapted from the upstream Brave primitive
// ("brave.global_privacy_control_enabled") per Kiryra integration policy:
// Kiryra owns the resulting privacy settings model rather than exposing
// Brave's product/pref namespace (browser-spec 05).
inline constexpr char kGlobalPrivacyControlEnabled[] =
    "kiryra.privacy.global_privacy_control_enabled";

}  // namespace global_privacy_control

#endif  // BRAVE_COMPONENTS_GLOBAL_PRIVACY_CONTROL_PREF_NAMES_H_
