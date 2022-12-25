#include <iostream>
#include <string>
#include <cassert>
#include "Day25.h"


std::vector<std::string> Day25::run(std::ifstream &input) {
    std::vector<std::string> out;
    
    long int total = 0;
    for(std::string read_line;getline(input, read_line);) {
        total += snafuToInt(read_line);
    }
    out.push_back(IntToSnafu(total));
    return out;
}


long int Day25::snafuToInt(std::string in) {
    long int mul = 1;
    long int res = 0;
    for(int i = (int)in.size() - 1; i >= 0; i--) {
        switch (in[i]) {
            case '0' : break;
            case '1': res += mul; break;
            case '2': res += (2*mul); break;
            case '-': res -= mul; break;
            case '=': res -= (2*mul); break;
            default: assert(false); break;
        }
        mul *= 5;
    }
    return res;
}

std::string Day25::IntToSnafu(long int in) {
    std::vector<int> res;
    while(in > 0) {
        res.push_back(in % 5);
        in /= 5;
    }
    unsigned int i = 0;
    while(i < res.size()) {
        if (res[i] > 4) {
            int rem = res[i] % 5;
            int div = res[i] / 5;
            if(res.size() - 1 == i ) {res.push_back(0);}
            res[i+1]+= div;
            res[i] = rem;
        }
        if (res[i] == 3) {
            res[i] = -2;
            if(res.size() - 1 == i ) {res.push_back(0);}
            res[i+1]++;
        }
        else if (res[i] == 4) {
            res[i] = -1;
            if(res.size() - 1 == i ) {res.push_back(0);}
            res[i+1]++;
        }
        i++;
    }

    std::string strres;
    for(int j = res.size() - 1; j >= 0; j--) {
        if(res[j] >= 0 && res [j] <= 2) strres.append(std::to_string(res[j]));
        else if(res[j] == -1) strres.append("-");
        else if(res[j] == -2) strres.append("=");
        else {assert(false);}
    }
    return strres;

}