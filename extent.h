#pragma once

struct extent {
  uint start_block_address: 24;  // pointer to the extent
  uint length: 8;     // length of extent(number of blocks)
};