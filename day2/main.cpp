#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> parse(std::string path) {
    std::ifstream fileStream;
    fileStream.open(path);
    std::vector<std::vector<int>> report;

    std::string line;
    while (std::getline(fileStream, line)) {
        std::vector<int> level;
        std::stringstream str;
        str << line;
        int n;
        while (str >> n) {
            level.push_back(n);
        }
        report.push_back(level);
    }
    return report;
}

int countSafe(std::vector<std::vector<int>>& reports) {
    int numSafe = 0;
    int numReports = reports.size();
    for (int i = 0; i < numReports; i++) {
        int numLevels = reports[i].size();
        bool isSafe = true;
        bool reportDescending;

        if (numLevels > 1 && reports[i][1] < reports[i][0]) {
            reportDescending = true;
        }
        else {
            reportDescending = false;
        }

        for (int j = 1; j < numLevels; j++) {
            int diff = abs(reports[i][j] - reports[i][j - 1]);
            bool levelDescending = reports[i][j] < reports[i][j - 1];
            if (levelDescending != reportDescending || diff > 3 || diff < 1) {
                isSafe = false;
            }
        }

        if (isSafe) {
            numSafe++;
        }
    }
    return numSafe;
}

int main() {
    std::string path = "input";
    std::vector<std::vector<int>> reports = parse(path);
    int safeReports = countSafe(reports);
    std::printf("%d\n", safeReports);

    return 0;
}