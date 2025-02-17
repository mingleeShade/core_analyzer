/*
 * heap.h
 *
 *  Created on: Dec 13, 2011
 *  Modifed on: May 15, 2022
 *      Author: myan
 */
#ifndef _HEAP_H
#define _HEAP_H
#include <string>
#include <map>
#include "ref.h"

struct inuse_block
{
    inuse_block(address_t a, size_t s) : addr(a), size(s) {}
    inuse_block(const struct inuse_block& blk) : addr(blk.addr), size(blk.size) {}
    address_t addr;
    size_t    size;
};

/*
 * Memory usage/leak
 * Aggregated memory is the collection of memory blocks that are reachable from
 * either a global variable or a local variable
 */
struct reachable_block : public inuse_block
{
    reachable_block(address_t a, size_t s) : inuse_block(a, s) {}
    reachable_block(const struct inuse_block& blk) : inuse_block(blk) {}
    ~reachable_block()
    {
        if (index_map)
        {
            free(index_map);
        }
    }

    size_t        aggr_size  = 0;       // cached reachable count/size by me (solely)
    unsigned long aggr_count = 0;
    unsigned int* index_map  = nullptr; // cached indexes of all sub in-use blocks
};

struct memory_node
{
    std::string type_name;
    int object_count = 0;
    size_t directly_size = 0;
    size_t referenced_size = 0;
    std::vector<memory_node*> referenced_list;
};

struct object_type
{
    std::string obj_name;
    std::string type_name;
    address_t vaddr = 0;
    size_t size = 0;
    size_t directly_size = 0;
    enum storage_type  storage_type;
    std::vector<object_type*> referenced_list;
    // store object_list that reference this object for easy traceability
    std::vector<object_type*> referenced_by;
};


typedef const char* (*HeapVersionFunc)(void);
typedef bool (*InitHeapFunc)(void);
typedef bool (*HeapWalkFunc)(address_t addr, bool verbose);
typedef bool (*IsHeapBlockFunc)(address_t addr);
typedef bool (*GetHeapBlockInfoFunc)(address_t addr, struct heap_block* blk);
typedef bool (*GetNextHeapBlockFunc)(address_t addr, struct heap_block* blk);
typedef bool (*GetBiggestBlocksFunc)(struct heap_block* blks, unsigned int num);
typedef void (*PrintSizeFunc)(size_t sz);
typedef bool (*WalkInuseBlocksFunc)(struct inuse_block* opBlocks, unsigned long* opCount);

/** Different programs might use different heap managers
 * This heap interface is the abstract interface for each heap manager
 *
**/
struct CoreAnalyzerHeapInterface
{
    HeapVersionFunc heap_version;
    InitHeapFunc init_heap;
    HeapWalkFunc heap_walk;
    IsHeapBlockFunc is_heap_block;
    GetHeapBlockInfoFunc get_heap_block_info;
    GetNextHeapBlockFunc get_next_heap_block;
    GetBiggestBlocksFunc get_biggest_blocks;
    /*
    * Get all in-use memory blocks
    *   If param opBlocks is NULL, return number of in-use only,
    *   otherwise, populate the array with all in-use block info
    */
    WalkInuseBlocksFunc walk_inuse_blocks;

};

extern std::map<std::string, CoreAnalyzerHeapInterface*> gCoreAnalyzerHeaps;

extern CoreAnalyzerHeapInterface* gCAHeap;
#define CA_HEAP gCAHeap

/*
* This function is called at bootstrap or when target is changed
* and after target memory layout is scanned.
*/
extern bool init_heap_managers();

/*
* Individual heap manager calls this function in its init function
* to declare its name, heap interface, and whether it detects its heap data in the target.
*/
extern void register_heap_manager(std::string, CoreAnalyzerHeapInterface*, bool);

/*
* Each heap manager implements an init function
* Maybe we don't need to explicitly expose them. We may scape these functions at compile time
* the same way gdb commands initializers are collected.
*/
extern void register_pt_malloc_2_27();
extern void register_pt_malloc_2_31();
extern void register_pt_malloc_2_35();
extern void register_tc_malloc();
extern void register_je_malloc();
extern void register_mscrt_malloc();

extern std::string get_supported_heaps();

extern struct inuse_block* build_inuse_heap_blocks(unsigned long*);
extern struct inuse_block* find_inuse_block(address_t, struct inuse_block*, unsigned long);

extern bool display_heap_leak_candidates(void);

extern bool biggest_blocks(unsigned int num);
extern bool biggest_heap_owners_generic(unsigned int num, bool all_reachable_blocks);
extern void print_size(size_t sz);

extern bool heap_dump(const std::string& file_name);

extern bool
calc_aggregate_size(const struct object_reference* ref,
                    size_t var_len,
                    bool all_reachable_blocks,
                    std::vector<struct reachable_block>& inuse_blocks,
                    size_t* aggr_size,
                    unsigned long* count);

extern bool
set_obj_reference(struct object_type* obj_type,
                  size_t var_len,
                  std::vector<struct reachable_block>& inuse_blocks,
                  std::vector<struct object_type>& obj_types);

/*
 * Histogram of heap blocks
 */
struct MemHistogram
{
    unsigned int   num_buckets;
    size_t*        bucket_sizes;
    unsigned long* inuse_cnt;
    size_t*        inuse_bytes;
    unsigned long* free_cnt;
    size_t*        free_bytes;
};
extern void display_mem_histogram(const char*);
extern void init_mem_histogram(unsigned int nbuckets);
extern void release_mem_histogram(void);
extern void add_block_mem_histogram(size_t, bool, unsigned int);

#endif
