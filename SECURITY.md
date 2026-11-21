# Security

Humanity is chain software. A bug in consensus, cryptography, authorization, or resource billing can move value or halt a network.

## Reporting

Do not open a public issue for a vulnerability.

Use [private vulnerability reporting](https://github.com/dougbutner/Humanity/security/advisories/new) when that feature is enabled on the repository. Otherwise contact the Tetra Grids maintainers in private. Include:

- What an attacker can do
- Which component (`channeld`, a `ra.*` contract, `keyd`, a script)
- The commit or version you tried
- A reproduction, or the reason a reproduction would be dangerous to post

We will answer with a plan for a fix and a release. We credit reporters who want credit, in the advisory, after the fix is out.

## What to expect

There is no public bug-bounty program in this repository yet. A report still gets a maintainer, a private thread, and a fix aimed at the next tag once tags exist. Until the first release, say the commit you built.

Operator questions, build failures, and doc mistakes belong in a public [bug report](https://github.com/dougbutner/Humanity/issues/new?template=bug.yml).
