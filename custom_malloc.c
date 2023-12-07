#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define HEAP_CAP 640000 // 640KB memory
#define CHUNK_CAP 1024 //  Maximum chunk alloc limit

typedef struct{
  void* start_ptr;
  size_t size;

} Chunk;
// ChunkMemory

typedef struct{
  size_t size;
  Chunk Chunks[CHUNK_CAP];

} ChunkMemory;

int chunk_addr_compr(const void* a, const void* b){
  const Chunk * a_chunk = a;
  const Chunk * b_chunk = b;
  return a_chunk->start_ptr-b_chunk->start_ptr;
}

size_t find_chunk(const ChunkMemory * memory, void * ptr){
  Chunk reqrdchunk = {
    .start_ptr = ptr,
  };
  Chunk* chunk_found = bsearch(
    &reqrdchunk, 
    memory->Chunks, 
    memory->size, 
    sizeof(memory->Chunks[0]), 
    chunk_addr_compr
  );
  if (chunk_found == NULL) return -1;
  assert(memory->Chunks <= chunk_found);
  size_t index = (chunk_found - memory->Chunks);
  return index;
}

void insert_chunk(ChunkMemory * memory, void * ptr, size_t ptr_size){
  assert(memory->size < CHUNK_CAP);
  memory->Chunks[memory->size].start_ptr = ptr;
  memory->Chunks[memory->size].size = ptr_size;

  for (size_t i = memory->size; i > 0; i--){
    if (memory->Chunks[i].start_ptr < memory->Chunks[i-1].start_ptr){
      const Chunk tempchunk = memory->Chunks[i];
      memory->Chunks[i] = memory->Chunks[i-1];
      memory->Chunks[i-1] = tempchunk;
    } else break;
  }
  memory->size++;
}

void delete_chunk(ChunkMemory * memory, size_t index){
  assert(index < memory->size);
  for (size_t i = index; i < memory->size; i++){
    memory->Chunks[i] = memory->Chunks[i+1];
  }
  memory->size--;
}

// Merges currently deallocated seperated chunks into a single
// big chunk
void merge_chunk(const ChunkMemory * memory, ChunkMemory* tempMemory){
  // erase temp memory
  // tempMemory->size = 0;

  for (size_t i =0; i < memory->size; i++){
    const Chunk curr_chunk = memory->Chunks[i];
    if (tempMemory->size > 0){
      Chunk lastChunk = tempMemory->Chunks[tempMemory->size-1];
      if (lastChunk.start_ptr + lastChunk.size == curr_chunk.start_ptr){
        tempMemory->size += curr_chunk.size;
      } else insert_chunk(tempMemory, curr_chunk.start_ptr, curr_chunk.size);
    } else {
      insert_chunk(tempMemory, curr_chunk.start_ptr, curr_chunk.size);
    }
  }
  
}

void dump_chunks(const ChunkMemory memory, char* message){
  printf("Total Chunks: %zu : %s\n", memory.size, message);
  for (size_t i = 0; i < memory.size; i++){
    printf("%d. Address : %p | Size : %zu\n",
    i+1, memory.Chunks[i].start_ptr, memory.Chunks[i].size);
  }
}


// using char array to ensure contigous memory | each char rep 1 byte of memory
char Heap[HEAP_CAP] = {0};
ChunkMemory deallocated_memory = {
  .size = 1,
  .Chunks = {
    [0] = {.start_ptr = Heap, .size = sizeof(Heap)}
  }
};

ChunkMemory allocated_memory = {0};

void * halloc(size_t size){
  if (size <= 0) return NULL;

  for (size_t i=0; i < deallocated_memory.size; i++){
    Chunk chunk = deallocated_memory.Chunks[i];
    if (size <= chunk.size){
      delete_chunk(&deallocated_memory, i);

      void * new_memory = chunk.start_ptr;
      size_t tail_memory = chunk.size - size;
      insert_chunk(&allocated_memory, new_memory, size);
      
      if (tail_memory > 0){
        insert_chunk(&deallocated_memory, chunk.start_ptr + size, tail_memory);
      }
      return new_memory;

    }
  }
  return NULL;
}


// O(allocated_chunk_mem) for now -> TC
void hfree(void *ptr){
  if (ptr == NULL) return;
  const size_t ptr_ind = find_chunk(&allocated_memory, ptr);
  assert(ptr_ind >= 0);
  Chunk chunk_to_rem = allocated_memory.Chunks[ptr_ind];
  insert_chunk(&deallocated_memory, chunk_to_rem.start_ptr, chunk_to_rem.size);
  delete_chunk(&allocated_memory, ptr_ind);
  // this is stupid because we first use bsearch with O(n) to find the node
  // then we use delete_chunk with O(n) to go to the same node and manage deletion
  // SO overall it's O(n) again no point of using bsearch
}

void hcollector(){

}

int main(){
  void * refptr;
  for (int i = 0; i <= 10; i++){
    if (i%3==0 || i == 10 || 1){
      refptr = halloc(i);
      hfree(refptr);
      continue;
    }
    halloc(i);
  }
  // printf("%d\n", sizeof(refptr));
  dump_chunks(allocated_memory, "Allocated");
  printf("\n");
  dump_chunks(deallocated_memory, "Deallocated");
  return 0;
}