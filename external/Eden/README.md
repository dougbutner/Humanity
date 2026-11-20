# Eden election contract (trimmed)

Vendored from https://github.com/gofractally/Eden at the commit in `UPSTREAM_SHA`.

Kept: `contracts/eden` headers and on-chain sources (for `elections.cpp` / board permission wiring).

Never re-add:
- `packages/` (webapp, yarn workspace)
- `yarn.lock`, `package.json`, `node_modules`
- `libraries/` (eosiolib, abieos, clchain, debug_eos_vm)
- `external/` third-party clones (eos/mandel, Catch2, fmt, rapidjson, atomicassets)
- `docker/`, `.github/`, bios/boot/token contracts, clsdk docs
- `eden-micro-chain.cpp` (WASI/browser target; needs eosiolib)

Humanity builds board rotation through `contracts/fractal.perm` and native `setepoch` on `ra`.
