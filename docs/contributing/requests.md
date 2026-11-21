# Contribution requests

Each request below is written so someone else can implement it. The recipes they share are in [how to implement](./how-to-implement.md). File a new one with the [contribution request form](https://github.com/dougbutner/Humanity/issues/new?template=contribution-request.yml).

When you open the GitHub issue, put the issue number next to the request in this file. When the work merges, move the request to the bottom under Closed, with the pull request link.

Mainnet blockers are a shorter list, in [TO-DO-B4-MAINNET.md](../../TO-DO-B4-MAINNET.md). A request lands there only when a public chain waits on it.

## Open

### CR-1. Ubuntu 22.04 node CI

- **Area:** ci, node
- **Why:** A node pull request currently ends on the author's machine. Reviewers cannot see a `ctest` result unless the author pastes one.
- **Where:** a new `.github/workflows/node.yml`. Build instructions already in the [README](../../README.md#unpinned-build).
- **How to implement:**
  1. One job, `ubuntu-22.04`.
  2. Checkout with submodules.
  3. Install the README's unpinned packages (`build-essential`, `cmake`, `git`, `libcurl4-openssl-dev`, `libgmp-dev`, `llvm-11-dev`, `python3-numpy`, `file`, `zlib1g-dev`).
  4. Configure and build the way the README does, with `CHANNEL_BUILD_JOBS` low enough for the runner (start at 2; these units can use about 4GB each).
  5. From the build directory run `ctest -j 2 -LE _tests`.
  6. Leave serial tests, wasm spec tests, and long-running tests out of this job until it is green twice.
- **Done when:** a pull request that touches `libraries/`, `plugins/`, or `programs/` shows this job, and a run on `main` is green. Then M-2 in the mainnet table can close.

### CR-2. First tagged Ubuntu package

- **Area:** ci, node
- **Why:** The README tells a person to install `humanity*.deb` from Releases. There is no tag yet, so that path has nowhere to land.
- **Where:** GitHub Releases, and the version string `channeld --full-version` already prints. Packaging is the pinned build in `tools/reproducible.Dockerfile`, or the unpinned `make package` from the README.
- **How to implement:**
  1. Decide the version (`v0.1.0` is enough if `main` is still the development line). Follow [CONTRIBUTING.md](../../CONTRIBUTING.md#releases): `vMAJOR.MINOR.PATCH`.
  2. Produce an Ubuntu 22.04 `.deb` from that commit.
  3. Publish it on the Release for that tag. The asset name can stay `humanity*.deb` so the README command still matches.
  4. Install it in a clean Ubuntu 22.04 container and run `channeld --full-version`. The line starts with the tag.
- **Done when:** the Releases page has that asset, and the version check above is in the release notes. Then M-3 can close.

### CR-3. Keep the wasm list honest

- **Area:** contracts, ci
- **Good first issue.** The list is short and the failure is loud.
- **Why:** [Compile contracts](../../.github/workflows/compile-contracts.yml) only proves the wasm paths named in [`scripts/compile-contracts.sh`](../../scripts/compile-contracts.sh). A new contract that builds and is forgotten still looks green.
- **Where:** `scripts/compile-contracts.sh`, the `wasm=(...)` array.
- **How to implement:**
  1. When you add or rename a contract target, add `directory/name.wasm` to that array. `flex.token` lives at `ra.pure/flex.token.wasm`.
  2. Run `bash scripts/compile-contracts.sh` with CDT 4.1.x, or wait for the workflow on the pull request.
- **Done when:** the script's list and `contracts/CMakeLists.txt`'s `add_subdirectory` calls name the same shipping contracts. Test-only contracts under `contracts/test_contracts` stay off the list.

### CR-4. One callout at a time

- **Area:** docs
- **Good first issue.**
- **Why:** Pages under `docs/` still contain Spring callouts, written `[[info | Note]]`. GitHub renders that as raw brackets, so a new operator learns to ignore the manual.
- **Where:** any file under `docs/` you are already editing. The index is [`docs/index.md`](../index.md).
- **How to implement:**
  1. Pick one page you are reading for another reason.
  2. Replace each `[[info | …]]` / `|` callout block on that page with a paragraph or a blockquote that says the same thing.
  3. Do not retitle the page, move sections, or "clean up" facts you did not come to check.
- **Done when:** that page has zero `[[info` markers, and the meaning of each former callout is still on the page.

## Closed

None yet. The door this plan adds (forms, conduct, security, pages source, the contract script) is the baseline, recorded in [PLAN.md](../../PLAN.md). It is not a request someone still has to pick up.
