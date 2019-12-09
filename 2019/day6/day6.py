from collections import deque
f = open('input', 'r')

lines = f.read().splitlines()

class node:
    def __init__(self, n):
        self.name = n
        self.children = []
        self.parent = None

    def addchild(self, child):
        self.children += [child]
        child.parent = self

    def setlevel(self, i):
        self.level = i

def dfs(n, level):
    n.setlevel(level)
    for child in n.children:
        dfs(child, level+1)

def bfs(src, dest):
    cur = (src, 0)
    d = deque()
    v = set()
    v.add(cur[0].name)
    while not cur[0] == dest:
        if (not cur[0].parent == None) and (cur[0].parent.name not in v):
            d.append((cur[0].parent, cur[1]+1))
            v.add(cur[0].parent.name)
        for child in cur[0].children:
            if child.name not in v:
                d.append((child, cur[1]+1))
                v.add(child.name)
        cur = d.popleft()
    return cur[1]

nodes = {}

for line in lines:
    orbit = line.split(')')
    if not orbit[0] in nodes:
        nodes[orbit[0]] = node(orbit[0])
    if not orbit[1] in nodes:
        nodes[orbit[1]] = node(orbit[1])
    nodes[orbit[0]].addchild(nodes[orbit[1]])

dfs(nodes['COM'], 0)
res = 0
for name in nodes:
    res += nodes[name].level

print(res)
print(bfs(nodes['YOU'], nodes['SAN'])-2)