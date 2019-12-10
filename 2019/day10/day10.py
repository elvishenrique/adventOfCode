import math

f = open('input', 'r')

m = f.read().splitlines()

def angle(dest):
    global vap
    dx = vap[0] - dest[0]
    dy = vap[1] - dest[1]
    res = math.atan2(dy, dx)
    if res < math.pi / 2:
        return res + 2 * math.pi
    else:
        return res

def blocked(asts, a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]

    if dx == 0 and dy == 0:
        return True

    div = math.gcd(dx, dy)
    sx = dx//div
    sy = dy//div
    it = 1
    while not (sx*it == dx and sy*it == dy):
        if (b[0] + sx*it, b[1] + sy*it) in asts:
            return True
        it += 1
    return False

asts = {}
for i in range(len(m)):
    for j in range(len(m[i])):
        if m[i][j] == '#':
            asts[(j,i)] = []

for ast in asts:
    for vis in asts:
        if not blocked(asts, ast, vis):
            asts[ast] += [vis]

n = 0
for ast in asts:
    if len(asts[ast]) > n:
        n = len(asts[ast])
        vap = ast

res = sorted(asts[vap], key=angle)
print(res[199])