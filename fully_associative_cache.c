#include <stdio.h>
#include <stdlib.h> 
#define CACHE_SIZE 16

typedef struct {
    int valid;
    unsigned int tag;
} CacheLine;
 
typedef struct {
    CacheLine* lines;
    int hits;
    int accesses;
} FullyAssociativeCache;
 
FullyAssociativeCache* createCache(int size) {
    FullyAssociativeCache* cache = (FullyAssociativeCache*)malloc(sizeof(FullyAssociativeCache));
    cache->lines = (CacheLine*)malloc(sizeof(CacheLine) * size);
    cache->hits = 0;
    cache->accesses = 0;    
    for (int i = 0; i < size; i++) {
        cache->lines[i].valid = 0;
        cache->lines[i].tag = 0;
    }
    return cache;
}
void accessMemory(FullyAssociativeCache* cache, unsigned int address) {
    cache->accesses++;
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache->lines[i].valid && cache->lines[i].tag == (address >> 4)) {
            cache->hits++;
            printf("Cache Hit at Address 0x%08x (Tag: 0x%08x)\n", address, cache->lines[i].tag);
            return;
        }
    }
    printf("Cache Miss at Address 0x%08x (Tag: 0x%08x)\n", address, address >> 4);
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!cache->lines[i].valid) {
            cache->lines[i].valid = 1;
            cache->lines[i].tag = address >> 4;
            return;
        }
    }
    int lruIndex = 0;
    for (int i = 1; i < CACHE_SIZE; i++) {
        if (cache->lines[i].valid && cache->lines[i].tag < cache->lines[lruIndex].tag) {
            lruIndex = i;
        }
    }
    printf("Replacing LRU at Index %d (Tag: 0x%08x) with Address 0x%08x (Tag: 0x%08x)\n", lruIndex, cache->lines[lruIndex].tag, address, address >> 4);
    cache->lines[lruIndex].tag = address >> 4;
}
 
 
int main() {
    unsigned int trace_file[] = {
         0x80000000 ,0x80000004, 0x80000008, 0x8000000C ,0x00000020, 0x80000010, 0x80000014 ,0x80000018 ,0x8000000C ,0x00000024 ,0x80000010 ,0x80000014 ,0x80000018, 0x8000000C ,0x00000028, 0x80000010, 0x80000014, 0x80000018 ,0x8000000C ,0x0000002C ,0x80000010 ,0x80000014 ,0x80000018, 0x8000000C, 0x00000030 ,0x80000010 ,0x80000014 ,0x80000018 ,0x8000000C ,0x00000034, 0x80000010 ,0x80000014 ,0x80000018, 0x8000000C ,0x00000038 ,0x80000010 ,0x80000014 ,0x80000018 , 0x8000000C, 0x0000003C ,0x80000010 ,0x80000014 ,0x80000018, 0x8000000C, 0x00000040, 0x80000010 ,0x80000014 ,0x80000018 ,0x8000000C ,0x00000044 ,0x80000010 ,0x80000014, 0x80000018, 0x8000000C ,0x00000048 ,0x80000010 ,0x80000014, 0x80000018, 0x8000000C ,0x0000004C, 0x80000010, 0x80000014, 0x80000018 ,0x8000000C ,0x00000050, 0x80000010, 0x80000014 ,0x80000018 ,0x8000000C ,0x00000054, 0x80000010, 0x80000014, 0x80000018 ,0x8000000C ,0x00000058, 0x80000010 ,0x80000014, 0x80000018 ,0x8000000C ,0x0000005C, 0x80000010 ,0x80000014, 0x80000018, 0x8000000C, 0x00000060 ,0x80000010 ,0x80000014 ,0x80000018, 0x8000000C, 0x00000064 ,0x80000010 ,0x80000014, 0x80000018 ,0x8000000C, 0x00000068 ,0x80000010 ,0x80000014 ,0x80000018 ,0x8000000C ,0x0000006C, 0x80000010, 0x80000014 ,0x80000018
    };
    FullyAssociativeCache* cache_simulator = createCache(CACHE_SIZE);
    for (int i = 0; i < sizeof(trace_file) / sizeof(trace_file[0]); i++) {
        accessMemory(cache_simulator, trace_file[i]);
    }
    printf("\nNumber of Cache Hits: %d\n", cache_simulator->hits);
    printf("Number of Cache Accesses: %d\n", cache_simulator->accesses);
    printf("Cache Hit Rate: %.2f%%\n", (float)cache_simulator->hits / cache_simulator->accesses * 100);
    free(cache_simulator->lines);
    free(cache_simulator);
    return 0;
}
