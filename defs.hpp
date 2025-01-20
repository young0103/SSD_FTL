// defs.hpp
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct page{
    bool iv = false;
    int oob;
};

struct run {
  struct run *next;
};

page* kalloc(int gccode);
void kfree(page* v);
void freerange(page *vstart,page *vend, int gccode);

page* gc(int gccode);

extern page ivtable[param::iv_table_size];
extern page* mtable[param::mapping_table_size];

struct kmem_struct {
  struct run *freelist_head;
  struct run *freelist_tail;
  int freelist_cnt;
  page *vstart;
  page *vend;
  page *first_in;
  int *ivcnt;
};

extern kmem_struct kmem;

#ifdef __cplusplus
}
#endif
