# Brave Core Provenance

## Initial source pin

```text
project: Brave Core
repository: https://github.com/brave/brave-core
revision: 9ab716daf80005ab38c0127d53136629a1b3d387
brave_version: 1.95.51
chromium_version: 151.0.7922.108
primary_repository_license: MPL-2.0
```

Kiryra currently pins Chromium `151.0.7922.97`. Brave skipped that exact Chromium point release in the reference history used here, so source imported from this Brave revision MUST be rebased and validated against Kiryra's exact Chromium revision before it is enabled in a production build.

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
