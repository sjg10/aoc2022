#pragma once
#include <vector>
#include <string>
#include <array>
#include <algorithm>

struct Materials {
    unsigned long int ore;
    unsigned long int clay;
    unsigned long int obsidian;
    unsigned long int geode;
};

struct Blueprint {
    Materials ore_needs;
    Materials clay_needs;
    Materials obsidian_needs;
    Materials geode_needs;
    std::array<unsigned, 4> testBuild(Materials &material) const {
        return {
            material.ore >= ore_needs.ore && material.clay >= ore_needs.clay && material.obsidian >= ore_needs.obsidian && material.geode >= ore_needs.geode,
            material.ore >= clay_needs.ore && material.clay >= clay_needs.clay && material.obsidian >= clay_needs.obsidian && material.geode >= clay_needs.geode,
            material.ore >= obsidian_needs.ore && material.clay >= obsidian_needs.clay && material.obsidian >= obsidian_needs.obsidian && material.geode >= obsidian_needs.geode,
            material.ore >= geode_needs.ore && material.clay >= geode_needs.clay && material.obsidian >= geode_needs.obsidian && material.geode >= geode_needs.geode,
        };
    };

};

class Factory {
public:
    Factory() {}
    void loadBlueprint(std::string & in);
    unsigned int getTotalScore();
    unsigned int getTotalScore2();
private:
    unsigned int getMaxProcess(Blueprint const &bp, Materials robots, Materials materials, unsigned int t);
    std::vector<Blueprint> m_blueprints;
};