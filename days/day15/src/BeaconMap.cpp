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

RangeSet BeaconMap::getRangesAtRow(int y) const {
    RangeSet ranges;
    std::set<int> row_beacons;
    for (unsigned int i = 0; i < sensors.size(); i++) {
        int x = sensors[i]->getBeaconInRow(y);
        if(x != std::numeric_limits<int>::max()) {
            row_beacons.insert(x);
        }
        auto r = sensors[i]->getRange(y);

        if( r.second < r.first) {continue;}
    
        bool toadd = true;
        for (auto itr = ranges.cbegin(); itr != ranges.cend();) {
            if(r.second < itr->first) {
                // as set is ordered we are done with the loop
                break;
            }
            else if(r.second <= itr->second && r.first >= itr->first) {
                //(r is contained in another range, so we are done)
                toadd = false;
                break;
            }
            else if(itr->second <= r.second && itr->first >= r.first) { 
                // this range is contained in r, so throw it out and continue
                itr = ranges.erase(itr);
            }
            else { 
                auto r2 = *itr;
                bool modified = false;
                if (r.second >= r2.first && r.second <= r2.second) {
                    //right of new range intersects 
                    r.second = r2.second;
                    modified = true;
                }
                if (r.first <= r2.second  && r.first >= r2.first ) {
                    //left of new range intersects
                    r.first = r2.first,
                    modified = true;
                }
                if(modified) {
                    itr = ranges.erase(itr);
                }
                else {
                    itr++;
                }
            }
        }
        if (toadd) {
            ranges.insert(r);
        }
    }
    return ranges;
}

unsigned int BeaconMap::getRowPositions(int y) const {
    auto ranges = getRangesAtRow(y);
    std::set<int> row_beacons;
    for (unsigned int i = 0; i < sensors.size(); i++) {
        int x = sensors[i]->getBeaconInRow(y);
        if(x != std::numeric_limits<int>::max()) {
            row_beacons.insert(x);
        }
    }
    unsigned int ret = 0;
    for(auto const &range: ranges) {
        ret += (range.second - range.first) + 1;
    }
    return ret - row_beacons.size();
}

unsigned long int BeaconMap::findBeaconInRows(int max, int ymin, int ymax) const {
    for(int y = ymin; y <= ymax; y++) {
        auto ranges = getRangesAtRow(y);
        if (ranges.begin()->first > 0) { 
            long int x = ranges.begin()->first - 1; 
            return (x * 4000000L) + y;
        }
        for (auto itr = ranges.begin(); itr != ranges.end(); itr++) {
            auto nxt = itr;
            nxt++;
            if (itr->second > max) break;
            else if (nxt->first != itr->second + 1) {
                long int x = itr->second + 1;
                return (x * 4000000L) + y;
            }
        }
        if (ranges.rbegin()->second < max) {
            long int x = ranges.rbegin()->second + 1;
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
