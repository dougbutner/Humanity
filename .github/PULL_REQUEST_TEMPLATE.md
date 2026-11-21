## Summary

<!-- Why this change. Link the contribution request or bug. -->

## How to validate

<!-- The command you ran. Contracts: `bash scripts/compile-contracts.sh`. Node: the README build, then `ctest` from the build directory. -->

## Checklist

- [ ] Builds the piece this PR changes (or Compile contracts is the check, for a contract-only change)
- [ ] Tests added or updated when behavior changed
- [ ] `clang-format` applied to C++ this PR touches
- [ ] Docs updated when a person using the node, a contract, or the repo would notice
- [ ] New `.cpp` is listed in the matching `add_contract` / `add_subdirectory`
- [ ] New shipping wasm is listed in `scripts/compile-contracts.sh`
- [ ] `PLAN.md` and `site/plan/index.html` both move if the plan moved
