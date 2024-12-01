import os
import sys

class Solver:
    def __init__(self):
        self.list1 = []
        self.list2 = []
        self.distance = 0
    
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