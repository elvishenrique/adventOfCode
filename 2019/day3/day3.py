f = open('input', 'r')

w1 = f.readline()[:-1]
w2 = f.readline()

wire1 = w1.split(',')
wire2 = w2.split(',')

m = {}
x = 0
y = 0

def dist(a):
    return abs(a[0]) + abs(a[1])

s = 0

for inst in wire1:
    k = int(inst[1:])
    if inst[0] == 'R':
        for i in range(k):
            if (x+i, y) not in m:
                m[(x+i, y)] = s
            s = s + 1
        x = x + k
    elif inst[0] == 'L':
        for i in range(k):
            if (x-i,y) not in m:
                m[(x-i, y)] = s
            s = s + 1
        x = x - k
    elif inst[0] == 'U':
        for i in range(k):
            if (x,y+i) not in m:
                m[(x, y+i)] = s
            s = s + 1
        y = y + k
    else: #inst[0] == 'D'
        for i in range(k):
            if (x,y-i) not in m:
                m[(x, y-i)] = s
            s = s + 1
        y = y - k

n = {}

x = 0
y = 0
s = 0

for inst in wire2:
    k = int(inst[1:])
    if inst[0] == 'R':
        for i in range(k):
            if (x+i, y) not in n:
                n[(x+i,y)] = s
            s = s + 1
        x = x + k
    elif inst[0] == 'L':
        for i in range(k):
            if (x-i, y) not in n:
                n[(x-i,y)] = s
            s = s + 1
        x = x - k
    elif inst[0] == 'U':
        for i in range(k):
            if (x, y+i) not in n:
                n[(x,y+i)] = s
            s = s + 1
        y = y + k
    else: #inst[0] == 'D'
        for i in range(k):
            if (x, y-i) not in n:
                n[(x,y-i)] = s
            s = s + 1
        y = y - k

p = {}
for k in m:
    if k in n:
        p[k] = m[k] + n[k]

del p[(0,0)]
# print(m.keys())
print(dist(min(p.keys(), key=dist)))
print(min(p.values()))
#print(m)
#print(n)