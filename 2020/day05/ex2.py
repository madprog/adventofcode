import sys

lines = [l.strip() for l in sys.stdin]
found_seats = set()
for line in lines:
    min_row = 0
    max_row = 127
    min_col = 0
    max_col = 7

    for c in line:
        if c == 'F':
            max_row = int(min_row + (max_row - min_row) / 2)
        elif c == 'B':
            min_row = int(min_row + (max_row - min_row + 1) / 2)
        elif c == 'L':
            max_col = int(min_col + (max_col - min_col) / 2)
        elif c == 'R':
            min_col = int(min_col + (max_col - min_col + 1) / 2)

    seat_id = min_row * 8 + min_col
    found_seats.add(seat_id)

for row in range(127):
    for col in range(7):
        seat_id = row * 8 + col
        if (seat_id not in found_seats
            and seat_id - 1 in found_seats
            and seat_id + 1 in found_seats):
            print(seat_id)
