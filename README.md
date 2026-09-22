# Browser Community Derived — Chromium

Public/open-source community-derived layer used by Kiryra.

This repository contains source, patches, and components derived from external Chromium browser projects. It is intentionally separate from KiTech-owned private browser code so provenance and licence obligations remain clear.

This layer exists only when reuse makes Kiryra faster to build or easier to maintain. It does not define Kiryra product architecture, policy, defaults, naming, settings, or UX. A community component that increases long-term integration or maintenance cost should be replaced with a Kiryra-owned implementation.

## Current upstream sources

### Brave Core

- upstream: `brave/brave-core`
- initial pinned revision: `973c5c8667ce80d2d3c227ef6e60df530eb26d35`
- Brave version at pin: `1.97.37`
- Chromium baseline at pin: `153.0.8010.37`
- Kiryra Chromium baseline: `153.0.8010.52`
- primary upstream licence: MPL-2.0
- status: imported source is byte-identical at the M153 Brave reference pin; Kiryra integration still requires build/test validation against the exact Kiryra Chromium pin

Brave-derived privacy/security/browser-engineering code may be reused directly when its applicable licence permits it and the implementation is sufficiently self-contained. If a useful feature is materially entangled with Brave product plumbing, services, UI, telemetry, accounts, or ecosystem dependencies, it is not imported; Kiryra implements that capability independently.

## Licence model

Imported files retain their original copyright and licence notices.

MPL-2.0-covered files, including modifications to those covered files, remain available under MPL-2.0 when distributed. Separate KiTech-authored files are not automatically MPL-2.0 merely because they interact with an MPL-covered file; each component's actual licence governs.

Third-party code bundled by an upstream project must be tracked under its own licence rather than assumed to inherit the upstream repository's primary licence.

See:

- `brave/PROVENANCE.md`
- `brave/manifest.toml`
- `LICENSES/brave-core/MPL-2.0.txt`
- `THIRD_PARTY_NOTICES.md`

## Product boundary

This repository may contain reusable privacy/security implementations from Brave, but Kiryra does not adopt Brave Rewards/BAT, Ads, Wallet, Search coupling, VPN, Leo/AI, News, Talk, Brave Sync, Brave-specific Tor product integration, referrals, promotions, branding, accounts, or service endpoints merely because source code is available.

The authoritative policy is in `daijingroup/browser-spec`.

## Brave harvest status

The initial Brave M153 privacy/security harvest is complete at the pinned Brave Core revision.

Imported or adapted community-derived primitives:

- debounce common definitions and rule engine;
- query-filter schema/data/matching/filtering core;
- URL sanitization matcher/query-stripping core;
- Global Privacy Control primitive;
- HTTPS-upgrade exception-list decision core;
- de-AMP detection/canonical-URL parser;
- adblock Rust/C++ bridge and domain resolver;
- farbling PRNG primitive.

Kiryra intentionally does **not** import Brave's higher-level Shields/product framework. The following are Kiryra-owned implementation work:

- Shields UI, settings, site panel, service factories and orchestration;
- Brave component-updater integration;
- P3A/Brave telemetry;
- full farbling/fingerprinting integration beyond the isolated PRNG;
- ephemeral-storage service as implemented through Shields;
- Brave GPC network-delegate/product integration;
- Brave webcompat/reporting and product exception plumbing;
- Brave account, Sync, Search, Wallet, Rewards/BAT, Ads, VPN, AI, News, Talk, Tor-product, referral and promotional systems.

The upstream Rust `adblock` crate used by the imported bridge is pinned in `brave/manifest.toml` and will be vendored during build integration rather than being treated as Brave product source.

