import sys

lines = [l.strip() for l in sys.stdin]
max_x = len(lines[0])
max_y = len(lines)
product = 1
for dx, dy in ((1, 1), (3, 1), (5, 1), (7, 1), (1, 2)):
    x, y = 0, 0
    nb_trees = 0
    while y < max_y - dy:
        y += dy
        x = (x + dx) % max_x
        if lines[y][x] == '#':
            nb_trees += 1
    product *= nb_trees

print(product)
