#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// parses into expanded representation of memory
// empty blocks represented by -1
std::vector<int> parse(std::string path) {
    std::ifstream fileStream;
    fileStream.open(path);

    if (!fileStream) {
        std::cerr << "File not opened" << std::endl;
        exit(1);
    }

    std::vector<int> disk;
    char n;
    int id = 0;
    bool isOccBlock = true;
    int sizeOfDisk = 0;
    while(fileStream.get(n)) {
        if (isOccBlock) {
            for (int i = 0; i < n - '0'; i++) {
                disk.push_back(id);
            }
            id++;
            isOccBlock = false;
        }
        else {
            for (int i = 0; i < n - '0'; i++) {
                disk.push_back(-1);
            }
            isOccBlock = true;
        }
    }
    return disk;
}

void compactDisk(std::vector<int>& disk) {
    int i = 0;
    int j = disk.size() - 1;

    if (disk.size() == 0) {
        std::cerr << "Disk empty, cannot compact" << std::endl;
        exit(2);
    }
    // find first non-empty block from end
    // and first empty block from start
    while (disk[j] == -1) {
        j--;
    }
    while (disk[i] > -1) {
        i++;
    }
    while (i < j) {
        disk[i] = disk[j];
        disk[j] = -1;

        // find next non-empty block from end
        while(disk[j] == -1) {
            j--;
        }
        // find next empty block from start
        while (disk[i] > -1) {
            i++;
        }
    }
}

// works for both compacted and non-compacted disk
long long getChecksum(std::vector<int>& disk) {
    int diskSize = disk.size();
    long long sum = 0;
    for (int i = 0; i < diskSize; i++) {
        if (disk[i] > -1) {
            sum += i * disk[i];
        }
    }
    return sum;
}

int main() {
    std::string path = "input";
    std::vector<int> disk = parse(path);
    printf("parse done. disk size: %llu\n", disk.size());
    compactDisk(disk);
    printf("compact done. disk size: %llu\n", disk.size());

    // this took me an embarrassingly *long* amount of time to figure out
    // python dynamic int sizing would have saved me 😞
    long long checksum = getChecksum(disk);
    
    std::printf("checksum done\n");
    std::printf("%lld\n", checksum);
    return 0;
}