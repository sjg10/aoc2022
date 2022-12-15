#include "BeaconMap.h"
#include <regex>
#include <list>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <set>
#include <future>

unsigned int manhattanDistance(Point a, Point b) {
    return abs(a.first - b.first) + abs(a.second - b.second); 
}

Sensor::Sensor(std::string &in) {
    const std::regex re("Sensor at x=(-?\\d*), y=(-?\\d*): closest beacon is at x=(-?\\d*), y=(-?\\d*)");
    std::smatch m;
    std::regex_match(in, m, re);
    assert(m.size() == 5);
    int s_x = std::stol(m[1]);
    int s_y = std::stol(m[2]);
    int b_x = std::stol(m[3]);
    int b_y = std::stol(m[4]);
    sensor = std::make_pair(s_x, s_y);
    beacon = std::make_pair(b_x, b_y);
    d = manhattanDistance(beacon, sensor);
}

Range Sensor::getRange(int y) {
    int rem = d - abs(sensor.second - y);
    return std::make_pair(sensor.first - rem, sensor.first + rem); 
}

int Sensor::getBeaconInRow(int y) {
    return (beacon.second == y) ? beacon.first : std::numeric_limits<int>::max();
}

BeaconMap::BeaconMap(std::istream &input) {
    for(std::string readline; std::getline(input, readline);) {
        sensors.push_back(std::make_unique<Sensor>(readline));
    }
}
std::vector<Range> BeaconMap::getRangesAtRow(int y) const {
    std::vector<Range> ranges;
    std::list<Range> new_ranges;
    std::set<int> row_beacons;
    for (unsigned int i = 0; i < sensors.size(); i++) {
        int x = sensors[i]->getBeaconInRow(y);
        if(x != std::numeric_limits<int>::max()) {
            row_beacons.insert(x);
        }
        new_ranges.push_back(sensors[i]->getRange(y));
    }
    while (!new_ranges.empty()) {
        auto r = new_ranges.front();
        new_ranges.pop_front();
        if (r.second < r.first) {continue;} // skip invalid ranges
        bool intersected = false;
        for (unsigned int i = 0; i < ranges.size() && !intersected; i++) {
            if(r.second <= ranges[i].second && r.first >= ranges[i].first) {
                //new range contained in old
                intersected = true;
            }
            else if (r.second > ranges[i].second && r.first < ranges[i].first ) {
                // old range contained in new range
                new_ranges.push_back(std::make_pair(r.first, ranges[i].first  - 1));
                new_ranges.push_back(std::make_pair(ranges[i].second + 1, r.second));
                intersected = true;
            }
            else if (r.first <= ranges[i].second  && r.first >= ranges[i].first ) {
                //left of new range intersects
                new_ranges.push_back(std::make_pair(ranges[i].second + 1, r.second));
                intersected = true;
            }
            else if (r.second >= ranges[i].first && r.second <= ranges[i].second) {
                //right of new range intersects
                new_ranges.push_back(std::make_pair(r.first, ranges[i].first - 1));
                intersected = true;
            }
        }
        if (!intersected) {
            ranges.push_back(r);
        }
    }
    return ranges;
}
unsigned int BeaconMap::getRowPositions(int y) const {
    std::vector<Range> ranges = getRangesAtRow(y);
    std::set<int> row_beacons;
    for (unsigned int i = 0; i < sensors.size(); i++) {
        int x = sensors[i]->getBeaconInRow(y);
        if(x != std::numeric_limits<int>::max()) {
            row_beacons.insert(x);
        }
    }
    unsigned int ret = 0;
    for (unsigned int j = 0; j < ranges.size(); j++) {
        ret += (ranges[j].second - ranges[j].first) + 1;
    }
    return ret - row_beacons.size();
}

unsigned long int BeaconMap::findBeaconInRows(int max, int ymin, int ymax) const {
    for(int y = ymin; y <= ymax; y++) {
        auto ranges = getRangesAtRow(y);
        std::sort(ranges.begin(), ranges.end(), 
        [](const Range & a, const Range & b){ 
            return a.first < b.second; 
        });
        if (ranges[0].first > 0) { 
            long int x = ranges[0].first - 1; 
            return (x * 4000000L) + y;
        }
        for (unsigned int i = 0; i < ranges.size() - 1; i++) {
            if (ranges[i].second > max) break;
            else if (ranges[i+1].first != ranges[i].second + 1) {
                long int x = ranges[i].second + 1;
                return (x * 4000000L) + y;
            }
        }
        if (ranges.back().second < max) {
            long int x = ranges.back().second + 1;
            return (x * 4000000L) + y;
        }
    }
    throw std::runtime_error("Not found");
}

unsigned long int BeaconMap::findBeacon(int max) const {
    const unsigned int threads = std::thread::hardware_concurrency();
    std::vector<std::future<unsigned long int>> futures;
    for(long int ystep = 0; ystep < threads; ystep++) {
        futures.emplace_back(std::async(std::launch::async,
                                &BeaconMap::findBeaconInRows, this, max,
                                ystep * (max / threads),
                                std::min(((ystep + 1) * (max / threads)) - 1, (long int) max)
                                ));
    }
    for (auto &f : futures) {
        try{
            return f.get();
        } catch(const std::exception& e) {}
    }
    assert(false);
    return 0;
}
