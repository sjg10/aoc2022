#pragma once
#include <istream>
#include <vector>
#include <set>
#include <memory>

using Range = std::pair<int,int>;
using Point = std::pair<int,int>;

/** Ordering for non overlapping ranges */
namespace RangeCmp {
    struct RangeCmpStruct {
        bool operator() (Range const & lhs, Range const & rhs) const {
            return lhs.first < rhs.second;
        }
    };
}

using RangeSet = std::set<Range,  RangeCmp::RangeCmpStruct>;


class Sensor {
public:
    Sensor(std::string &in);
    Range getRange(int y);
    // Return x coord if beacon is in row y, else int max
    int getBeaconInRow(int y);
private:
    Point beacon;
    Point sensor;
    unsigned int d;
};

class BeaconMap {
public:
    BeaconMap(std::istream &input);
    unsigned int getRowPositions(int y) const;
    unsigned long int findBeacon(int max) const;
private:
    // searches for missed beacon in row, throws if none found
    unsigned long int findBeaconInRows(int max, int ymin, int ymax) const; 
    RangeSet getRangesAtRow(int y) const;
    std::vector<std::unique_ptr<Sensor>> sensors;
};