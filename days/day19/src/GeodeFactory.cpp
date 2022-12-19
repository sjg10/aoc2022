#include "GeodeFactory.h"
#include <regex>
#include <cassert>
#include <future>

void Factory::loadBlueprint(std::string & in) {
    const std::regex re("Blueprint (\\d*): Each ore robot costs (\\d*) ore. Each clay robot costs (\\d*) ore. Each obsidian robot costs (\\d*) ore and (\\d*) clay. Each geode robot costs (\\d*) ore and (\\d*) obsidian.");
    std::smatch m;
    std::regex_match(in, m, re);
    assert(m.size() == 8);
    assert(m_blueprints.size() + 1 == std::stoul(m.str(1)));
    m_blueprints.push_back(
        {
            Materials({std::stoul(m.str(2)), 0, 0, 0}),
            Materials({std::stoul(m.str(3)), 0, 0, 0}),
            Materials({std::stoul(m.str(4)), std::stoul(m.str(5)), 0, 0}),
            Materials({std::stoul(m.str(6)), 0, std::stoul(m.str(7)), 0}),
    }
    );
}


unsigned int Factory::getTotalScore() {
    unsigned int res = 0;
    std::vector<std::future<unsigned int>> futures;
    for(unsigned int i = 0 ; i < m_blueprints.size(); i++) {
        futures.emplace_back(std::async(std::launch::async,
                                &Factory::getMaxProcess, this, m_blueprints[i],
                                Materials({1, 0, 0, 0}), Materials({0, 0, 0, 0}), 24));
    }
    for(unsigned int i = 0 ; i < m_blueprints.size(); i++) {
        res += (i+1) * futures[i].get();
    }
    return res;
}

unsigned int Factory::getTotalScore2() {
    unsigned int res = 1;
    std::vector<std::future<unsigned int>> futures;
    for(unsigned int i = 0 ; i < 3; i++) {
        futures.emplace_back(std::async(std::launch::async,
                                &Factory::getMaxProcess, this, m_blueprints[i],
                                Materials({1, 0, 0, 0}), Materials({0, 0, 0, 0}), 32));
    }
    for(unsigned int i = 0 ; i < 3; i++) {
        res *= futures[i].get();
    }
        //res *= getMaxProcess(m_blueprints[i], Materials({1, 0, 0, 0}), Materials({0, 0, 0, 0}), 32);
    return res;
}

unsigned int ceil(unsigned int x, unsigned int y) {
    return (x + y - 1) / y;
}

