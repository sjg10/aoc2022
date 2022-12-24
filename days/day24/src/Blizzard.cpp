#include "Blizzard.h"
#include <cassert>
#include <numeric>
#include <list>
#include <map>
#include <iostream>

void Blizzards::addBlizzard(unsigned int x, unsigned int y, Direction d) {
    switch(d) {
        case Direction::UP: upgoingcolumns[y].push_back(x); break;
        case Direction::DOWN: downgoingcolumns[y].push_back(x); break;
        case Direction::LEFT: leftgoingrows[x].push_back(y); break;
        case Direction::RIGHT: rightgoingrows[x].push_back(y); break;
    }
}
void Blizzards::setBounds(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
}

std::vector<std::tuple<int, unsigned int, unsigned int>> Blizzards::getMoves(int xin, unsigned int y, unsigned int d) {
    std::vector<std::tuple<int, unsigned int, unsigned int>>  ret;
    unsigned int hshift = d % m_width;
    unsigned int vshift = d % m_height;

    if (xin < 0) {
        std::vector<std::tuple<int, unsigned int, unsigned int>>  out = {{xin, y, d}};
        bool move = true;
        for(auto const &xval: downgoingcolumns[0]) {
            move &= ((xval + vshift) % m_height) != 0;
        }
        for(auto const &xval: upgoingcolumns[0]) {
            move &= ((xval + (m_height - vshift)) % m_height) != 0;
        }
        for(auto const &yval: rightgoingrows[0]) {
            move &= ((yval + hshift) % m_width) != y;
        }
        for(auto const &yval: leftgoingrows[0]) {
            move &= ((yval + (m_width - hshift)) % m_width) != y;
        }
        if(move) { out.push_back({0,0,d});}
        return out;
    }
    else if (xin == (int)m_height) {
        std::vector<std::tuple<int, unsigned int, unsigned int>> out = {{xin, y, d}};
        bool move = true;
        for(auto const &xval: downgoingcolumns[m_width - 1]) {
            move &= ((xval + vshift) % m_height) != 0;
        }
        for(auto const &xval: upgoingcolumns[m_width - 1]) {
            move &= ((xval + (m_height - vshift)) % m_height) != 0;
        }
        for(auto const &yval: rightgoingrows[m_height - 1]) {
            move &= ((yval + hshift) % m_width) != y;
        }
        for(auto const &yval: leftgoingrows[m_height - 1]) {
            move &= ((yval + (m_width - hshift)) % m_width) != y;
        }
        if(move) { out.push_back({m_height - 1,m_width - 1,d});}
        return out;
    }
    else {
        unsigned int x = abs(xin);
        bool N = (x > 0);
        bool S = (x < m_height - 1);
        bool E = (y < m_width - 1);
        bool W = (y > 0);
        bool C = true;

        if (W) {
            for(auto const &xval: downgoingcolumns[y - 1]) {
                W &= ((xval + vshift) % m_height) != x;
            }
            for(auto const &xval: upgoingcolumns[y - 1]) {
                W &= ((xval + (m_height - vshift)) % m_height) != x;
            }
        }
        for(auto const &xval: downgoingcolumns[y]) {
            auto nx = ((xval + vshift) % m_height);
            if(N) N &= nx != x - 1;
            if (C) C &= nx != x;
            if(S) S &= nx != x + 1;
        }
        for(auto const &xval: upgoingcolumns[y]) {
            auto nx = ((xval + (m_height - vshift)) % m_height);
            if(N) N &= nx != x - 1;
            if(C) C &= nx != x;
            if(S) S &= nx != x + 1;
        }
        if (E) {
            for(auto const &xval: downgoingcolumns[y + 1]) {
                E &= ((xval + vshift) % m_height) != x;
            }
            for(auto const &xval: upgoingcolumns[y + 1]) {
                E &= ((xval + (m_height - vshift)) % m_height) != x;
            }
        }

        if (S) {
            for(auto const &yval: rightgoingrows[x + 1]) {
                S &= ((yval + hshift) % m_width) != y;
            }
            for(auto const &yval: leftgoingrows[x + 1]) {
                S &= ((yval + (m_width - hshift)) % m_width) != y;
            }
        }
        for(auto const &yval: rightgoingrows[x]) {
            auto ny = ((yval + hshift) % m_width);
            if (W) W &= ny != y - 1;
            if (C) C &= ny != y;
            if (E) E &= ny != y + 1;
        }
        for(auto const &yval: leftgoingrows[x]) {
            auto ny = ((yval + (m_width - hshift)) % m_width);
            if (W) W &= ny != y - 1;
            if (C) C &= ny != y;
            if (E) E &= ny != y + 1;
        }
        if(N)  {
            for(auto const &yval: rightgoingrows[x - 1]) {
                if (N) N &= ((yval + hshift) % m_width) != y;
            }
            for(auto const &yval: leftgoingrows[x - 1]) {
                if (N) N &= ((yval + (m_width - hshift)) % m_width) != y;
            }
        }
        std::vector<std::tuple<int, unsigned int, unsigned int>>  out = {};
        if (N) {out.push_back({x - 1,y,d});}
        if (S) {out.push_back({x + 1,y,d});}
        if (E) {out.push_back({x,y + 1,d});}
        if (W) {out.push_back({x,y - 1,d});}
        if (C) {out.push_back({x,y,d});}
        return out;
    }
}

