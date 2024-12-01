from solver import Solver

s = Solver()

s.parse_input("input")


# Part 1 solution
# s.sort_lists()
# distance = s.calculate_distance()
# print(distance)


# Part 2 solution
result = s.similarity_score()
print(result)