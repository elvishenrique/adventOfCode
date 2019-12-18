from collections import deque

f = open('input', 'r')

mem = f.read().split(',')

def complete(tape, index):
    if index >= len(tape):
        fill =  [0] * (index + 1 - len(tape))
        tape += fill

def getparam(tape, pos, rel):
    instr = tape[pos][-1]
    param1 = ['3', '4', '9']

    index = -1
    if len(tape[pos]) < 3 or tape[pos][-3] == '0': #position
        index = int(tape[pos + 1])
    elif tape[pos][-3] == '1': #immediate
        x = tape[pos + 1]
    elif tape[pos][-3] == '2': #relative
        index = int(tape[pos + 1]) + rel

    if index >= 0:
        complete(tape, index)
        x = tape[index]

    if instr in param1:
        return (x,0)

    index = -1
    if len(tape[pos]) < 4 or tape[pos][-4] == '0': #position
        index = int(tape[pos + 2])
    elif tape[pos][-4] == '1': #immediate
        y = tape[pos + 2]
    elif tape[pos][-4] == '2': #relative
        index = int(tape[pos + 2]) + rel

    if index >= 0:
        complete(tape, index)
        y = tape[index]

    return (x,y)

def decision(pos, visited):
    global area
    global stack
    north = (0, 1)
    south = (0, -1)
    west = (-1, 0)
    east = (1, 0)
    npos = (pos[0], pos[1] + 1)
    spos = (pos[0], pos[1] - 1)
    wpos = (pos[0] - 1, pos[1])
    epos = (pos[0] + 1, pos[1])

    # first explore new places
    if npos not in area:
        stack.append(south)
        return north
    if spos not in area:
        stack.append(north)
        return south
    if wpos not in area:
        stack.append(east)
        return west
    if epos not in area:
        stack.append(west)
        return east

    # then try not visited places
    if npos not in visited:
        stack.append(south)
        return north
    if spos not in visited:
        stack.append(north)
        return south
    if wpos not in visited:
        stack.append(east)
        return west
    if epos not in visited:
        stack.append(west)
        return east

    if len(stack) == 0 and pos == (0, 0):
        return (0, 0)

    return stack.pop()

stack = deque()
area = {(0, 0): 1}

def proc(tape, inp):
    dpad = {(0, 1): 1, (0, -1): 2, (-1, 0): 3, (1, 0): 4}
    pos = 0
    rel = 0
    droid = (0, 0)
    direction = (0, 0)
    oxygen = None
    vis = set()
    vis.add((0, 0))
    global area
    while not tape[pos] == '99':
        if tape[pos][-1] == '1': #add
            p = getparam(tape, pos, rel)
            add = int(p[0]) + int(p[1])

            if len(tape[pos]) < 5 or tape[pos][-5] == '0': #position
                index = int(tape[pos + 3])
            elif tape[pos][-5] == '2': #relative
                index = int(tape[pos + 3]) + rel

            complete(tape, index)
            tape[index] = str(add)
            pos += 4
        elif tape[pos][-1] == '2': #mul
            p = getparam(tape, pos, rel)
            prod = int(p[0]) * int(p[1])

            if len(tape[pos]) < 5 or tape[pos][-5] == '0': #position
                index = int(tape[pos + 3])
            elif tape[pos][-5] == '2': #relative
                index = int(tape[pos + 3]) + rel

            complete(tape, index)
            tape[index] = str(prod)
            pos += 4
        elif tape[pos][-1] == '3': #input
            if len(tape[pos]) < 3 or tape[pos][-3] == '0': #position
                i = int(tape[pos + 1])
            elif tape[pos][-3] == '2': #relative
                i = int(tape[pos + 1]) + rel
            complete(tape, i)
            direction = decision(droid, vis)
            if direction == (0, 0):
                return oxygen
            tape[i] = dpad[direction]
            pos += 2
        elif tape[pos][-1] == '4': #output
            o = getparam(tape, pos, rel)
            newdroid = (droid[0] + direction[0], droid[1] + direction[1])
            vis.add(newdroid)
            if newdroid not in area:
                area[newdroid] = int(o[0])
            if o[0] == '0':
                stack.pop()
            else:
                droid = newdroid
            if o[0] == '2':
                if inp == 1:
                    print('huge success')
                    return droid
                else:
                    oxygen = droid
            pos += 2
        elif tape[pos][-1] == '5': #jtrue
            p = getparam(tape, pos, rel)
            if not int(p[0]) == 0:
                pos = int(p[1])
            else:
                pos +=  3
        elif tape[pos][-1] == '6': #jfalse
            p = getparam(tape, pos, rel)
            if int(p[0]) == 0:
                pos = int(p[1])
            else:
                pos += 3
        elif tape[pos][-1] == '7': #lessthan
            p = getparam(tape, pos, rel)

            if len(tape[pos]) < 5 or tape[pos][-5] == '0': #position
                index = int(tape[pos + 3])
            elif tape[pos][-5] == '2': #relative
                index = int(tape[pos + 3]) + rel

            complete(tape, index)
            if int(p[0]) < int(p[1]):
                tape[index] = '1'
            else:
                tape[index] = '0'

            pos += 4
        elif tape[pos][-1] == '8': #equals
            p = getparam(tape, pos, rel)

            if len(tape[pos]) < 5 or tape[pos][-5] == '0': #position
                index = int(tape[pos + 3])
            elif tape[pos][-5] == '2': #relative
                index = int(tape[pos + 3]) + rel

            complete(tape, index)
            if int(p[0]) == int(p[1]):
                tape[index] = '1'
            else:
                tape[index] = '0'

            pos += 4
        elif tape[pos][-1] == '9': #setrel
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                index = int(tape[pos + 1])
            elif tape[pos][-3] == '1':
                index = pos + 1
            elif tape[pos][-3] == '2':
                index = int(tape[pos + 1]) + rel

            complete(tape, index)
            rel += int(tape[index])
            pos += 2
        else:
            print('error')
            return -1
    return oxygen

