# Browser Community Derived — Chromium

Public/open-source community-derived layer used by Kiryra.

This repository contains source, patches, and components derived from external Chromium browser projects. It is intentionally separate from KiTech-owned private browser code so provenance and licence obligations remain clear.

## Current upstream sources

### Brave Core

- upstream: `brave/brave-core`
- initial pinned revision: `973c5c8667ce80d2d3c227ef6e60df530eb26d35`
- Brave version at pin: `1.97.37`
- Chromium baseline at pin: `153.0.8010.37`
- Kiryra Chromium baseline: `153.0.8010.52`
- primary upstream licence: MPL-2.0
- status: imported source is byte-identical at the M153 Brave reference pin; Kiryra integration still requires build/test validation against the exact Kiryra Chromium pin

Brave-derived privacy/security/browser-engineering code may be reused directly when its applicable licence permits it. Brave product services and ecosystem dependencies are not part of Kiryra.

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
