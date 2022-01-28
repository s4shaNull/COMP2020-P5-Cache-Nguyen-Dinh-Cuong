#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "cache.h"
#include "print_helpers.h"

cache_t *make_cache(int capacity, int block_size, int assoc, enum protocol_t protocol, bool lru_on_invalidate_f){
  cache_t *cache = malloc(sizeof(cache_t));
  cache->stats = make_cache_stats();
  
  cache->capacity = capacity;      // in Bytes
  cache->block_size = block_size;  // in Bytes
  cache->assoc = assoc;            // 1, 2, 3... etc.

  // FIX THIS CODE!
  // first, correctly set these 5 variables. THEY ARE ALL WRONG
  // note: you may find math.h's log2 function useful
  cache->n_cache_line = capacity / block_size;
  cache->n_set = capacity / (assoc * block_size);
  cache->n_offset_bit = log2(block_size);
  cache->n_index_bit = log2(cache->n_set);
  cache->n_tag_bit = 32 - (cache->n_index_bit) - (cache->n_offset_bit);

  // next create the cache lines and the array of LRU bits
  // - malloc an array with n_rows
  // - for each element in the array, malloc another array with n_col
  // FIX THIS CODE!

  cache->lines = malloc((cache->n_set)*sizeof(cache_line_t*));
  for (int i = 0; i < (cache->n_set); i++)
  {
    (cache->lines)[i] = malloc(assoc * sizeof(cache_line_t));
  }
  cache->lru_way = malloc((cache->n_set)*sizeof(int));

  // initializes cache tags to 0, dirty bits to false,
  // state to INVALID, and LRU bits to 0
  // FIX THIS CODE!
  for (int i = 0; i < (cache->n_set); i++) {
    for (int j = 0; j < assoc; j++) {
      (cache->lines[i][j]).tag = 0;
      (cache->lines[i][j]).dirty_f = false;
      (cache->lines[i][j]).state = INVALID;
    }
    cache->lru_way[i]=0;
  }

  cache->protocol = protocol;
  cache->lru_on_invalidate_f = lru_on_invalidate_f;
  
  return cache;
}

/* Given a configured cache, returns the tag portion of the given address.
 *
 * Example: a cache with 4 bits each in tag, index, offset
 * in binary -- get_cache_tag(0b111101010001) returns 0b1111
 * in decimal -- get_cache_tag(3921) returns 15 
 */
unsigned long get_cache_tag(cache_t *cache, unsigned long addr) {
  // FIX THIS CODE!
  return addr >> (32 - (cache->n_tag_bit));
}

/* Given a configured cache, returns the index portion of the given address.
 *
 * Example: a cache with 4 bits each in tag, index, offset
 * in binary -- get_cache_index(0b111101010001) returns 0b0101
 * in decimal -- get_cache_index(3921) returns 5
 */
unsigned long get_cache_index(cache_t *cache, unsigned long addr) {
  // FIX THIS CODE!
  return (addr >> cache->n_offset_bit) & ~(~0 << cache->n_index_bit);
}

/* Given a configured cache, returns the given address with the offset bits zeroed out.
 *
 * Example: a cache with 4 bits each in tag, index, offset
 * in binary -- get_cache_block_addr(0b111101010001) returns 0b111101010000
 * in decimal -- get_cache_block_addr(3921) returns 3920
 */
unsigned long get_cache_block_addr(cache_t *cache, unsigned long addr) {
  // FIX THIS CODE!
  return (addr >> (cache->n_offset_bit)) << (cache->n_offset_bit);
}


/* this method takes a cache, an address, and an action
 * it proceses the cache access. functionality in no particular order: 
 *   - look up the address in the cache, determine if hit or miss
 *   - update the LRU_way, cacheTags, state, dirty flags if necessary
 *   - update the cache statistics (call update_stats)
 * return true if there was a hit, false if there was a miss
 * Use the "get" helper functions above. They make your life easier.
 */
void update_lru(cache_t *cache, int index, int chosen_way)
{
  if (cache->assoc == 1)
  {
    return;
  }
  else if (chosen_way < (cache->assoc -1))
  {
    cache->lru_way[index] = chosen_way + 1;
  }
  else
  {
    cache->lru_way[index] = 0;
  }

}

bool update_cache(cache_t *cache, unsigned long tag, unsigned long index, int chosen_way, enum action_t action, enum state_t updated_state, bool hit_f, bool writeback_f, bool upgrade_miss_f)
{
  log_way(chosen_way);
  if (!hit_f && (action == LOAD || action == STORE))
  {
    cache->lines[index][chosen_way].tag = tag;
  }
  update_stats(cache->stats, hit_f, writeback_f, upgrade_miss_f, action);
  cache->lines[index][chosen_way].state = updated_state;
  if (action == LOAD)
  {
    if(!hit_f)
    {
      cache->lines[index][chosen_way].dirty_f = 0;
      update_lru(cache, index, chosen_way);
    }
  }
  else if (action == STORE)
  {
    cache->lines[index][chosen_way].dirty_f = 1;
    update_lru(cache, index, chosen_way);
  }
  return hit_f;
}

