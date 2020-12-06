import sys

groups = [[]]
for line in sys.stdin:
    line = line.strip()
    if not line:
        groups.append([])
    else:
        groups[-1].append(line)
if not groups[-1]:
    del groups[-1]

nb_answers_sum = 0
for group in groups:
    answers = set(group[0])
    for answer in group[1:]:
        answers.intersection_update(answer)
    nb_answers_sum += len(answers)
print(nb_answers_sum)