def fillpath(s, p):
    res = set()
    res.add(s)
    while not len(p) == 0:
        d = p.pop()
        s = (s[0] + d[0], s[1] + d[1])
        res.add(s)
    return res

def printarea():
    global area
    for i in range(15, -20, -1):
        s = ''
        for j in range(-13, 20):
            if (j, i) == (0, 0):
                s += 's'
            elif (j, i) not in area:
                s += ' '
            elif area[(j, i)] == 0:
                s += '#'
            elif area[(j, i)] == 1:
                s += '.'
            elif area[(j, i)] == 2:
                s += 'o'
        print(s)

def bfs(src, dest):
    global area
    vis = set()
    h = deque()
    cur = (src, 0)
    while not cur[0] == dest:
        vis.add(cur[0])
        npos = (cur[0][0], cur[0][1] + 1)
        spos = (cur[0][0], cur[0][1] - 1)
        wpos = (cur[0][0] - 1, cur[0][1])
        epos = (cur[0][0] + 1, cur[0][1])
        if not area[npos] == 0 and npos not in vis:
            h.append((npos, cur[1] + 1))
        if not area[spos] == 0 and spos not in vis:
            h.append((spos, cur[1] + 1))
        if not area[wpos] == 0 and wpos not in vis:
            h.append((wpos, cur[1] + 1))
        if not area[epos] == 0 and epos not in vis:
            h.append((epos, cur[1] + 1))
        cur = h.popleft()
    return cur[1]

o = proc(mem.copy(), 1)
print(o)
# printarea()
stack.clear()
o = proc(mem.copy(), 1)
print(o)
# printarea()
stack.clear()
print(bfs((0, 0), o))
o = proc(mem.copy(), 2)
# printarea()

t = 0
h = deque()
h.append((o, 0))
while len(h) > 0:
    cur = h.popleft()
    area[cur[0]] = 2
    npos = (cur[0][0], cur[0][1] + 1)
    spos = (cur[0][0], cur[0][1] - 1)
    wpos = (cur[0][0] - 1, cur[0][1])
    epos = (cur[0][0] + 1, cur[0][1])
    if area[npos] == 1:
        h.append((npos, cur[1] + 1))
    if area[spos] == 1:
        h.append((spos, cur[1] + 1))
    if area[wpos] == 1:
        h.append((wpos, cur[1] + 1))
    if area[epos] == 1:
        h.append((epos, cur[1] + 1))

print(cur[1])