// defs.hpp
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char* kalloc();
void kfree(char* v);
void freerange(void* start, void* end);

struct page{
    bool iv;
    int oob;
};

#ifdef __cplusplus
}
#endif
