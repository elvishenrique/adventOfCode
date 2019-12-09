f = open('input', 'r')

inst = f.read().split(',')
out = 0

def proc(tape, ph, inp, index):
    #global out
    global ready
    global reg
    pos = 0
    phase = True
    while not tape[pos] == '99':
        if tape[pos][-1] == '1': #add
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            add = int(x) + int(y)
            tape[int(tape[pos+3])] = str(add)
            pos += 4
        elif tape[pos][-1] == '2': #mul
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            prod = int(x) * int(y)
            tape[int(tape[pos+3])] = str(prod)
            pos += 4
        elif tape[pos] == '3': #read
            i = int(tape[pos+1])
            if phase:
                tape[i] = str(ph)
                phase = False
                pos += 2
            elif ready[index]:
                tape[i] = str(reg[index])
                ready[index] = False
                pos += 2
            #else:
                #tape[i] = str(inp)
            #pos += 2
        elif tape[pos][-1] == '4': #output
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                o = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                o = tape[pos+1]
            print(o)
            #out = int(o)
            reg[(index+1)%5] = int(o)
            ready[(index+1)%5] = True
            pos += 2
        elif tape[pos][-1] == '5': #jtrue
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            if not int(x) == 0:
                pos = int(y)
            else:
                pos += 3
        elif tape[pos][-1] == '6': #jfalse
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            if int(x) == 0:
                pos = int(y)
            else:
                pos += 3
        elif tape[pos][-1] == '7': #lessthan
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            if int(x) < int(y):
                tape[int(tape[pos+3])] = '1'
            else:
                tape[int(tape[pos+3])] = '0'
            pos += 4
        elif tape[pos][-1] == '8': #equals
            if len(tape[pos]) < 3 or tape[pos][-3] == '0':
                x = tape[int(tape[pos+1])]
            elif tape[pos][-3] == '1':
                x = tape[pos+1]
            if len(tape[pos]) < 4 or tape[pos][-4] == '0':
                y = tape[int(tape[pos+2])]
            elif tape[pos][-4] == '1':
                y = tape[pos+2]
            if int(x) == int(y):
                tape[int(tape[pos+3])] = '1'
            else:
                tape[int(tape[pos+3])] = '0'
            pos += 4
        else:
            print('error')
            return -1
    return tape[0]

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
# shift = [1,0,4,3,2]

# for p in permutation(shift):
#     for i in p:
#         n = inst[:]
#         proc(n, i, out)
#     if out > mx:
#         mx = out
#         result = p
#     out = 0

# print(mx)
# print(result)

mem = []
reg = [0] * 5
ready = [False] * 5
for i in range(5):
    mem += [inst[:]]