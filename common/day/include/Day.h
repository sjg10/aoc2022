#pragma once
#include <vector>
#include <string>
#include <fstream>
		
class Day {
    public:
        Day(const std::string &input_filename);
        void runday();
    protected:
        virtual std::vector<std::string> run(std::ifstream &input) = 0;
    private:
        std::ifstream m_stream;
};