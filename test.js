const flod = require('.');

const NUM_CELLS = 16;
const NUM_CELLS_OVERSCAN = NUM_CELLS + 1;

const _getEtherIndex = (x, y, z) => x + (z * NUM_CELLS_OVERSCAN) + (y * NUM_CELLS_OVERSCAN * NUM_CELLS_OVERSCAN);

const ether = new Float32Array(NUM_CELLS_OVERSCAN * (NUM_CELLS_OVERSCAN * 4) * NUM_CELLS_OVERSCAN);
ether.fill(1);
for (let dx = 0; dx <= NUM_CELLS_OVERSCAN; dx++) {
  for (let dz = 0; dz <= NUM_CELLS_OVERSCAN; dz++) {
    // for (let dy = 4; dy <= 4; dy++) {
      ether[_getEtherIndex(dx, 4, dz)] = -1;
    // }
  }
}

const peeks = new Uint8Array(16);

flod(ether, [0, NUM_CELLS, 0], peeks);

console.log(peeks);

/* let min = Infinity;
let max = -Infinity;
console.time('time');
for (let dx = 0; dx < 64; dx++) {
  for (let dz = 0; dz < 64; dz++) {
    const v = fn.in2D(1000 + dx, 1000 + dz);
    min = Math.min(v, min);
    max = Math.max(v, max);
  }
}
console.timeEnd('time');
console.log(min, max); */
