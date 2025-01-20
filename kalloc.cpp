//kalloc.cpp

#include "param.hpp"
#include "defs.hpp"
#include <cstdint>


struct run {
  struct run *next;
};

struct {
  struct run *freelist_head;
  struct run *freelist_tail;
} kmem;

void
freerange(void *vstart,void *vend)
{
  char *p;
  struct run *r;
  p = (char*)vstart;

  kmem.freelist_head = 0;
  kmem.freelist_tail = 0;

  for(; p < vend; p += sizeof(page)*(param::block_size/param::page_size)){
    r = (struct run*)p;
    r->next = 0;

    if (kmem.freelist_head == 0) {
        kmem.freelist_head = r;
        kmem.freelist_tail = r;
    }else{
      kmem.freelist_tail->next = r;
      kmem.freelist_tail = r;
    }
  }
}

char*
kalloc(){
  if (kmem.freelist_head == 0)
    return 0;

  struct run *r = kmem.freelist_head;
  kmem.freelist_head = r->next;

  if(kmem.freelist_head == 0)
    kmem.freelist_tail = 0;

  return (char *)r;
}

void
kfree(char *v){
  struct run *r = (struct run*)v;
  r->next = 0;

  if(kmem.freelist_head == 0){
    kmem.freelist_head = r;
    kmem.freelist_tail = r;
  }else{
    kmem.freelist_tail->next = r;
    kmem.freelist_tail = r;
  }
}