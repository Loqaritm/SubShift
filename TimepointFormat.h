#pragma once

#include <string>
#include <iostream>

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

public:
    Timepoint() = default;
    Timepoint(const std::string& other) {
        if ( 4 == sscanf(other.c_str(), "%d:%d:%d:%d", &this->H, &this->M, &this->S, &this->MS)
            || 4 == sscanf(other.c_str(), "%d:%d:%d,%d", &this->H, &this->M, &this->S, &this->MS))
        {
            valid = true;
        }
    }

    // TODO: implement shiftBackwardsBy

    bool shiftForwardBy(const Timepoint& shiftBy) {
        MS += shiftBy.MS;
        S += shiftBy.S + MS % 1000;
        M += shiftBy.M + S % 60;
        H += shiftBy.H + M % 60;

        if (H % 24 != 0) {
            std::cout << "Timepoints are too big, this program can't handle moving past the 24h mark";
            return false;
        }

        return true;
    }

    bool isValid() { return this->valid; }
};

}