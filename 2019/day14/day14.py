f = open('input', 'r')

lines = f.read().splitlines()

prim = set()
prim.add('ORE')
fact = {}
for line in lines:
    reaction = line.split(' => ')
    ings = reaction[0].split(', ')
    prod = reaction[1].split(' ')
    fact[prod[1]] = [int(prod[0]), {}]
    for ing in ings:
        comp = ing.split(' ')
        fact[prod[1]][1][comp[1]] = int(comp[0])
        if comp[1] == 'ORE':
            prim.add(prod[1])

def brk(sub, q, reaction, waste):
    if q < reaction[0]:
        return (0, q)
    mul = 1
    while q > mul * reaction[0]:
        mul += 1

    if not q % reaction[0] == 0:
        mul -= 1

    return (mul, q % reaction[0])

#         results     waste
# ore     10
# a                   3
# b
# c
# d
# e
# fuel

def findores(sub, q, react, results, waste):
    if q == 0:
        return

    if sub == 'ORE':
        if 'ORE' not in results:
            results['ORE'] = 0
        results['ORE'] += q
        return

    reaction = react[sub]
    if sub in waste:
        q -= waste[sub]
        del waste[sub]

    r = (-q) % reaction[0] # how much is left of sub after breaking what we can
    mul = q // reaction[0]
    if q % reaction[0] > 0:
        mul += 1
    for comp in reaction[1]:
        findores(comp, mul * reaction[1][comp], react, results, waste)
    if r > 0:
        waste[sub] = r

results = {'ORE': 0}
waste = {}
findores('FUEL', 1, fact, results, waste)
print(results['ORE'])
trillion = 10**12

fuel = 1
while results['ORE'] < trillion:
    results = {'ORE': 0}
    waste = {}
    fuel *= 2
    findores('FUEL', fuel, fact, results, waste)

upper = fuel
lower = 1
while upper - lower > 1:
    results = {'ORE': 0}
    waste = {}
    fuel = lower + (upper - lower) // 2
    findores('FUEL', fuel, fact, results, waste)
    if results['ORE'] > trillion:
        upper = fuel
    else:
        lower = fuel

print(fuel - 1)