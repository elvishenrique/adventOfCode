f = open('input', 'r')

mem = f.read().split(',')

def complete(tape, index):
    if index >= len(tape):
        fill =  [0] * (index + 1 - len(tape))
        tape += fill

def getparam(tape, pos, rel):
    instr = tape[pos][-1]
    param1 = ['3', '4', '9']
    param2 = ['5', '6']
    param3 = ['1', '2', '7', '8']

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

def turn(vec, left):
    if left:
        d = -1
    else:
        d = 1
    return (vec[1] * d, -vec[0] * d)

def xvalue(vec):
    return vec[0]

def yvalue(vec):
    return vec[1]

def proc(tape, inp):
    rob = (0,0) # robot position
    vec = (0,1) # direction of turning
    pan = {} # panel
    pan[rob] = 1 # part2
    paint = True # should paint or turn
    pos = 0
    rel = 0
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
            if rob not in pan:
                pan[rob] = 0
            tape[i] = pan[rob]
            pos += 2
        elif tape[pos][-1] == '4': #output
            o = getparam(tape, pos, rel)
            # print(o[0])
            if paint:
                paint = False
                pan[rob] = int(o[0])
            else:
                paint = True
                vec = turn(vec, int(o[0]) == 0)
                rob = (rob[0] + vec[0], rob[1] + vec[1])
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
    return pan

reg = proc(mem, 1)
print(len(reg))

minx = min(reg, key=xvalue)[0]
maxx = max(reg, key=xvalue)[0]
miny = min(reg, key=yvalue)[1]
maxy = max(reg, key=yvalue)[1]
print((minx, miny))
print((maxx, maxy))

for i in range(maxy, miny-1, -1):
    s = ''
    for j in range(minx, maxx+1):
        if (j,i) not in reg or reg[(j,i)] == 0:
            s += '.'
        else:
            s += '#'
    print(s)