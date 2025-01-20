//gc.cpp
#include <iostream>
#include "param.hpp"
#include "defs.hpp"


page* gc(int gccode){
    page *vblock;
    switch(gccode){
        case 0:
            vblock = kmem.first_in;
            if(kmem.first_in < kmem.vend){
                kmem.first_in += param::page_per_block;
            }else{
                kmem.first_in = kmem.vstart;
            }
            break;
        case 1:
            int cur_ivcnt = 0;
            int max_cnt = -1;
            int max_block = 0;
            for(; cur_ivcnt < param::physical_dev_size / param::block_size; cur_ivcnt++)
                if(max_cnt <= kmem.ivcnt[cur_ivcnt]){
                    max_cnt = kmem.ivcnt[cur_ivcnt];
                    max_block = cur_ivcnt;
                }
            vblock = kmem.vstart + cur_ivcnt*(param::page_per_block);
            kmem.ivcnt[cur_ivcnt] = 0;
            break;
    }
    run *p = kmem.freelist_head;
    kmem.freelist_head = p->next;
    page *log_page = reinterpret_cast<page*>(p);

    for(int i = 0; i < param::page_per_block; i++){//find live page
        page* src_page = (vblock + i);
        if((src_page)->iv){
            mtable[src_page->oob] = log_page;
            log_page->iv = true;
            src_page->iv = false;
            log_page++;
        }
    }
    kfree(vblock);
    return log_page;
}