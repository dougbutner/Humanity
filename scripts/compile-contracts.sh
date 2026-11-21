#!/usr/bin/env bash
# Build contracts/ with the same CDT toolchain the root CMake external project uses.
# Wasm lands in build-contracts/<dir>/<name>.wasm (gitignored). Requires cdt-cpp on PATH.
set -euo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
cdt_bin=$(python3 -c 'import os, sys; print(os.path.realpath(sys.argv[1]))' "$(command -v cdt-cpp)")
cdt_root=$(dirname "$(dirname "$cdt_bin")")
toolchain="$cdt_root/lib/cmake/cdt/CDTWasmToolchain.cmake"
test -f "$toolchain"

if [[ -z "${CHANNEL_BUILD_JOBS:-}" ]]; then
  if command -v nproc >/dev/null 2>&1; then
    CHANNEL_BUILD_JOBS=$(nproc)
  else
    CHANNEL_BUILD_JOBS=$(sysctl -n hw.ncpu)
  fi
fi

build="$root/build-contracts"
cmake -S "$root/contracts" -B "$build" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$toolchain" \
  -Dcdt_DIR="$cdt_root/lib/cmake/cdt" \
  -DSYSTEM_CONFIGURABLE_WASM_LIMITS=ON \
  -DSYSTEM_BLOCKCHAIN_PARAMETERS=ON
cmake --build "$build" --parallel "$CHANNEL_BUILD_JOBS"

wasm=(
  ra.bios/ra.bios.wasm
  ra.boot/ra.boot.wasm
  ra.msig/ra.msig.wasm
  ra.system/ra.system.wasm
  ra.token/ra.token.wasm
  ra.wrap/ra.wrap.wasm
  ra.fees/ra.fees.wasm
  ra.bpay/ra.bpay.wasm
  ra.resources/ra.resources.wasm
  ra.authex/ra.authex.wasm
  ra.claim/ra.claim.wasm
  ra.org/ra.org.wasm
  ra.pure/flex.token.wasm
  fractal.perm/fractal.perm.wasm
)
for f in "${wasm[@]}"; do
  test -f "$build/$f"
  echo "ok $f"
done
