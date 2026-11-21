# To do before mainnet

Protocol and release work that blocks a public chain. Collaboration requests (docs, the node workflow, the first package) live in [docs/contributing/requests.md](./docs/contributing/requests.md). This table is only the mainnet gate.

Add a row when a public chain waits on the work. Open a [contribution request](https://github.com/dougbutner/Humanity/issues/new?template=contribution-request.yml) with label `mainnet-todo` and put the issue number in the last column. Closing the issue removes the row.

The order and the Tetra context are in [PLAN.md](./PLAN.md).

| ID | Task | Issue |
| --- | --- | --- |
| M-1 | Compile-contracts workflow is green on `main` (`.github/workflows/compile-contracts.yml`) | |
| M-2 | Ubuntu 22.04 node build and parallelizable `ctest` are green on `main` ([CR-1](./docs/contributing/requests.md#cr-1-ubuntu-2204-node-ci)) | |
| M-3 | A release tag ships an Ubuntu 22.04 `.deb`, and `channeld --full-version` matches it ([CR-2](./docs/contributing/requests.md#cr-2-first-tagged-ubuntu-package)) | |
