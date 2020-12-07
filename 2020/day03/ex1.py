import sys

lines = [l.strip() for l in sys.stdin]
max_x = len(lines[0])
nb_trees = 0
for y in range(len(lines)):
    x = (3 * y) % max_x
    if lines[y][x] == '#':
        nb_trees += 1
print(nb_trees)
