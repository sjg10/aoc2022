#include <memory>
#include <map>
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"
//Further day includes go here
#include <iostream>


/** Register of days to run */
std::vector<std::pair<std::string, std::shared_ptr<Day>>> days = {
    {"Day01", std::make_shared<Day01>("../res/day01.txt")},
    {"Day02", std::make_shared<Day02>("../res/day02.txt")},
    {"Day03", std::make_shared<Day03>("../res/day03.txt")},
    {"Day04", std::make_shared<Day04>("../res/day04.txt")},
    {"Day05", std::make_shared<Day05>("../res/day05.txt")},
    {"Day06", std::make_shared<Day06>("../res/day06.txt")},
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