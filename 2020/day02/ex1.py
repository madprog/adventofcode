import re
import sys

nb_good = 0
for line in sys.stdin:
    m = re.match('(\d+)-(\d+) (\w): (.*)', line)
    if not m:
        raise Exception("No match for %r" % (line,))
    nb = len([i for i in m.group(4) if i == m.group(3)])
    if int(m.group(1)) <= nb <= int(m.group(2)):
        nb_good += 1
print(nb_good)
