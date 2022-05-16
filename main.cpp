#include <iostream>
#include "CLI11.hpp"
#include <string>
#include "TimepointFormat.h"
#include <fstream>
#include "parser.h"

void runTests() {
    const std::string testValue = "1:22:04:333";

    SubShift::Timepoint testPoint(testValue);
    std::cout << testPoint.H << " "
                << testPoint.M << " "
                << testPoint.S << " "
                << testPoint.MS << std::endl;
}


int main(int argc, char** argv) {
    CLI::App app{"SubShift is a simple tool to shift .srt subtitle files in specific points."};

    std::string filename = "default";
    app.add_option("-i,--input", filename, "A help string");

    std::string output = "default";
    app.add_option("-o,--output", output, "Output file");

    std::string startPoint = "00:00:00:000";

    int shiftBySeconds = 0;
    app.add_option("-s,--shift", shiftBySeconds, "Shift by n seconds forward");

    CLI11_PARSE(app, argc, argv);

    std::ifstream infile(filename);
    std::ofstream outfile(output);
    std::string line;
    while (std::getline(infile, line)) {
        std::pair<SubShift::Timepoint, SubShift::Timepoint> parsedStartAndEndTimes = {};
        
        std::string outputLine = line;

        if (!SubShift::Parser::parseLine(line, parsedStartAndEndTimes)) {

            parsedStartAndEndTimes.first.shiftForwardBy(shiftBy)
            outputLine = SubShift::Parser::getTimePointsString()
        }

    }


    runTests();

    return 0;
}