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
for passport in passports:
    keys = set(passport.keys())
    missing_keys = req_fields - keys
    if not missing_keys <= {'cid'}:
        continue

    if not (set(passport['byr']) <= set('0123456789')
            and 1920 <= int(passport['byr']) <= 2002):
        continue

    if not (set(passport['iyr']) <= set('0123456789')
            and 2010 <= int(passport['iyr']) <= 2020):
        continue

    if not (set(passport['eyr']) <= set('0123456789')
            and 2020 <= int(passport['eyr']) <= 2030):
        continue

    if not (set(passport['hgt'][:-2]) <= set('0123456789')
            and passport['hgt'][-2:] in ('cm', 'in')
            and (passport['hgt'].endswith('cm') and 150 <= int(passport['hgt'][:-2]) <= 193
                 or passport['hgt'].endswith('in') and 59 <= int(passport['hgt'][:-2]) <= 76)):
        continue

    if not (len(passport['hcl']) == 7
            and set(passport['hcl'][1:]) <= set('0123456789abcdef')
            and passport['hcl'][:1] == '#'):
        continue

    if not (passport['ecl'] in {'amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'}):
        continue

    if not (len(passport['pid']) == 9
            and set(passport['pid']) <= set('0123456789')):
        continue

    nb_valid += 1
print(nb_valid)
