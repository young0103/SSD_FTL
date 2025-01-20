//kalloc.cpp

#include "param.hpp"
#include "defs.hpp"
#include <cstdint>
#include <iostream>


kmem_struct kmem = {
    kmem.freelist_head = 0,
    kmem.freelist_tail = 0,
    kmem.freelist_cnt  = 0,
    kmem.vstart        = nullptr,
    kmem.vend          = nullptr,
    kmem.first_in      = nullptr,
    kmem.ivcnt         = nullptr
};

void
freerange(page *vstart,page *vend, int gccode)
{
  page *p;
  struct run *r;

  kmem.vstart = vstart;
  kmem.vend = vend;
  p = vstart;
  switch(gccode){
    case 0:
      kmem.first_in = vstart;
      break;
    case 1:
      int* ivcnt = new int[param::physical_dev_size/param::block_size];
      for (std::size_t i = 0; i < (param::physical_dev_size/param::block_size); i++){
      ivcnt[i] = 0;
      }
      kmem.ivcnt = ivcnt;
      break;
  }

  for(; p < vend; p += param::page_per_block){
    r = (struct run*)p;
    kmem.freelist_cnt ++;
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

page*
kalloc(int gccode){
  if (kmem.freelist_head == 0)  //empty freelist
    return 0;
  if (kmem.freelist_cnt <= 4){  //gc on
    return gc(gccode);
  }

  struct run *r = kmem.freelist_head;
  kmem.freelist_head = r->next;
  kmem.freelist_cnt --;

  if(kmem.freelist_head == 0)
    kmem.freelist_tail = 0;

  return reinterpret_cast<page*>(r);
}

void
kfree(page *v){
  struct run *r = (struct run*)v;
  r->next = 0;
  kmem.freelist_cnt ++;

  if(kmem.freelist_head == 0){
    kmem.freelist_head = r;
    kmem.freelist_tail = r;
  }else{
    kmem.freelist_tail->next = r;
    kmem.freelist_tail = r;
  }
}