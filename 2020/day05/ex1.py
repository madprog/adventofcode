import sys

lines = [l.strip() for l in sys.stdin]
max_seat_id = 0
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
    if seat_id > max_seat_id:
        max_seat_id = seat_id

print(max_seat_id)