bool vi_protocol(cache_t *cache, unsigned long addr, enum action_t action)
{
  unsigned long tag = get_cache_tag(cache, addr);
  unsigned long index = get_cache_index(cache, addr);
  log_set(index);
  for (int a = 0; a < cache->assoc; a++)
  {
    if (tag == cache->lines[index][a].tag)
    {
      if (cache->lines[index][a].state == INVALID)
      {
        if (action == LD_MISS || action == ST_MISS)
        {
          return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, false, false);
        }
        else
        {
          return update_cache(cache, tag, index, cache->lru_way[index], action, VALID, false, false, false);
        }
      }
      else
      {
        if (action == LD_MISS || action == ST_MISS)
        {
          return update_cache(cache, tag, index, a, action, INVALID, true, cache->lines[index][a].dirty_f, false);
        }
        else
        {
          return update_cache(cache, tag, index, a, action, VALID, true, false, false);
        }
      }
    }
  }
  bool evict_dirty = cache->lines[index][cache->lru_way[index]].dirty_f;
  if (cache->lines[index][cache->lru_way[index]].state == INVALID)
  {
    if (action == LD_MISS || action == ST_MISS)
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, evict_dirty, false);
    }
    else
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, VALID, false, evict_dirty, false);
    }
  }
  else
  {
    if (action == LD_MISS || action == ST_MISS) 
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, VALID, false, false, false);
    }
    else
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, VALID, false, evict_dirty, false);
    }
  }
}

bool msi_protocol(cache_t *cache, unsigned long addr, enum action_t action)
{
  unsigned long tag = get_cache_tag(cache, addr);
  unsigned long index = get_cache_index(cache, addr);
  log_set(index);
  for (int a = 0; a < cache->assoc; a++)
  {
    if (tag == cache->lines[index][a].tag)
    {
      if (cache->lines[index][a].state == INVALID)
      {
        if (action == LOAD) 
        {
          return update_cache(cache, tag, index, cache->lru_way[index], action, SHARED, false, false, false);
        }
        else if (action == STORE) 
        {
          return update_cache(cache, tag, index, cache->lru_way[index], action, MODIFIED, false, false, false);
        }
        else
        {
          return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, false, false);
        }
      }
      else if (cache->lines[index][a].state == MODIFIED)
      {
        if (action == LD_MISS)
        {
          return update_cache(cache, tag, index, a, action, SHARED, true, true, false);
        }
        else if (action == ST_MISS) 
        {
          return update_cache(cache, tag, index, a, action, INVALID, true, true, false);
        }
        else
        {
          return update_cache(cache, tag, index, a, action, MODIFIED, true, false, false);
        }
      }
      else
      {
        if (action == STORE)
        {
          return update_cache(cache, tag, index, a, action, MODIFIED, false, false, true);
        }
        else if (action == ST_MISS)
        {
          return update_cache(cache, tag, index, a, action, INVALID, true, false, false);
        }
        else
        {
          return update_cache(cache, tag, index, a, action, SHARED, true, false, false);
        }
      }
    }
  }
  bool evict_dirty = cache->lines[index][cache->lru_way[index]].dirty_f;
  if (cache->lines[index][cache->lru_way[index]].state == INVALID) 
  {
    if (action == LOAD) 
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, SHARED, false, evict_dirty, false);
    }
    else if (action == STORE) 
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, MODIFIED, false, evict_dirty, false);
    }
    else
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, evict_dirty, false);
    }
  }
  else if (cache->lines[index][cache->lru_way[index]].state == MODIFIED)
  {
    if (action == LD_MISS)
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, SHARED, false, true, false);
    }
    else if (action == ST_MISS)
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, true, false);
    }
    else
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, SHARED, false, evict_dirty, false);
    }
  }
  else 
  {
    if (action == STORE) 
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, MODIFIED, false, evict_dirty, false);
    }
    else if (action == ST_MISS) 
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, INVALID, false, evict_dirty, false);
    }
    else
    {
      return update_cache(cache, tag, index, cache->lru_way[index], action, SHARED, false, evict_dirty, false);
    }
  }
  return false;
}

bool access_cache(cache_t *cache, unsigned long addr, enum action_t action) {
  // FIX THIS CODE!
  if (cache->protocol == VI)
  {
    return vi_protocol(cache, addr, action);
  }
  else if (cache->protocol == MSI)
  {
    return msi_protocol(cache, addr, action);
  }
  unsigned long tag = get_cache_tag(cache, addr);
  unsigned long index = get_cache_index(cache, addr);
  log_set(index);
  for (int i = 0; i < cache->assoc; i++)
  {
    if (tag == cache->lines[index][i].tag)
    {
      return update_cache(cache, tag, index, i, action, VALID, true, false, false);
    }
  }
  bool writeback_f = cache->lines[index][cache->lru_way[index]].dirty_f == 1;
  if (action == LD_MISS || action == ST_MISS)
  {
    writeback_f = false;
  }
  return update_cache(cache, tag, index, cache->lru_way[index], action, VALID, false, writeback_f, false);
}
