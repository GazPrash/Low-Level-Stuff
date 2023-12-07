#include<stdio.h>
#include<stdio.h>

#define LOWLVL_ALLOC malloc
#define LOWLVL_ASSERT assert


typedef struct {
  size_t size;
  size_t capacity;
  void* data;

} Region;

Region* RegionMemoryAlloc(size_t memory){
  Region* region;
  void * region_memory = LOWLVL_ALLOC(memory);
  LOWLVL_ASSERT(region_memory != NULL);
  region->data = region_memory;
  region->capacity = memory;
  
  return region;
}

void AllocateInt32Region(Region * region, __int32* data, size_t data_sz){
  if (region == NULL){
    perror("Region is Null. Please Use RegionMemoryAlloc to alloacate a Region.");
    return;
  }
  
}

int main(){
  Region* r = RegionMemoryAlloc(5000);


}