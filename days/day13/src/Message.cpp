#include "Message.h"
#include <algorithm>
#include <numeric>

int comp(Json::Value &a, Json::Value &b) {
    if (a.isInt() && b.isInt()) {
        int ai = a.asInt();
        int bi = b.asInt();
        return ai < bi ? 1 : (ai > bi ? -1 : 0);
    }
    else if (a.isInt()) {
        if (b.size() == 0) {return -1;}
        int c  = comp(a,b[0]);
        if (c != 0) {return c;}
        else {return (b.size() == 1) ? 0 : 1;}
    }
    else if (b.isInt()) {
        if (a.size() == 0) {return 1;}
        int c  = comp(a[0],b);
        if (c != 0) {return c;}
        else {return (a.size() == 1) ? 0 : -1;}
    }
    else {
        for (unsigned int i = 0; i < a.size(); i++) {
            if (i >= b.size()) {
                return -1;
            }
            int c = comp(a[i], b[i]);
            if (c != 0) {return c;}
        }
        return (b.size() == a.size()) ? 0 : 1;
    }
}

void Message::parsePair(std::string line1, std::string line2) {
    Json::Reader reader;
    Json::Value obj1,obj2;
    reader.parse(line1 ,obj1);
    reader.parse(line2 ,obj2);
    inOrder.push_back(comp(obj1, obj2) >= 0);
    data.append(obj1);
    data.append(obj2);
}


unsigned int Message::getOrderedPairScore() {
    unsigned int ret = 0;
    for (unsigned int i = 0; i < inOrder.size(); i++) {
        ret += (i + 1) * inOrder[i];
    }   
    return ret;
}

unsigned int Message::getTotalSortScore() {
    Json::Value s(data);

    Json::Value d;
    d.append(2);
    Json::Value d2;
    d2.append(d);
    s.append(d2);

    Json::Value e;
    e.append(6);
    Json::Value e2;
    e2.append(e);
    s.append(e2);

    std::vector<unsigned int> ivec(s.size());
    std::iota(ivec.begin(), ivec.end(), 0); // ivec will become: [0..99]
    std::sort(ivec.begin(), ivec.end(),  [&](unsigned int &a, unsigned int &b) {return comp(s[a],s[b]) == 1; });
    auto idx1 = (std::find(ivec.begin(), ivec.end(),  s.size() - 2) - ivec.begin()) + 1;
    auto idx2 = (std::find(ivec.begin(), ivec.end(),  s.size() - 1) - ivec.begin()) + 1;
    return idx1 * idx2;
}