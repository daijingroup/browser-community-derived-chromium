# Brave Core Provenance

## Initial source pin

```text
project: Brave Core
repository: https://github.com/brave/brave-core
revision: 973c5c8667ce80d2d3c227ef6e60df530eb26d35
brave_version: 1.97.37
chromium_version: 153.0.8010.37
primary_repository_license: MPL-2.0
```

Kiryra currently pins Chromium `153.0.8010.52`. The selected Brave Core snapshot is the final master commit immediately before Brave moved from Chromium 153 to Chromium 154, and it targets Chromium `153.0.8010.37`. The currently imported debounce and farbling primitive files are byte-identical between the prior M151 reference snapshot and this M153 reference snapshot. They still MUST be built and tested against Kiryra's exact Chromium `153.0.8010.52` revision before production enablement.

## Initial imports

- `components/debounce/core/common/` — Brave bounce-tracking/debounce common feature definitions.
- `components/brave_shields/core/common/farbling_prng.h` — deterministic PRNG primitive used by Brave fingerprinting/farbling code.

The files are stored under `brave/` using their upstream-relative paths and are initially kept unchanged so copyright, attribution, and provenance are obvious.

- `components/global_privacy_control/` — Global Privacy Control preference/enablement primitive. Imported atomically from the pinned M153 Brave snapshot. Kiryra integration (MPL-covered adaptation): the preference was renamed from `brave.global_privacy_control_enabled` to `kiryra.privacy.global_privacy_control_enabled`, and the intra-component include path was adjusted from `brave/components/...` to `components/...` because Kiryra does not reproduce Brave's `brave/` checkout layout. Logic is otherwise unchanged from upstream. See `browser-kitech-derived-chromium` `patches/0005-kiryra-integrate-global-privacy-control.patch` for the Kiryra-owned wiring (pref registration, `Sec-GPC` header throttle).

- `components/query_filter/` — query-filter schema/data/matching/filtering core. Brave component installer, updater integration, pref namespace, and test plumbing are intentionally excluded; Kiryra will provide rule delivery and policy integration.

- `components/debounce/core/browser/debounce_rule.{cc,h}` — reusable debounce rule parser/application engine. Brave component updater, service factory, Shields-aware navigation throttle and product plumbing are excluded.

- `components/url_sanitizer/core/common/url_sanitizer_core.{cc,h}` — MPL-covered KiTech adaptation of Brave URLSanitizerService matcher/query-stripping logic. Brave component updater, Mojo/Android bridge and product service are excluded.

- `components/https_upgrade_exceptions/core/https_upgrade_exceptions_core.{cc,h}` — MPL-covered KiTech adaptation preserving Brave's exception-list and fail-safe decision behavior while excluding Brave component-updater/service plumbing.

- `components/de_amp/core/de_amp_parser.{cc,h}` — MPL-covered KiTech adaptation of Brave's AMP detection/canonical URL parser. Brave body-sniffer, preferences, feature gating and browser interception are excluded.

- `components/brave_shields/core/common/adblock/rs/` + `resolver/` — Brave's MPL-covered Rust/C++ adblock bridge and domain resolver. The higher-level Shields content/browser service, settings/UI, P3A, filter-list product plumbing, and component updater are excluded. The underlying `adblock` crate is recorded separately at v0.13.3 / revision `886d45dcf5283ce8eddc6d961e7dd27966ab23f2` and will be vendored only when Kiryra build integration is implemented.

## Harvest completion

The initial Brave M153 code-harvesting pass is complete.

Further Brave code MUST NOT be added merely to avoid implementing Kiryra functionality. New imports require a new review showing that the candidate is self-contained, licence-compatible, useful independently of Brave product plumbing, and materially better than a Kiryra-owned implementation.

The following areas were reviewed and deliberately left for independent Kiryra implementation because their useful behavior is materially coupled to Brave product architecture: higher-level Shields orchestration/UI, full farbling integration, ephemeral storage, GPC network plumbing, component updating, P3A/telemetry, and Brave webcompat/product services.

## Import rules

1. Pin an immutable Brave revision.
2. Record the Brave and Chromium versions.
3. Preserve source-file copyright and licence headers.
4. Record any non-MPL licences separately.
5. Keep MPL-covered files and Kiryra modifications to those files available under MPL-2.0 when distributed.
6. Import only sufficiently self-contained Brave code. If a candidate is materially coupled to Brave product/service/UI/account/telemetry plumbing, skip the import and implement the capability independently in Kiryra.
7. Do not copy imported implementation into private KiTech files to avoid source/licence obligations.
8. Rebase and test each imported component against the exact Kiryra Chromium pin.
9. Record Kiryra-side integration patches separately from pristine imported source where practical.
