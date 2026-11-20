# Eden election contract (trimmed)

Vendored from https://github.com/gofractally/Eden at the commit in `UPSTREAM_SHA`.

Kept: `contracts/eden` headers and on-chain sources. The important call site is `set_board_permission` in `src/elections.cpp`: after an election it writes `board.major` / `board.minor` via `ra::updateauth`, then attaches native `setepoch` so weights fade until the next election (or seven days). Full story: [README — Elections and permission epochs](../../README.md#elections-and-permission-epochs).

Never re-add:
- `packages/` (webapp, yarn workspace)
- `yarn.lock`, `package.json`, `node_modules`
- `libraries/` (eosiolib, abieos, clchain, debug_eos_vm)
- `external/` third-party clones (eos/mandel, Catch2, fmt, rapidjson, atomicassets)
- `docker/`, `.github/`, bios/boot/token contracts, clsdk docs
- `eden-micro-chain.cpp` (WASI/browser target; needs eosiolib)

Humanity does not build this with clsdk. Board helpers live in `contracts/fractal.perm`.
