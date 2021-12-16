const fs = require("fs");

const input = fs.readFileSync("input.txt", { encoding: "utf8" }).split("\n");

let template = input[0].replace(/(\r\n|\n|\r)/gm, "").split("");
let rules = {};
for (let i = 2; i < input.length; i++) {
  const match = input[i].match(/(\w+) -> (\w)/);
  rules[match[1]] = match[2];
}

// Part 1
for (let i = 0; i < 10; i++) {
  let insert = [];
  for (let t = 0; t < template.length - 1; t++) {
    insert.push(rules[`${template[t]}${template[t + 1]}`]);
  }
  for (let t = 0; t < insert.length; t++) {
    template.splice(2 * t + 1, 0, insert[t]);
  }
}

let counts = {};
template.forEach((p) => (counts[p] = 1 + (counts[p] || 0)));
const min = Object.entries(counts).reduce((prev, curr) =>
  prev[1] < curr[1] ? prev : curr
);
const max = Object.entries(counts).reduce((prev, curr) =>
  prev[1] > curr[1] ? prev : curr
);
console.log(`Part 1: ${max[1] - min[1]}`);

// Part 2
template = input[0].replace(/(\r\n|\n|\r)/gm, "").split("");

// Initial polys
let polys = {};
for (let t = 0; t < template.length - 1; t++) {
  const poly = `${template[t]}${template[t + 1]}`;
  polys[poly] = 1 + (polys[poly] || 0);
}

// Split polys into two and count em - very hacky, put it prints correct answer so wtv .)
for (let i = 0; i < 40; i++) {
  let newPolys = {};
  Object.keys(polys).forEach((p) => {
    let new1 = `${p[0]}${rules[p]}`;
    let new2 = `${rules[p]}${p[1]}`;
    newPolys[new1] = polys[p] + (newPolys[new1] || 0);
    newPolys[new2] = polys[p] + (newPolys[new2] || 0);
  });

  Object.keys(newPolys).forEach((p) => {
    if (polys[p]) polys[p] += newPolys[p];
    else polys[p] = newPolys[p];
  });
  polys = newPolys;
}

let counts2 = {};
for(let [key, value] of Object.entries(polys)) {
  counts2[key[0]] = value + (counts2[key[0]] || 0);
}
const min2 = Object.entries(counts2).reduce((prev, curr) =>
  prev[1] < curr[1] ? prev : curr
);
const max2 = Object.entries(counts2).reduce((prev, curr) =>
  prev[1] > curr[1] ? prev : curr
);
console.log(`Part 2: ${max2[1] - min2[1] - 1}`);