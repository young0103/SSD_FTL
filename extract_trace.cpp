#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <input_trace> <output_trace> <lines_to_copy>\n";
        return 1;
    }

    const char* input_filename = argv[1];
    const char* output_filename = argv[2];
    long long lines_to_copy = std::stoll(argv[3]);

    std::ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file: " << input_filename << "\n";
        return 1;
    }

    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file: " << output_filename << "\n";
        return 1;
    }

    std::string line;
    long long line_count = 0;
    while (line_count < lines_to_copy && std::getline(input_file, line)) {
        output_file << line << "\n";
        ++line_count;
    }

    std::cout << "Copied " << line_count << " lines from " << input_filename 
              << " to " << output_filename << ".\n";

    input_file.close();
    output_file.close();

    return 0;
}
