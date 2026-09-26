# Brave M153 Harvest Status

Source pin: `brave/brave-core@973c5c8667ce80d2d3c227ef6e60df530eb26d35`  
Brave version: `1.97.37`  
Brave Chromium baseline: `153.0.8010.37`  
Kiryra Chromium baseline: `153.0.8010.52`

## Complete

The initial Brave privacy/security harvesting phase is complete.

### Reused

| Capability | Result |
|---|---|
| Bounce/debounce | Common definitions plus reusable rule parser/application engine |
| Query filtering | Rule schema, rule storage, matcher and query-filter core |
| URL sanitization | MPL-covered standalone adaptation of matcher/query stripping |
| Global Privacy Control | Small GPC preference/enablement primitive |
| HTTPS upgrade exceptions | MPL-covered standalone exception parser/decision core |
| De-AMP | MPL-covered AMP detection and canonical-URL parser |
| Ad/tracker filtering | Brave Rust/C++ adblock bridge plus domain resolver; upstream `adblock` crate pinned separately |
| Fingerprinting | Deterministic farbling PRNG primitive only |

### Deliberately not imported

These are too coupled to Brave product architecture and will be implemented by Kiryra:

- Shields UI, settings, site panel and orchestration;
- Shields-aware navigation/service factories;
- component updater and remote component lifecycle;
- P3A and Brave telemetry;
- full farbling/fingerprinting policy and Blink/browser integration;
- ephemeral-storage service tied to Shields settings;
- Brave-specific GPC network delegate integration;
- Brave webcompat/reporting services;
- Brave account/product/service functionality.

## Integration state

Harvested code is not equivalent to production enablement. Each component still requires Kiryra-owned integration, exact Chromium `153.0.8010.52` build validation, tests, rule/update-source decisions where applicable, and privacy-policy wiring.

### Integrated

| Capability | Kiryra wiring |
|---|---|
| Global Privacy Control | `browser-kitech-derived-chromium` `patches/0006-kiryra-integrate-global-privacy-control.patch`: renamed pref to Kiryra namespace, registered as a Kiryra profile pref (default enabled, inspectable at `chrome://prefs-internals`), and a `URLLoaderThrottle` sends `Sec-GPC: 1` per the harvested primitive's decision. Not yet wired to a Kiryra-owned enterprise policy or user-facing settings toggle; both are deferred to the phase 06 browser-experience/settings work. |
| Bounce/debounce | `browser-kitech-derived-chromium` `patches/0008-kiryra-integrate-bounce-tracking.patch`: `debounce_rule.h/cc` adapted (Kiryra path layout, pref renamed to `kiryra.privacy.debounce_enabled`), copied into `components/debounce/core/browser` and `components/debounce/core/common`. `KiryraDebounceNavigationThrottle` wired into `CreateAndAddChromeThrottlesForNavigation`. Bundled initial ruleset of 7 common tracking redirectors; component-updater-driven rule refresh deferred to spec 06. Not yet exposed via user-facing settings toggle. |

Everything else in this table remains unintegrated.

No further Brave feature harvesting is part of the current scope.
