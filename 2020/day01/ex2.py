entries = []
while True:
    try:
        entries.append(int(input()))
    except EOFError:
        break

for i in range(len(entries)):
    for j in range(i+1, len(entries)):
        for k in range(j+1, len(entries)):
            if entries[i] + entries[j] + entries[k] == 2020:
                print(entries[i] * entries[j] * entries[k])
