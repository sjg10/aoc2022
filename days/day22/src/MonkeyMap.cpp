#include "MonkeyMap.h"
#include <cassert>
#include <iostream>

void MonkeyMap::loadLine(std::string const &line) {
    std::vector<Location> row;
    unsigned int rowstart = 0;
    for(unsigned int i = 0; i < line.size(); i++) {
        switch (line[i]) {
            case ' ': row.push_back(Location::EMPTY);rowstart++;break;
            case '.': row.push_back(Location::OPEN);break;
            case '#': row.push_back(Location::ROCK);break;
        }
    }
    m_rowstart.push_back(rowstart);
    m_rowend.push_back(line.size() - 1);
    m_map.push_back(row);
}

MonkeyMap::MonkeyMap(std::istream &in) {
    std::string readline;
    for(; std::getline(in, readline) && readline != "";) {
        loadLine(readline);
    }
    std::getline(in, readline);
    std::string dist = "";
    for(unsigned int i = 0; i < readline.size(); i++) {
        if(readline[i] == 'R')  {
            m_distances.push_back(std::stoul(dist)); dist = "";
            m_turns.push_back( Direction::RIGHT);
        }
        else if(readline[i] == 'L') {
            m_distances.push_back(std::stoul(dist)); dist = "";
            m_turns.push_back( Direction::LEFT);
        }
        else {
            dist.push_back(readline[i]);
        }
        
    }
    m_distances.push_back(std::stoul(dist)); dist = "";
    m_width = 0;
    for (auto const &r: m_map) {
        if(r.size() > m_width) { m_width = r.size();}
    }
/*
    for(unsigned int col = 0; col < m_width; col++) {
        unsigned int row = 0;
        while (m_map[row].size() < (col + 1)) {row++;} // find row wide enough
        m_colstart.push_back(row);
        while (row < m_map.size() && m_map[row].size() < (col + 1)) {row++;} // find row wide enough
        m_colend.push_back(m_colstart.back());
        for (;row < m_map[row].size(); row++) {
            if (m_map[row][col] == Location::EMPTY) break;
            m_colend.back()++;
        }
    }
*/
    for(unsigned int col = 0; col < m_width; col++) {
    for(unsigned int row = 0; row < m_map.size() - 1; row++) {
        if(m_colstart.size() <= col) {
            if(m_map[row].size() > col && m_map[row][col] !=Location::EMPTY ) {m_colstart.push_back(row);}
        }
        if (m_colstart.size() > col) {
            if(m_map[row + 1].size() <= col || m_map[row + 1][col] ==Location::EMPTY ) {
                m_colend.push_back(row);
                break;
                }
        }
        if (m_colend.size() < col) { m_colend.push_back(m_map.size() - 1);}
    }
    }

}


void MonkeyMap::wrapDown(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size) {
    if(cube_face_size == 0) {row = m_colstart[col];}
    else if (cube_face_size == 4) {
        //unsigned int facerow = row % cube_face_size;
        unsigned int facecol = col % cube_face_size;
        if( col < cube_face_size) { //face 2 to face 5
            dir =  Direction::UP;
            row = m_map.size() - 1;
            col = ((3 * cube_face_size) - 1) - facecol;
        } else if (col < 2 * cube_face_size) { //face 3 to face 5
            dir =  Direction::RIGHT;
            col = (2 * cube_face_size);
            row = (2 * cube_face_size) + ((cube_face_size - 1) - facecol);
        } else if (col < 3 * cube_face_size) { //face 5 to face 2
            dir =  Direction::UP;
            row = (2 * cube_face_size) - 1;
            col = (cube_face_size - 1) - facecol;
        } else { //face 6 to face 2
            dir =  Direction::RIGHT;
            col = 0;
            row = cube_face_size + ((cube_face_size - 1) - facecol);
        }
    }
    else {
        //unsigned int facerow = row % cube_face_size;
        unsigned int facecol = col % cube_face_size;
        if( col < cube_face_size) { //face 6 to 2
            dir =  Direction::DOWN;
            row = 0;
            col = 2* cube_face_size + facecol;
        } else if (col < 2 * cube_face_size) { //face 5 to face 6
            dir =  Direction::LEFT;
            col = cube_face_size - 1;
            row = (3 * cube_face_size) + facecol;
        } else { //face 2 to face 3
            dir =  Direction::LEFT;
            col = (2 * cube_face_size) - 1;;
            row = cube_face_size + facecol;
        }
    }
}