BlizzardMap::BlizzardMap(std::istream &in) {
    blizzards = std::make_unique<Blizzards>();
    std::string readline;
    std::getline(in, readline);
    unsigned int width = readline.size() - 2;
    unsigned int x = 0;
    while(std::getline(in, readline)) {
        for(unsigned int y = 0; y < width; y++) {
            switch (readline[y + 1]) {
                case '#': break;// last line
                case '>': blizzards->addBlizzard(x,y,Direction::RIGHT); break;
                case '<': blizzards->addBlizzard(x,y,Direction::LEFT); break;
                case 'v': blizzards->addBlizzard(x,y,Direction::DOWN); break;
                case '^': blizzards->addBlizzard(x,y,Direction::UP); break;
                case '.': break;
                default: assert(false);
            }
        }
        x++;
    }
    m_width = width;
    m_height = x - 1;
    blizzards->setBounds(m_width, m_height);
    wrap = (m_width * m_height) / (std::gcd(m_width,m_height));

}
std::pair<unsigned int, unsigned int> BlizzardMap::getPathLengths() {
    auto a = getShortestPath(true, 0);
    auto b = getShortestPath(false, a.second + 1);
    auto c = getShortestPath(true, b.second + 1);
    return {a.first, a.first + b.first + c.first};
}

std::pair<unsigned int, unsigned int> BlizzardMap::getShortestPath(bool start_to_finish, unsigned int startd) {
    std::set<std::tuple<int, int, unsigned int>> visited;
    std::list<std::vector<std::tuple<int, int, unsigned int>>> queue;

    std::vector<std::tuple<int, int, unsigned int>> start = {std::make_tuple(start_to_finish ? -1 : m_height, start_to_finish ? 0 : m_width - 1, startd)};
    queue.push_back(start);
    int endx = start_to_finish ? m_height - 1 : 0;
    unsigned int endy = start_to_finish ? m_width - 1 : 0;

    while (!queue.empty()) {
        auto ps = queue.front(); queue.pop_front();
        auto p = ps.back();
        int x = std::get<0>(p);
        unsigned int d = std::get<2>(p) + 1;
        d %= wrap;
        int y = std::get<1>(p);
        auto moves = blizzards->getMoves(x,y,d);
        for(auto const &p2: moves) {
            if(visited.find(p2) == visited.end()) {
                auto ps_nw = ps;
                ps_nw.push_back(p2);
                if (std::get<1>(p2) == endy && std::get<0>(p2) == endx) {
                    return {ps_nw.size(), d};
                }
                visited.insert(p2);
                queue.push_back(ps_nw);
            }
        }
    }
    assert(false);
    return {0,0};
}