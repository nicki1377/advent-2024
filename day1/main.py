from solver import Solver

s = Solver()

s.parse_input("input")
s.sort_lists()
distance = s.calculate_distance()
print(distance)