import re
import sys

nb_good = 0
for line in sys.stdin:
    m = re.match('(\d+)-(\d+) (\w): (.*)', line)
    if not m:
        raise Exception("No match for %r" % (line,))
    pos1 = int(m.group(1)) - 1
    pos2 = int(m.group(2)) - 1
    charpos1 = m.group(4)[pos1:pos1+1]
    charpos2 = m.group(4)[pos2:pos2+1]
    if ((charpos1 == m.group(3) and charpos2 != m.group(3))
        or (charpos1 != m.group(3) and charpos2 == m.group(3))):
        nb_good += 1
print(nb_good)
