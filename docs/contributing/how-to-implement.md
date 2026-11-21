# How to implement

A contribution request names an area, a why, a where, the steps, and the check that closes it. This page is the map those steps use. The open queue is [requests.md](./requests.md). The order of the whole repository is [PLAN.md](../../PLAN.md).

Build and test detail that would duplicate the README stays in the [README](../../README.md). Commands below are the ones a reviewer can run.

## The map

| You are changing | Start here |
| --- | --- |
| The node (`channeld`, `chan`, `keyd`, plugins) | `libraries/`, `plugins/`, `programs/` |
| A core contract | `contracts/` and its `CMakeLists.txt` |
| Election sources we vendor | Read `external/Eden/README.md` before you touch anything under `external/Eden` |
| Board permission helpers we compile | `contracts/fractal.perm` |
| Local boot | `scripts/launch-devnet.py` |
| Contract CI | `scripts/compile-contracts.sh` and `.github/workflows/compile-contracts.yml` |
| Operator manual | `docs/` |
| This plan or the public pages | `PLAN.md` and `site/` together |
| A meeting | `roundtables/README.md` |

Supported release host: **Ubuntu 22.04**. macOS is best-effort. Say which one you used.

## Before you branch

1. Search open issues and [requests.md](./requests.md).
2. If no request covers the work, [open one](https://github.com/dougbutner/Humanity/issues/new?template=contribution-request.yml). Fill in how to implement. Then build that.
3. Fork [dougbutner/Humanity](https://github.com/dougbutner/Humanity) and clone with submodules when you will build the node:

   ```bash
   git clone --recursive https://github.com/<you>/Humanity.git
   cd Humanity
   git remote add upstream https://github.com/dougbutner/Humanity.git
   git checkout -b feature/short-description
   ```

   A docs-only or contract-only clone can skip `--recursive`. The contract script does not need the node submodules.

Branch names: `feature/…`, `fix/…`, `docs/…`, `chore/…`.

## A docs change

1. Edit the page a reader actually opens. Operator facts live in `docs/`. Repository process lives in `CONTRIBUTING.md`, `PLAN.md`, and `docs/contributing/`.
2. If the page contains `[[info | …]]`, replace that callout with a paragraph or a blockquote. Leave the rest of the page's facts alone.
3. If you changed the plan, edit `site/plan/index.html` in the same commit. If you changed a recipe or a request, edit `site/contribute/index.html` too.
4. Open the pages locally when you touched `site/`:

   ```bash
   python3 -m http.server 8080 --directory site
   ```

## A contract change

You need [CDT](https://github.com/AntelopeIO/cdt) 4.1.x (`cdt-cpp` on `PATH`). Ubuntu 22.04 is the host the workflow uses. The deb is `cdt_4.1.1-1_amd64.deb` from the [v4.1.1 release](https://github.com/AntelopeIO/cdt/releases/tag/v4.1.1).

1. Match the nearest contract. Actions, tables, and include style follow the contract you are editing. `clang-format` the C++ you touch, using the repo-root [`.clang-format`](../../.clang-format).
2. A new `.cpp` on an existing contract goes on that directory's `add_contract(...)`. A new contract directory needs `add_subdirectory` in `contracts/CMakeLists.txt` and a `CMakeLists.txt` copied from the closest sibling.
3. A new shipping wasm path goes in the list inside `scripts/compile-contracts.sh`.
4. Compile:

   ```bash
   bash scripts/compile-contracts.sh
   ```

   Wasm is written under `build-contracts/` (gitignored). The script fails if a listed wasm is missing. Lower the job count with `CHANNEL_BUILD_JOBS=4` when the machine is tight.
5. Boot, when the change should show up on a local chain and you already have `channeld` / `chan` / `keyd`:

   ```bash
   python3 scripts/launch-devnet.py --reset --contracts-dir build-contracts
   ```

   A full node build with `-DBUILD_CONTRACTS=ON` still writes wasm under `build/contracts/`, and the launch script finds that directory on its own.

Pull requests that only touch `contracts/**` get the [Compile contracts](../../.github/workflows/compile-contracts.yml) workflow. That is the check to name in the PR.

## A node change

Build on Ubuntu 22.04. Prerequisites, the pinned Docker build, and the unpinned `cmake` / `make` steps are in the README under [Build and Install from Source](../../README.md#build-and-install-from-source). Some `.cpp` files need about 4GB of RAM. Lower `-j` if the compiler is killed.

From the build directory, run the parallelizable suite:

```bash
ctest -j "$(nproc)" -LE _tests
```

Boost.Test `--run_test=` takes the suite name from `BOOST_AUTO_TEST_SUITE()`, which is often different from the filename. Plugin tests live under `tests/`. Python TestHarness scripts run from the build directory.

There is no node workflow in the tree yet. Adding one is [CR-1](./requests.md#cr-1-ubuntu-2204-node-ci). Until it exists, paste the `ctest` command and the result in the pull request.

Leave submodule pointers alone. A change that only bumps `libraries/boost` or another `.gitmodules` path belongs upstream of this repository.

## A pages change

`site/` is the site. `site/brand/` is the Tetra chrome, tokens, and buttons, copied in as a set. Replace that directory as a set when the brand changes. Do not edit it into a second visual system.

`site/site.js` mounts the chrome. Page copy is the HTML under `site/index.html`, `site/plan/`, and `site/contribute/`. Relative links stay relative (`plan/`, `../contribute/`) so the site works on `https://dougbutner.github.io/Humanity/` and on a local server.

The workflow [`.github/workflows/pages.yml`](../../.github/workflows/pages.yml) deploys `site/` after an admin sets Pages to **GitHub Actions**. See [PLAN.md](../../PLAN.md#publishing-the-pages).

## The pull request

Use the template. Link the issue. Say how you validated.

Maintainer review is one approval for most changes, and a slower read for consensus, crypto, serialization, and resource limits. CI that applies to the PR has to pass. The contract workflow is the one that applies today.

## Labels

Use these when you open or triage an issue. Create a missing label once; the forms already name them.

| Label | Use |
| --- | --- |
| `contribution-request` | The five-part request |
| `bug` | A run that disagreed with the docs or the code |
| `good first issue` | A request whose steps fit in one sitting |
| `area: node` | `libraries/`, `plugins/`, `programs/` |
| `area: contracts` | `contracts/` |
| `area: docs` | `docs/`, the README, the plan |
| `area: ci` | `.github/workflows/` |
| `mainnet-todo` | A row in `TO-DO-B4-MAINNET.md` |
