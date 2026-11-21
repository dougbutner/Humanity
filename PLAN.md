# Plan

The repository can boot. A second person still has to guess how to begin. This plan is the work that makes Humanity a place to build together, and the order that work should happen.

The public reading copy is [`site/`](./site/). It publishes from this repository. See [Publishing the pages](#publishing-the-pages). When you change this plan, change [`site/plan/index.html`](./site/plan/index.html) in the same commit.

## Tetra

[Tetra](https://tetra.earth) is the grid this chain settles. Tetra means four. Proof of attention.

An offer is a record: what it takes, how you know it was done, and a cost or a payment. The payment can be RA, USDC, or any token the offer names. You become a node by offering and by completing offers. The same relation holds at every scale we use: one person, a group of four to six, a region, the planet.

Four faces:

- **Passport** — who you are, where you are from, what you offer
- **Discovery** — daily charts. A region, then a nation, then the world
- **Recurve** — fractal governance. Small groups, representatives, chiefs
- **Localize** — house rules, the procedure for a place, a region you turn on

RA is the daily attention currency. Level changes how much arrives. Humanity is the ledger under that grid: accounts you can say out loud, permissions that nest, storage at a fixed price, elections whose signer weights fade when the term ends. The app lives at tetra.earth. This repository is the chain. The knowbase is [know.tetra.earth](https://know.tetra.earth).

## Where the repository stands

Already in the tree:

- A Spring 2.0 node (`channeld`, `chan`, `keyd`) with Savanna, EM and ED keys, the XPR-style RAM market, fractal elections, and permission epochs. The map is the [README](./README.md).
- Core contracts under `contracts/` in the `ra.*` namespace, plus `flex.token` and `fractal.perm`.
- A local boot: `python3 scripts/launch-devnet.py --reset`.
- The argument for the chain, [WHITEPAPER.md](./WHITEPAPER.md), and the money layer, [PURE-LIQUID.md](./PURE-LIQUID.md).
- Operator manual in [`docs/`](./docs/). Roundtables in [`roundtables/`](./roundtables/).

Still thin, and why it matters:

- Issue forms, a pull-request template, a security policy, and pages were missing. A new person had a long README and no queue. Those files land with this plan.
- [TO-DO-B4-MAINNET.md](./TO-DO-B4-MAINNET.md) was an empty table pointing at files that were not in the repository. It now holds the mainnet gate only.
- The README described a Compile contracts Action before the workflow existed. The workflow is [`.github/workflows/compile-contracts.yml`](./.github/workflows/compile-contracts.yml). It is finished when a run on `main` is green.
- There is no tag and no shipped `.deb` yet. The install section describes the package we intend to publish.
- [`docs/`](./docs/) still uses Spring callouts (`[[info | Note]]`). GitHub shows those as raw text.
- [`skills/README.md`](./skills/README.md) used to list Cursor skills that are not checked in. GitHub contributors follow [CONTRIBUTING.md](./CONTRIBUTING.md).

## What finishing means

Two finishes. Keep them in separate lists.

**Collaborative finish.** Someone who has never been in a roundtable can find a request, follow the steps, open a pull request, and see a contract build run. That finish comes first.

**Mainnet finish.** An Ubuntu 22.04 binary from a tag, a green node test on that host, and a boot whose trust assumptions are written down. The rows are in [TO-DO-B4-MAINNET.md](./TO-DO-B4-MAINNET.md).

Passport, Discovery, and Localize stay on tetra.earth. Recurve's on-chain board is the election code in this repository (`external/Eden`, `contracts/fractal.perm`, permission epochs). The app is a different repository.

## Order of work

Do them in this order. A later step leans on the earlier one.

### 1. A door

Land, in the repository:

- This plan
- [How to implement](./docs/contributing/how-to-implement.md)
- [Contribution requests](./docs/contributing/requests.md)
- Issue forms and a pull-request template under `.github/`
- [CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md) and [SECURITY.md](./SECURITY.md)
- The Tetra section in the README
- The pages in `site/`

A contribution request has five parts: area, why, where, how to implement, done when. The form uses those fields. A request without steps is a wish. Send it back.

### 2. A green contract build

Workflow: [`.github/workflows/compile-contracts.yml`](./.github/workflows/compile-contracts.yml).

It installs [CDT](https://github.com/AntelopeIO/cdt) 4.1.1 on Ubuntu 22.04 and runs [`scripts/compile-contracts.sh`](./scripts/compile-contracts.sh). That script configures `contracts/` with the same toolchain arguments the root `CMakeLists.txt` passes into its external project. It checks that each shipping `.wasm` exists.

Done when a run on `main` is green. Until then, M-1 in the mainnet table stays open.

When you add a contract, add one path to the wasm list in the script. That is [CR-3](./docs/contributing/requests.md#cr-3-keep-the-wasm-list-honest).

### 3. A green node build

[CR-1](./docs/contributing/requests.md#cr-1-ubuntu-2204-node-ci). Ubuntu 22.04, the unpinned README build or the pinned Docker build, then from the build directory:

```bash
ctest -j "$(nproc)" -LE _tests
```

One workflow. The parallelizable suite first. Serial and long-running tests stay optional until that job is stable.

This is the gate that lets a node pull request mean something.

### 4. A release you can install

[CR-2](./docs/contributing/requests.md#cr-2-first-tagged-ubuntu-package). Tag `vMAJOR.MINOR.PATCH`. Publish the Ubuntu 22.04 `.deb` on GitHub Releases. `channeld --full-version` prints that version. The README install section becomes a path someone can walk.

macOS stays best-effort. The release host is Ubuntu 22.04.

### 5. The queue stays the requests

New protocol work starts as a contribution request, then a row in `TO-DO-B4-MAINNET.md` when it blocks a public chain. Put the issue number in the table. Closing the issue removes the row.

Docs, CI, and first-hour fixes stay in `docs/contributing/requests.md`. They stay off the mainnet table.

### 6. The operator manual, one page at a time

[CR-4](./docs/contributing/requests.md#cr-4-one-callout-at-a-time). When you edit a page under `docs/`, replace a `[[info | …]]` callout you touch with a normal paragraph or blockquote. Leave the rest of that page's facts alone. A mass rewrite hides real edits.

## How to implement

The recipes are in [how to implement](./docs/contributing/how-to-implement.md). Short form:

1. Read the request. If the steps are thin, improve the request before you write code.
2. Branch from `main`: `feature/…`, `fix/…`, `docs/…`.
3. Change the smallest surface that makes the request true.
4. Build the piece you changed. Contracts: `bash scripts/compile-contracts.sh`. Node: the README unpinned build, then the parallelizable `ctest`.
5. Open a pull request with the template. Link the request.

Consensus, crypto, serialization, and resource limits need a maintainer who will read them slowly. Say that in the request.

## Boundaries

- Edit this repository. Leave submodule commits where they are (`libraries/boost`, `libraries/libfc/libraries/boringssl`, and the rest of `.gitmodules`).
- `external/Eden` is a trimmed vendor. The kept sources and the ban list are in `external/Eden/README.md`. Board helpers that we compile are `contracts/fractal.perm`.
- Deposit credit is a trusted relayer. The steps are in `contracts/ra.claim/FUTURE.md`. A proving design is a new request with a written trust model, filed before any table change.
- Social recovery is described in the whitepaper. A request names the account graph and the limit check before any table is added.
- Code permission on this chain is `ra.code`.
- `RAM_RESTRICTIONS` is what makes `payer=get_self()` safe. Leave `FORWARD_SETCODE` off when `ra` must keep intercepting `setcode`. The launch script's `--no-forward-setcode` also skips Savanna, because Savanna depends on that feature.
- Supported release host: Ubuntu 22.04. State your OS in every bug report.

## Publishing the pages

The site source is [`site/`](./site/). Files in `site/brand/` are a copy of the Tetra visual system (void `#050705`, Jost, green `#22c55e`, radius 0, the existing chrome). Do not restyle them here. When the brand changes, replace that directory from the brand source as a whole.

Workflow: [`.github/workflows/pages.yml`](./.github/workflows/pages.yml). It deploys the `site/` directory with GitHub Actions.

One setting lives in GitHub, outside git. A maintainer with admin on `dougbutner/Humanity` opens **Settings → Pages → Build and deployment → Source: GitHub Actions**. The next push to `main` that touches `site/` publishes `https://dougbutner.github.io/Humanity/`.

Until that setting is on, open the same pages locally:

```bash
python3 -m http.server 8080 --directory site
```

Then visit `http://127.0.0.1:8080/`.
