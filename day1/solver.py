import os
import sys

class Solver:
    def __init__(self):
        self.list1 = []
        self.list2 = []
        self.distance = 0
        self.frequencies = {}
    
    def parse_input(self, input_path):
        with open(input_path) as f:
            lines = f.readlines()
            for line in lines:
                self.list1.append(int(line[0:5]))
                self.list2.append(int(line[8:13]))

    def sort_lists(self):
        self.list1.sort()
        self.list2.sort()

    def calculate_distance(self):
        for a, b in zip(self.list1, self.list2):
            self.distance += abs(b - a)
        return self.distance

    def __get_frequency(self, n):
        freq = self.frequencies.get(n)
        if freq is not None:
            return freq
        else:
            occurrences = 0
            for value in self.list2:
                if value == n:
                    occurrences += 1
            self.frequencies[n] = occurrences
            return occurrences

    def similarity_score(self):
        sum = 0
        for value in self.list1:
            n = value * self.__get_frequency(value)
            sum += n
        return sum