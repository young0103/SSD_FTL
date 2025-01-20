//main.cpp

#include "param.hpp"
#include "defs.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

page *mtable[param::mapping_table_size];
page ivtable[param::iv_table_size];


int main(int argc, char* argv[]){
    if (argc < 3){
        std::cerr << "Usage: " << argv[0] << " <trace_file> <0:FIFO / 1:Greedy>\n";
        return 1;
    }

    std::ifstream trace_file(argv[1]);
    int gccode = std::stoi(argv[2]);

    switch (gccode) {
    case 0:
        std::cout << "Using FIFO GC method\n";
        break;
    case 1:
        std::cout << "Using Greedy GC method\n";
        break;
    default:
        std::cerr << "Invalid GC code: " << gccode << "\n";
        return 1;
    }

    if (!trace_file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }
    std::cout<<"Dividing Physical Device...\n";
    freerange(ivtable, ivtable + param::iv_table_size, gccode);

    double timestamp;
    int io_type;
    uint64_t lba;
    int io_size;
    int stream_num;
    page *log_page = kalloc(gccode);

    std::cout<<"Reading Trace File..\n";
    while (trace_file >> timestamp 
                     >> io_type 
                     >> lba 
                     >> io_size 
                     >> stream_num)
    {   
        if(mtable[lba]->iv)
            mtable[lba]->iv = false;
            if(gccode == 1)
                kmem.ivcnt[(log_page - ivtable)/param::page_per_block]++;
        mtable[lba] = log_page;
        log_page->iv = true;
        log_page->oob = lba;

        log_page += 1;
        if((log_page - ivtable + 1)%param::page_per_block == 0){
            log_page = kalloc(gccode);
            if(log_page == 0)
                std::cout << "there is no invalid freeblock" << std::endl;
                return 0;
        }
    }
    return 0;
}