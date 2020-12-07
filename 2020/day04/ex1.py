import sys

lines = [l.strip() for l in sys.stdin]
req_fields = {'byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid', 'cid'}
passports = [[]]
for line in lines:
    if not line:
        passports[-1] = dict(k.split(':') for k in ' '.join(passports[-1]).split(' '))
        passports.append([])
        continue
    passports[-1].append(line)
if not passports[-1]:
    del passports[-1]
if isinstance(passports[-1], list):
    passports[-1] = dict(k.split(':') for k in ' '.join(passports[-1]).split(' '))

nb_valid = 0
for p in passports:
    keys = set(p.keys())
    missing_keys = req_fields - keys
    if missing_keys <= {'cid'}:
        nb_valid += 1
print(nb_valid)
