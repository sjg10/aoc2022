#include <chrono>
#include <iostream>
#include <filesystem>
#include "Day.h"

Day::Day(const std::string &input_filename) {
    m_stream = std::ifstream("../" + input_filename);
    std::cout << std::filesystem::current_path() << std::endl;
    if(m_stream.fail()) {throw std::runtime_error("Could not open file " + input_filename);}
}

void Day::runday() {
    std::cout << "**********************" << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = run(m_stream);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    for(unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Part " << i + 1 << ": " << res[i] << std::endl;
    }
    std::cout << "Elapsed time " << ms_int.count() << "ms" << std::endl;
    std::cout << "**********************" << std::endl << std::endl;
}