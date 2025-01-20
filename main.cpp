//main.cpp

#include "param.hpp"
#include "defs.hpp"
#include <iostream>
#include <fstream>
#include <string>

page *mtable[param::mapping_table_size];
page ivtable[param::iv_table_size];

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <trace_file>\n";
        return 1;
    }

    std::ifstream trace_file(argv[1]);

    if (!trace_file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    freerange((char*)ivtable, (char*)ivtable + param::iv_table_size * sizeof(page));

    double timestamp;
    int io_type;
    uint64_t lba;
    int io_size;
    int stream_num;
    page *active_block = (page *)kalloc();
    std::cout << active_block << std::endl;
    if (active_block == 0){
        std::cout<<"there is no free page"<<std::endl;
        return 1;
    }
    page *log_page = active_block;

    while (trace_file >> timestamp 
                     >> io_type 
                     >> lba 
                     >> io_size 
                     >> stream_num)
    {   
        if(log_page - active_block >= (param::block_size / param::page_size)){
            active_block = reinterpret_cast<page*>(kalloc());
            if(active_block == 0)
                std::cout << "there is no invalid freeblock" << std::endl;
            log_page = active_block;
            std::cout<<"new block is allocated" << std::endl;
            std::cout << active_block << std::endl;
        }
        mtable[lba] = active_block;
        log_page->iv = io_type; 
        log_page->oob = lba;

        
        log_page += 1;
    }
    return 0;
}