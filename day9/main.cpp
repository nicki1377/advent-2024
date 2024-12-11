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

void printDisk(std::vector<int>& disk) {
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] != -1) {
            printf(" ");
        }
        printf("%d ", disk[i]);
    }
    printf("\n");
}

int getSpaceSize(std::vector<int>& disk, int startIndex) {
    if (startIndex == -1) {
        return -1;
    }

    int size = 0;
    int end = disk.size();
    int i = startIndex;
    while (i < end && disk[i] == -1) {
        size++;
        i++;
    }
    return size;
}

int getFileSize(std::vector<int>& disk, int lastIndex) {
    int val = disk[lastIndex];

    int size = 0;
    int i = lastIndex;
    while (i >= 0 && disk[i] == val) {
        size++;
        i--;
    }
    return size;
}

int findNextSpace(std::vector<int>& disk, int index) {
    int end = disk.size();
    while (index < end && disk[index] != -1) {
        index++;
    }
    if (index == end) {
        return -1;
    }
    return index;
}

int findPrevFile(std::vector<int>& disk, int index) {
    while (index >= 0 && disk[index] == -1) {
        index--;
    }
    return index;
}

void compactDisk(std::vector<int>& disk) {
    if (disk.size() == 0) {
        std::cerr << "Disk empty, cannot compact" << std::endl;
        exit(2);
    }

    int i = findNextSpace(disk, 0);
    int j = findPrevFile(disk, disk.size() - 1);
    
    while (i < j) {
        disk[i] = disk[j];
        disk[j] = -1;

        j = findPrevFile(disk, j);
        i = findNextSpace(disk, i);
    }
}

void compactByFile(std::vector<int>& disk) {
    if (disk.size() == 0) {
        std::cerr << "Disk empty, cannot compact" << std::endl;
        exit(2);
    }

    // i will represent first block of empty space
    // j will represent last block of file
    int j = findPrevFile(disk, disk.size() - 1);
    int fileSize = getFileSize(disk, j);
    int currentFile = disk[j];

    while (j >= 0) {
        int i = findNextSpace(disk, 0);
        int spaceSize = getSpaceSize(disk, i);

        // findNextSpace returns -1 when there is no next space
        // spaceSize will still run
        while (spaceSize < fileSize && i != -1 && i < j) {
            i = findNextSpace(disk, i + spaceSize);
            spaceSize = getSpaceSize(disk, i);
        }

        // only perform moving operations if there is a valid space
        // otherwise skip this step altogether
        if (spaceSize >= fileSize && i < j) {
            for (int k = 0; k < fileSize; k++) {
                disk[i + k] = disk[j - k];
                disk[j - k] = -1;
            }
        }

        j = findPrevFile(disk, j - fileSize);
        fileSize = getFileSize(disk, j);
        currentFile--;
        // ensure files that have already been moved are not moved again
        while (j >= 0 && disk[j] != currentFile) {
            j = findPrevFile(disk, j - fileSize);
            fileSize = getFileSize(disk, j);
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
    //printDisk(disk);

    // part 1
    // compactDisk(disk);
    // part 2
    compactByFile(disk);
    printf("compact done. disk size: %llu\n", disk.size());

    // this took me an embarrassingly *long* amount of time to figure out
    // python dynamic int sizing would have saved me 😞
    long long checksum = getChecksum(disk);

    //printDisk(disk);

    std::printf("checksum done\n");
    std::printf("%lld\n", checksum);
    return 0;
}