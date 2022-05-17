#pragma once

#include <string>
#include <iostream>
#include "stringUtils.h"
#include "cpp11format.h"
#include "logger.h"

namespace SubShift {

// TODO: This should probably just be replaced by an in-built time type with proper initialization using sscanf (if it's not already done in std... probably is)
// I give up, cpp tm struct is terrible and I want nothing to do with it
class Timepoint {
public:
    int H;
    int M;
    int S;
    int MS;

private:
    bool valid = false;

    void addAndGetOverflow(int& val, int toAdd, int& overflow, int maxValue) {
        val += toAdd;
        if (val / maxValue > 0 ) {
            overflow = val - maxValue;
        } else {
            overflow = 0;
        }
        val = val % maxValue;
    }

public:
    Timepoint() = default;
    Timepoint(int H, int M, int S, int MS) : H(H), M(M), S(S), MS(MS) {}
    Timepoint(const std::string& other) {
        if ( 4 == sscanf(other.c_str(), "%d:%d:%d:%d", &this->H, &this->M, &this->S, &this->MS)
            || 4 == sscanf(other.c_str(), "%d:%d:%d,%d", &this->H, &this->M, &this->S, &this->MS))
        {
            valid = true;
        }
    }

    friend bool operator >=(const Timepoint& t1, const Timepoint& t2);

    // TODO: implement shiftBackwardsBy

    bool shiftForwardBy(const Timepoint& shiftBy) {
        int overflow = 0;
        addAndGetOverflow(MS, shiftBy.MS, overflow, 999);
        addAndGetOverflow(S, shiftBy.S + overflow / 1000, overflow, 59);
        addAndGetOverflow(M, shiftBy.M + overflow / 60, overflow, 59);
        addAndGetOverflow(H, shiftBy.H + overflow / 60, overflow, 24);

        if (overflow != 0) {
            LOG << "Timepoints are too big, this program can't handle moving past the 24h mark\n";
            return false;
        }

        return true;
    }

    bool isValid() { return this->valid; }

    std::string toString() {
        return string_format("%s:%s:%s,%s", StringUtils::intToPaddedString(H, 2).c_str(),
                                            StringUtils::intToPaddedString(M, 2).c_str(),
                                            StringUtils::intToPaddedString(S, 2).c_str(),
                                            StringUtils::intToPaddedString(MS, 3).c_str());
    }
};

// I really should add a >= operator as well.
bool operator >=(const Timepoint& t1, const Timepoint& t2) {
    return t1.H * 60 * 60 * 1000 + t1.M * 60 * 1000 + t1.S * 1000 + t1.MS
            >= t2.H * 60 * 60 * 1000 + t2.M * 60 * 1000 + t2.S * 1000 + t2.MS;
}

}