void MonkeyMap::wrapUp(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size) {
    if(cube_face_size == 0) { row = m_colend[col];}
    else if (cube_face_size == 4) {
        //unsigned int facerow = row % cube_face_size;
        unsigned int facecol = col % cube_face_size;
        if( col < cube_face_size) { //face 2 to face 1
            dir =  Direction::DOWN;
            row = 0;
            col = (2*cube_face_size) + ((cube_face_size - 1) - facecol);
        } else if (col < 2 * cube_face_size) { //face 3 to face 1
            dir =  Direction::RIGHT;
            col = (2 * cube_face_size);
            row = facecol;
        } else if (col < 3 * cube_face_size) { //face 1 to face 2
            dir =  Direction::DOWN;
            row = cube_face_size;
            col = (cube_face_size - 1) - facecol;
        } else { //face 6 to face 4
            dir =  Direction::LEFT;
            col = (3 * cube_face_size) - 1;
            row = cube_face_size + ((cube_face_size - 1) - facecol);
        }
    }
    else {
        //unsigned int facerow = row % cube_face_size;
        unsigned int facecol = col % cube_face_size;
        if( col < cube_face_size) { //face 4 to face 3
            dir =  Direction::RIGHT;
            row = cube_face_size + facecol;
            col = cube_face_size;
        } else if (col < 2 * cube_face_size) { //face 1 to face 6
            dir =  Direction::RIGHT;
            col = 0;
            row = (3 * cube_face_size) + facecol;
        } else { //face 2 to face 6
            dir =  Direction::UP;
            col = facecol;
            row = cube_face_size * 4 - 1;
        }
    }
}

void MonkeyMap::wrapLeft(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size) {
    if(cube_face_size == 0) {col = m_rowend[row];}
    else if (cube_face_size == 4) {
        unsigned int facerow = row % cube_face_size;
        //unsigned int facecol = col % cube_face_size;
        if( row < cube_face_size) { //face 1 to face 3
            dir = Direction::DOWN;
            row = cube_face_size;
            col = cube_face_size + facerow;
        } else if (row < 2 * cube_face_size) { //face 2 to face 6
            dir = Direction::UP;
            row = m_map.size() - 1;
            col = (m_width - 1) - (facerow);
        }
        else { //face 5 to face 3
            dir = Direction::UP;
            row = (cube_face_size * 2) - 1;
            col = ((cube_face_size * 2) - 1) - facerow;
        }
    }
    else {
        unsigned int facerow = row % cube_face_size;
        //unsigned int facecol = col % cube_face_size;
        if( row < cube_face_size) { // 1 to 4
            dir = Direction::RIGHT;
            row = (cube_face_size * 2) + ((cube_face_size - 1) - facerow);
            col = 0;

        } else if (row < 2 * cube_face_size) { //face 3 to 4
            dir = Direction::DOWN;
            row = (cube_face_size * 2);
            col = facerow;
        }
        else if (row < 3 * cube_face_size) { //face 4 to 1
            dir = Direction::RIGHT;
            row = (cube_face_size -1) - facerow;
            col = cube_face_size;
        }
        else { // face 6 to 1
            dir = Direction::DOWN;
            row = 0;
            col = cube_face_size + facerow;
        }
    }
    

}

