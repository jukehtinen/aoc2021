const fs = require("fs");

const input = fs.readFileSync("input.txt", { encoding: "utf8" });
const linelen = input.indexOf("\n") - 1;
const data = input.replace(/(\r\n|\n|\r)/gm, "");

const getHeight = (x, y) => {
  if (x < 0 || x >= linelen || y < 0 || y >= data.length / linelen) return 9;
  return parseInt(data[y * linelen + x]);
};

// Part 1
let risk = 0;
for (let i = 0; i < data.length; i++) {
  const value = parseInt(data[i]);
  const coord = { x: i % linelen, y: parseInt(i / linelen) };
  if (
    value < getHeight(coord.x - 1, coord.y) &&
    value < getHeight(coord.x + 1, coord.y) &&
    value < getHeight(coord.x, coord.y - 1) &&
    value < getHeight(coord.x, coord.y + 1)
  ) {
    risk += value + 1;
  }
}
console.log(`Part 1: ${risk}`);

// Part 2
let visited = [];
const flood = (x, y) => {
  if (getHeight(x, y) == 9 || visited[y * linelen + x]) return 0;

  visited[y * linelen + x] = 1;  
  let count = 1;

  count += flood(x + 1, y);
  count += flood(x - 1, y);
  count += flood(x, y + 1);
  count += flood(x, y - 1);

  return count;
};

let basins = [];
for (let i = 0; i < data.length; i++) {
  basins.push(flood(i % linelen, parseInt(i / linelen)));
}

let largest3 = basins.sort(function (a, b) {return a - b;}).reverse().slice(0, 3);
console.log(`Part 2: ${largest3.reduce((a, b) => a * b)}`);
