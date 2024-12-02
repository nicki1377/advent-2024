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

bool isSafe(std::vector<int> report) {
    int numLevels = report.size();
    bool reportDescending;

    if (numLevels > 1 && report[1] < report[0]) {
        reportDescending = true;
    }
    else {
        reportDescending = false;
    }

    for (int j = 1; j < numLevels; j++) {
        int diff = abs(report[j] - report[j - 1]);
        bool levelDescending = report[j] < report[j - 1];
        if (levelDescending != reportDescending || diff > 3 || diff < 1) {
            return false;
        }
    }

    return true;
}

int countSafe(std::vector<std::vector<int>>& reports) {
    int numSafe = 0;
    int numReports = reports.size();
    for (int i = 0; i < numReports; i++) {
        if (isSafe(reports[i])) {
            numSafe++;
        }
    }
    return numSafe;
}

int countSafeDampened(std::vector<std::vector<int>>& reports) {
    int numSafe = 0;
    int numReports = reports.size();
    for (int i = 0; i < numReports; i++) {
        int numLevels = reports[i].size();
        // 'problem dampener'-
        // try it with one level removed
        for (int removeIndex = 0; removeIndex < numLevels; removeIndex++) {
            
            std::vector<int> report(reports[i]);
            report.erase(report.begin() + removeIndex);

            if (isSafe(report)) {
                numSafe++;
                break;
            }
        }
    }
    return numSafe;
}

int main() {
    std::string path = "input";
    std::vector<std::vector<int>> reports = parse(path);
    // pt 1
    // int safeReports = countSafe(reports);
    // pt 2
    int safeReports = countSafeDampened(reports);
    std::printf("%d\n", safeReports);

    return 0;
}