void MonkeyMap::wrapRight(unsigned int &row, unsigned int &col, Direction &dir, unsigned int cube_face_size) {
    if(cube_face_size == 0) {col = m_rowstart[row];}
    else if (cube_face_size == 4) {
        unsigned int facerow = row % cube_face_size;
        //unsigned int facecol = col % cube_face_size;
        if( row < cube_face_size) { //face 1 to face 6
            dir = Direction::LEFT;
            row = (m_map.size() - 1) - facerow;
            col = m_width - 1;
        } else if (row < 2 * cube_face_size) { //face 4 to face 6
            dir = Direction::DOWN;
            row = cube_face_size * 2;
            col = (m_width - 1) - (facerow);
        }
        else { //face 6 to face 1
            dir = Direction::LEFT;
            row = (cube_face_size - 1) - facerow;
            col = (cube_face_size * 2) - 1;

        }
    }
    else {
        unsigned int facerow = row % cube_face_size;
        //unsigned int facecol = col % cube_face_size;
        if( row < cube_face_size) { // 2 to 5
            dir = Direction::LEFT;
            col = cube_face_size * 2 - 1;
            row = cube_face_size * 2  + ((cube_face_size - 1) - facerow);

        } else if (row < 2 * cube_face_size) { //face 3 to 2
            dir = Direction::UP;
            row = cube_face_size - 1;
            col = facerow + (2 * cube_face_size);
        }
        else if (row < 3 * cube_face_size) { //face 5 to 2
            dir = Direction::LEFT;
            row = (cube_face_size - 1) - facerow;
            col = (cube_face_size * 3) - 1;
        }
        else { // face 6 to 5
            dir = Direction::UP;
            row = (cube_face_size * 3) - 1;
            col = cube_face_size +  facerow;
        }
    }
}

unsigned int MonkeyMap::getScore(unsigned int cube_face_size) {
    unsigned int row = 0;
    unsigned int col = m_rowstart[0];
    Direction dir = Direction::RIGHT;
    for(unsigned int s = 0 ;s < m_distances.size(); s++) {
        for(unsigned int i = 0 ;i < m_distances[s]; i++) {
            unsigned int newrow = row;
            unsigned int newcol = col;
            Direction newdir = dir;
            switch (dir) {
                case Direction::DOWN: 
                    if((row + 1) > m_map.size() || (row + 1) > m_colend[col]) {
                        wrapDown(newrow, newcol, newdir, cube_face_size);
                    } else {newrow++;}
                    break;
                case Direction::UP: 
                    if(row == 0 || (row - 1) < m_colstart[col]) {
                        wrapUp(newrow, newcol, newdir, cube_face_size);
                    } else {newrow--;}
                    break;
                case Direction::LEFT: 
                    if(col == 0 || (col - 1) < m_rowstart[row]) {
                        wrapLeft(newrow, newcol, newdir, cube_face_size);
                    } else {newcol--;}
                    break;
                case Direction::RIGHT: 
                    if((col + 1) >= m_width || (col + 1) > m_rowend[row]) {
                        wrapRight(newrow, newcol, newdir, cube_face_size);
                    } else {newcol++;}
                    break;
            };
            if (m_map[newrow][newcol] == Location::ROCK) {break;}
            if(m_map[newrow][newcol] != Location::OPEN) {
                assert(false);
            }
            row = newrow; col=newcol; dir = newdir;
        }
        if (s < m_turns.size()) {
            if(m_turns[s] == Direction::RIGHT) {
                switch (dir) {
                    case Direction::RIGHT:  dir = Direction::DOWN; break;
                    case Direction::LEFT:  dir = Direction::UP; break;
                    case Direction::UP:  dir = Direction::RIGHT; break;
                    case Direction::DOWN:  dir = Direction::LEFT; break;
                }
            }else{
                switch (dir) {
                    case Direction::RIGHT:  dir = Direction::UP; break;
                    case Direction::LEFT:  dir = Direction::DOWN; break;
                    case Direction::UP:  dir = Direction::LEFT; break;
                    case Direction::DOWN:  dir = Direction::RIGHT; break;
                }
            }
        }
    }
    unsigned int dirval = 0;
    switch (dir) {
        case Direction::RIGHT:  dirval = 0; break;
        case Direction::DOWN:  dirval = 1; break;
        case Direction::LEFT:  dirval = 2; break;
        case Direction::UP:  dirval = 3; break;
    }
    return (1000 * (row + 1)) + (4 * (col+1)) + dirval;
}
