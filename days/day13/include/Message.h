#pragma once
#include <variant>
#include <algorithm>
#include <json/json.h>


class Message {
public:
    Message() {}
    /** Input a pair */
    void parsePair(std::string line1, std::string line2);
    unsigned int getOrderedPairScore();
    unsigned int getTotalSortScore();
private:
    std::vector<bool> inOrder;
    Json::Value data;
};