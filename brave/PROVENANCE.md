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

## Import rules

1. Pin an immutable Brave revision.
2. Record the Brave and Chromium versions.
3. Preserve source-file copyright and licence headers.
4. Record any non-MPL licences separately.
5. Keep MPL-covered files and Kiryra modifications to those files available under MPL-2.0 when distributed.
6. Remove, replace, or isolate Brave product/service dependencies before Kiryra integration.
7. Do not copy imported implementation into private KiTech files to avoid source/licence obligations.
8. Rebase and test each imported component against the exact Kiryra Chromium pin.
9. Record Kiryra-side integration patches separately from pristine imported source where practical.
