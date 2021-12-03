const fs = require("fs");

const input = fs.readFileSync("input.txt", { encoding: "utf8" });
const data = input
  .split("\n")
  .map((l) => ({ action: l.split(" ")[0], value: parseInt(l.split(" ")[1]) }));

// Part 1
let pos = 0;
let depth = 0;

data.forEach((a) => {
  if (a.action === "forward") pos += a.value;
  if (a.action === "down") depth += a.value;
  if (a.action === "up") depth -= a.value;
});

console.log(`Part 1: ${pos * depth} (p: ${pos} d: ${depth})`);

// Part 2
pos = 0;
depth = 0;
let aim = 0;

data.forEach((a) => {
  if (a.action === "forward") {
    pos += a.value;
    depth += aim * a.value;
  }
  if (a.action === "down") aim += a.value;
  if (a.action === "up") aim -= a.value;
});

console.log(`Part 2: ${pos * depth} (p: ${pos} d: ${depth})`);
