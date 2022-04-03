#include "bits.h"
#include "cache.h"

int extractBits(address_type address, int bits, int position){
    return (((1 << bits) - 1) & (address >> (position - 1)));
}
int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int set_bits = cache->set_bits;
  int block_bits = cache->block_bits;
  return extractBits(address,set_bits,block_bits + 1); 
}
int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  int set_bits = cache->set_bits;
  int block_bits = cache->block_bits;
  int tag_bits = 32 - block_bits - set_bits;
  return extractBits(address,tag_bits,set_bits + block_bits + 1);
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  int block_bits = cache->block_bits;
  return extractBits(address,block_bits,1);
}
