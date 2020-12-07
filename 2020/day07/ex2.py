import sys

bags_tree = {}
for line in sys.stdin:
    line = line.strip()
    bag_id, contents = line.strip('.').split(" contain ")
    bags_tree[bag_id] = []
    for c in contents.split(', '):
        if c == 'no other bags':
            continue
        nb_bags, bags_type = c.split(' ', 1)
        if nb_bags == '1':
            bags_type += 's'
        bags_tree[bag_id].append((int(nb_bags), bags_type))

def nb_bags(bag_id, indent=''):
    total = 0
    for nb, bid in bags_tree[bag_id]:
        total += nb * (nb_bags(bid, indent + '  ') + 1)
    return total

print(nb_bags('shiny gold bags'))
