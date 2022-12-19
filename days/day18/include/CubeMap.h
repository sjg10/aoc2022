#pragma once
#include <string>
#include <set>
#include <tuple>

using Face = std::tuple<int,int,int>;
using Cube = std::tuple<int,int,int>;

class CubeMap {
public:
    CubeMap() {};
    void addPoint(std::string &point);
    unsigned int getFaces() { return m_ext_faces.size();};
    unsigned int getExteriorArea();
private:
    void addFace(Face f);
    std::set<Face> m_ext_faces;
    std::set<Face> m_int_faces;
    std::set<Cube> m_points;
};