import { mountTetraChrome } from "./brand/chrome.js"

const root = document.body.dataset.root || "./"

mountTetraChrome({
  home: root,
  nav: [
    { href: root, label: "Humanity" },
    { href: `${root}plan/`, label: "Plan" },
    { href: `${root}contribute/`, label: "Contribute" },
  ],
  footer: [
    { href: "https://tetra.earth", label: "Tetra" },
    { href: "https://know.tetra.earth", label: "Knowbase" },
    { href: "https://github.com/dougbutner/Humanity", label: "Repository" },
    { href: "https://github.com/dougbutner/Humanity/tree/main/docs", label: "Operator manual" },
  ],
  blurb: "Proof of attention",
})
