#include <iostream>
#include "CLI11.hpp"
#include <string>
#include "TimepointFormat.h"
#include <fstream>
#include "parser.h"
#include "logger.h"

// void runTests() {
//     const std::string testValue = "1:22:04:333";

//     SubShift::Timepoint testPoint(testValue);
//     std::cout << testPoint.H << " "
//                 << testPoint.M << " "
//                 << testPoint.S << " "
//                 << testPoint.MS << std::endl;
// }


int main(int argc, char** argv) {
    CLI::App app{"SubShift is a simple tool to shift .srt subtitle files in specific points."};

    std::string filename = "default";
    app.add_option("-i,--input", filename, "A help string");

    std::string output = "default";
    app.add_option("-o,--output", output, "Output file");

    std::string startPointString = "00:00:00:000";
    app.add_option("-b,--begin", startPointString, "Starting point from which to begin the delay. Format: 0:04:20:000");

    // TODO: Add option to shift by a timestamp
    // TODO: Add support for format +10s -10s and so on
    int shiftBySeconds = 0;
    app.add_option("-s,--shift-by-seconds", shiftBySeconds, "Shift by n seconds forward");

    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Get more debug output");

    CLI11_PARSE(app, argc, argv);

    // Init values
    SubShift::Timepoint startPoint(startPointString);
    SubShift::Logger().instance().setupLogging(verbose);


    LOG << "start point string is: " << startPoint.toString() << "\n";

    std::ifstream infile(filename);
    std::ofstream outfile(output);
    std::string line;
    while (std::getline(infile, line)) {
        std::pair<SubShift::Timepoint, SubShift::Timepoint> parsedStartAndEndTimes = {};
        
        std::string outputLine = line;

        if (SubShift::Parser::parseLine(line, parsedStartAndEndTimes)) {
            if (parsedStartAndEndTimes.first >= startPoint) {
                parsedStartAndEndTimes.first.shiftForwardBy(SubShift::Timepoint(0,0,shiftBySeconds,0));
            }
            if (parsedStartAndEndTimes.second >= startPoint) {
                parsedStartAndEndTimes.second.shiftForwardBy(SubShift::Timepoint(0,0,shiftBySeconds,0));
            }
            outputLine = SubShift::Parser::getTimePointsString(parsedStartAndEndTimes);

            LOG << "Original line: " << line << "\nModified line: " << outputLine << "\n";
        }

        // TODO: Test if this won't add unnecessary endlines
        outfile << outputLine << std::endl;
    }

    return 0;
}