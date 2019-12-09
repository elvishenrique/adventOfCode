f = open('input', 'r')

inst = f.read().split(',')
out = 0

def proc(tapes, ph, debug):
    done = [False] * 5
    index = 0
    ready = [False] * 5
    reg = [0] * 5
    pos = [0] * 5
    phase = [True] * 5
    ready[0] = True
    while done.count(False) > 0:
        if tapes[index][pos[index]][-1] == '1': #add
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            add = int(x) + int(y)
            tapes[index][int(tapes[index][pos[index]+3])] = str(add)
            pos[index] += 4
        elif tapes[index][pos[index]][-1] == '2': #mul
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            prod = int(x) * int(y)
            tapes[index][int(tapes[index][pos[index]+3])] = str(prod)
            pos[index] += 4
        elif tapes[index][pos[index]] == '3': #read
            i = int(tapes[index][pos[index]+1])
            if phase[index]:
                tapes[index][i] = str(ph[index])
                phase[index] = False
                pos[index] += 2
            elif ready[index]:
                tapes[index][i] = str(reg[index])
                ready[index] = False
                pos[index] += 2
            else:
                if debug:
                    print(index)
                index = (index + 1) % 5
        elif tapes[index][pos[index]][-1] == '4': #output
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                o = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                o = tapes[index][pos[index]+1]
            #print(o)
            reg[(index+1)%5] = int(o)
            ready[(index+1)%5] = True
            pos[index] += 2
        elif tapes[index][pos[index]][-1] == '5': #jtrue
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            if not int(x) == 0:
                pos[index] = int(y)
            else:
                pos[index] += 3
        elif tapes[index][pos[index]][-1] == '6': #jfalse
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            if int(x) == 0:
                pos[index] = int(y)
            else:
                pos[index] += 3
        elif tapes[index][pos[index]][-1] == '7': #lessthan
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            if int(x) < int(y):
                tapes[index][int(tapes[index][pos[index]+3])] = '1'
            else:
                tapes[index][int(tapes[index][pos[index]+3])] = '0'
            pos[index] += 4
        elif tapes[index][pos[index]][-1] == '8': #equals
            if len(tapes[index][pos[index]]) < 3 or tapes[index][pos[index]][-3] == '0':
                x = tapes[index][int(tapes[index][pos[index]+1])]
            elif tapes[index][pos[index]][-3] == '1':
                x = tapes[index][pos[index]+1]
            if len(tapes[index][pos[index]]) < 4 or tapes[index][pos[index]][-4] == '0':
                y = tapes[index][int(tapes[index][pos[index]+2])]
            elif tapes[index][pos[index]][-4] == '1':
                y = tapes[index][pos[index]+2]
            if int(x) == int(y):
                tapes[index][int(tapes[index][pos[index]+3])] = '1'
            else:
                tapes[index][int(tapes[index][pos[index]+3])] = '0'
            pos[index] += 4
        elif tapes[index][pos[index]] == '99':
            done[index] = True
            index = (index + 1) % 5
        else:
            print('error')
            return -1
    return reg[0]

def permutation(lst):
    if len(lst) == 0:
        return []
    if len(lst) == 1:
        return [lst]

    res = []
    for i in range(len(lst)):
        cur = lst[i]
        remlst = lst[:i] + lst[i+1:]
        for p in permutation(remlst):
            res.append([cur] + p)
    return res

mx = 0
result = []

def generate(inst):
    mem = []
    for i in range(5):
        mem += [inst[:]]
    return mem

shift = [9,8,7,6,5]
for p in permutation(shift):
    out = proc(generate(inst), p, False)
    if out > mx:
        mx = out
        result = p

print(mx)
print(result)