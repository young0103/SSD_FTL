#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] 
                  << " <output_trace> <lines_to_generate>\n";
        return 1;
    }

    const char* output_filename = argv[1];
    long long lines_to_generate = std::stoll(argv[2]);

    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file: " << output_filename << "\n";
        return 1;
    }

    // 난수 생성기 설정
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist_time(0.0, 10.0); // Timestamp 범위
    std::uniform_int_distribution<int> dist_io_type(0, 1);       // IO type 0 또는 1
    std::uniform_int_distribution<uint64_t> dist_lba(0, 7000000ULL); // 임의의 LBA 범위
    std::uniform_int_distribution<int> dist_io_size(4096, 16384); // IO Size, 4KB ~ 16KB
    std::uniform_int_distribution<int> dist_stream(0, 10);      // Stream number 0~10

    for (long long i = 0; i < lines_to_generate; ++i) {
        double timestamp = dist_time(rng) + i * 0.000003; 
        int io_type = dist_io_type(rng);
        uint64_t lba = dist_lba(rng);
        int io_size = dist_io_size(rng);
        int stream_num = dist_stream(rng);

        output_file << timestamp << " "
                    << io_type << " "
                    << lba << " "
                    << io_size << " "
                    << stream_num << "\n";
    }

    std::cout << "Generated " << lines_to_generate 
              << " lines to " << output_filename << "\n";

    output_file.close();
    return 0;
}
