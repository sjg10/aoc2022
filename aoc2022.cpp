#include <memory>
#include <map>
#include "Day01.h"
//Further day includes go here
#include <iostream>


/** Register of days to run */
std::vector<std::pair<std::string, std::shared_ptr<Day>>> days = {
    {"Day01", std::make_shared<Day01>("../res/day01.txt")},
    //Further days go here
};

int main(void) {
    std::cout << "AOC2022 Start" << std::endl;
    for (auto const &day : days) {
        std::cout << day.first << " Start" << std::endl;
        day.second->runday();
    }
    std::cout << "AOC2022 Complete" << std::endl;

    return 0;
}