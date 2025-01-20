//param.hpp

#include <cstdint>

namespace param{
    constexpr std::uint64_t GB = 1000ULL * 1000ULL * 1000ULL;
    constexpr std::uint64_t GiB = 1024ULL * 1024ULL * 1024ULL;
    constexpr std::uint64_t MB = 1000ULL * 1000ULL;
    constexpr std::uint64_t MiB = 1024ULL * 1024ULL;
    constexpr std::uint64_t KB = 1000ULL;
    constexpr std::uint64_t KiB = 1024ULL;

    constexpr std::uint64_t logical_dev_size = 32ULL * GB;
    constexpr std::uint64_t physical_dev_size = 32ULL * GiB;
    constexpr std::uint64_t block_size = 2ULL * MB;
    constexpr std::uint64_t page_size = 4ULL * KB;

    constexpr std::uint64_t mapping_table_size = logical_dev_size/4096;
    constexpr std::uint64_t iv_table_size = physical_dev_size/4096;
    constexpr std::uint64_t op = logical_dev_size / physical_dev_size;  //overprovisioning
}
