const fs = require("fs");

const input = fs.readFileSync("input.txt", { encoding: "utf8" });
const matches = input.match(
  "target area: x=([\\d-]+)\\.\\.([\\d-]+), y=([\\d-]+)\\.\\.([\\d-]+)"
);
const target = {
  x: Number(matches[1]),
  x2: Number(matches[2]),
  y: Number(matches[3]),
  y2: Number(matches[4]),
};

let bestMaxY = 0;

const launch = (vx, vy) => {
  let x = 0;
  let y = 0;
  let maxy = 0;
  let wasHit = false;

  while (true) {
    if (x >= target.x && x <= target.x2 && y >= target.y && y <= target.y2) {
      wasHit = true;
      bestMaxY = Math.max(bestMaxY, maxy);
      break;
    }
    if (
      (y < target.y && vy < 1) ||
      (x > target.x2 && vx === 0) ||
      (x < target.x && vx === 0)
    ) {
      break;
    }
    maxy = Math.max(maxy, y);

    x += vx;
    y += vy;
    if (vx > 0) vx--;
    else if (vx < 0) vx++;
    vy--;
  }

  return wasHit;
};

let hits = 0;
for (let i = -2000; i < 2000; i++) {
  for (let j = -2000; j < 2000; j++) {
    if (launch(j, i)) hits++;
  }
}
console.log(`Part 1: ${bestMaxY}`);
console.log(`Part 2: ${hits}`);