unsigned int Factory::getMaxProcess(Blueprint const &bp, Materials robots, Materials materials, unsigned int t) {
    unsigned int time_to_build = 0;
    unsigned int s = 0;
    unsigned int max = 0;
    // Ore
    if (robots.ore > 0 && robots.ore < std::max({bp.ore_needs.ore, bp.clay_needs.ore, bp.obsidian_needs.ore, bp.geode_needs.ore})) {
        if (bp.ore_needs.ore <= materials.ore) { time_to_build = 1; }
        else {time_to_build = ceil(bp.ore_needs.ore - materials.ore, robots.ore) + 1;}
        assert(time_to_build);
        if(time_to_build < t) {
        s = getMaxProcess(bp,
            Materials({robots.ore + 1, robots.clay, robots.obsidian, robots.geode}),
            Materials({materials.ore + (robots.ore * time_to_build) - bp.ore_needs.ore, materials.clay + robots.clay * time_to_build, materials.obsidian + robots.obsidian * time_to_build, materials.geode + robots.geode * time_to_build}),
            t - time_to_build
        );
        if(s > max) { max = s;}
    }
    }
    
    // Clay
    if (robots.ore > 0 && robots.clay < std::max({bp.ore_needs.clay, bp.clay_needs.clay, bp.obsidian_needs.clay, bp.geode_needs.clay})) {
        if (bp.clay_needs.ore <= materials.ore) { time_to_build = 1; }
        else {time_to_build = ceil(bp.clay_needs.ore - materials.ore, robots.ore) + 1;}
        assert(time_to_build);
        if(time_to_build < t) {
            s = getMaxProcess(bp,
                Materials({robots.ore, robots.clay + 1, robots.obsidian, robots.geode}),
                Materials({materials.ore + (robots.ore * time_to_build) - bp.clay_needs.ore, materials.clay + robots.clay * time_to_build, materials.obsidian + robots.obsidian * time_to_build, materials.geode + robots.geode * time_to_build}),
                t - time_to_build
            );
            if(s > max) { max = s;}
        }
    }

    // Obsidian
    if (robots.clay > 0 && robots.obsidian < std::max({bp.ore_needs.obsidian, bp.clay_needs.obsidian, bp.obsidian_needs.obsidian, bp.geode_needs.obsidian})) {
        unsigned int t_1 =  bp.obsidian_needs.ore > materials.ore  ? ceil(bp.obsidian_needs.ore - materials.ore, robots.ore) + 1 : 1;
        unsigned int t_2 =  bp.obsidian_needs.clay > materials.clay  ? ceil(bp.obsidian_needs.clay - materials.clay, robots.clay)  + 1: 1;
        time_to_build = std::max<unsigned long>(t_1, t_2);
        assert(time_to_build);
        if(time_to_build < t) {
            s = getMaxProcess(bp,
                Materials({robots.ore, robots.clay, robots.obsidian + 1, robots.geode}),
                Materials({materials.ore + (robots.ore * time_to_build) - bp.obsidian_needs.ore, materials.clay + (robots.clay * time_to_build) - bp.obsidian_needs.clay, materials.obsidian + robots.obsidian * time_to_build, materials.geode + robots.geode * time_to_build}),
                t - time_to_build
            );
            if(s > max) { max = s;}
        }        
    }
    // Geode
    if (robots.obsidian > 0 && robots.ore > 0) {
        unsigned int t_1 =  bp.geode_needs.ore > materials.ore  ? ceil(bp.geode_needs.ore - materials.ore, robots.ore)  + 1: 1;
        unsigned int t_2 =  bp.geode_needs.obsidian > materials.obsidian  ? ceil(bp.geode_needs.obsidian - materials.obsidian, robots.obsidian) + 1 : 1;
        time_to_build = std::max<unsigned long>(t_1, t_2);
        assert(time_to_build);
        if(time_to_build < t) {
            s = getMaxProcess(bp,
                Materials({robots.ore, robots.clay, robots.obsidian, robots.geode  + 1}),
                Materials({materials.ore + (robots.ore * time_to_build) - bp.geode_needs.ore, materials.clay + (robots.clay * time_to_build), materials.obsidian + (robots.obsidian * time_to_build)  - bp.geode_needs.obsidian, materials.geode + robots.geode * time_to_build}),
                t - time_to_build
            );
            if(s > max) { max = s;}
        }
    }
    
    // Nothing
    s = materials.geode + (t * robots.geode);
    if(s > max) { max = s;}
    return max;
}

/*
unsigned int Factory::getMaxProcess(Blueprint const &bp, Materials robots, Materials materials, unsigned int t) {
    if(t == 0) {
        return materials.geode;
    }
    else {
        auto test = bp.testBuild(materials);
        materials.ore += robots.ore;
        materials.clay += robots.clay;
        materials.obsidian += robots.obsidian;
        materials.geode += robots.geode;
        unsigned int max = 0;
        if(test[0]) {
            auto s = getMaxProcess(bp, 
                Materials({robots.ore + 1, robots.clay, robots.obsidian, robots.geode}),
                materials, t-1
            );
            if(s > max) { max = s;}
        }
        if(test[1]) {
            auto s = getMaxProcess(bp, 
                Materials({robots.ore, robots.clay + 1, robots.obsidian, robots.geode}),
                materials, t-1
            );
            if(s > max) { max = s;}
        }
        if(test[2]) {
            auto s = getMaxProcess(bp, 
                Materials({robots.ore, robots.clay, robots.obsidian + 1, robots.geode}),
                materials, t-1
            );
            if(s > max) { max = s;}
        }
        if(test[3]) {
            auto s = getMaxProcess(bp, 
                Materials({robots.ore, robots.clay, robots.obsidian, robots.geode + 1}),
                materials, t-1
            );
            if(s > max) { max = s;}
        }
        auto s = getMaxProcess(bp, 
            Materials({robots.ore, robots.clay, robots.obsidian, robots.geode}),
                materials, t-1
        );
        if(s > max) { max = s;}
        return max;
    }
}*/