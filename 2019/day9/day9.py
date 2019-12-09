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

def proc(tape, inp):
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
            tape[i] = str(inp)
            pos += 2
        elif tape[pos][-1] == '4': #output
            o = getparam(tape, pos, rel)
            print(o[0])
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
    return tape[0]

proc(mem, 1)
proc(mem, 2)