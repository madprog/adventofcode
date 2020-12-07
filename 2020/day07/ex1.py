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
        bags_tree[bag_id].append(bags_type)

nb_bags_shiny_gold = 0
for bag_id in bags_tree:
    stack = [bag_id]
    while stack:
        b_id = stack.pop()
        if 'shiny gold bags' in bags_tree[b_id]:
            nb_bags_shiny_gold += 1
            break
        stack.extend(bags_tree[b_id])

print(nb_bags_shiny_gold)
