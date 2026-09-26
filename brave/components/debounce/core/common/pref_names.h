// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Kiryra: pref name re-namespaced from brave.debounce.enabled to
// kiryra.privacy.debounce_enabled for consistency with our own pref namespace.

#ifndef BRAVE_COMPONENTS_DEBOUNCE_CORE_COMMON_PREF_NAMES_H_
#define BRAVE_COMPONENTS_DEBOUNCE_CORE_COMMON_PREF_NAMES_H_

namespace debounce::prefs {

// Is debounce feature currently enabled
inline constexpr char kDebounceEnabled[] = "kiryra.privacy.debounce_enabled";

}  // namespace debounce::prefs

#endif  // BRAVE_COMPONENTS_DEBOUNCE_CORE_COMMON_PREF_NAMES_H_
