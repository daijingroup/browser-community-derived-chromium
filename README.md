# Browser Community Derived — Chromium

Public/open-source community-derived layer used by Kiryra.

This repository contains source, patches, and components derived from external Chromium browser projects. It is intentionally separate from KiTech-owned private browser code so provenance and licence obligations remain clear.

## Current upstream sources

### Brave Core

- upstream: `brave/brave-core`
- initial pinned revision: `9ab716daf80005ab38c0127d53136629a1b3d387`
- Brave version at pin: `1.95.51`
- Chromium baseline at pin: `151.0.7922.108`
- Kiryra Chromium baseline: `151.0.7922.97`
- primary upstream licence: MPL-2.0
- status: imported source requires Kiryra rebase/integration validation against the Kiryra Chromium pin

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
