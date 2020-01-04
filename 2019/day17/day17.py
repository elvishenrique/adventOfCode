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

def proc(tape, inp):
    if inp:
        tape[0] = '2'
    image = ''
    pos = 0
    rel = 0
    inpindex = 0
    inptype = 0
    m = 'A,B,A,B,C,C,B,A,B,C'
    a = 'L,12,L,10,R,8,L,12'
    b = 'R,8,R,10,R,12'
    c = 'L,10,R,12,R,8'
    dust = ''
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
            if not inp:
                tape[i] = '1'
            elif inptype == 0:
                if inpindex == len(m):
                    tape[i] = ord('\n')
                    inpindex = 0
                    inptype += 1
                else:
                    tape[i] = ord(m[inpindex])
                    inpindex += 1
            elif inptype == 1:
                if inpindex == len(a):
                    tape[i] = ord('\n')
                    inpindex = 0
                    inptype += 1
                else:
                    tape[i] = ord(a[inpindex])
                    inpindex += 1
            elif inptype == 2:
                if inpindex == len(b):
                    tape[i] = ord('\n')
                    inpindex = 0
                    inptype += 1
                else:
                    tape[i] = ord(b[inpindex])
                    inpindex += 1
            elif inptype == 3:
                if inpindex == len(c):
                    tape[i] = ord('\n')
                    inpindex = 0
                    inptype += 1
                else:
                    tape[i] = ord(c[inpindex])
                    inpindex += 1
            elif inptype == 4:
                if inpindex == 0:
                    tape[i] = ord('n')
                    inpindex += 1
                else:
                    tape[i] = ord('\n')
            pos += 2
        elif tape[pos][-1] == '4': #output
            o = getparam(tape, pos, rel)
            if not inp:
                image += chr(int(o[0]))
            else:
                dust = o[0]
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
    if not inp:
        return image
    return dust

# img = proc(mem, False)
# print(img)

# lines = img.splitlines()
# view = {}
# for i in range(len(lines) - 1):
#     for j in range(len(lines[i])):
#         view[(j, i)] = lines[i][j]

# hor = []
# for y in range(len(lines) - 1):
#     scaf = False
#     start = -1
#     for x in range(len(lines[y])):
#         if not view[(x, y)] == '.' and not view[(x, y)] == 'X' and not scaf:
#             start = x
#             scaf = True
#         elif view[(x, y)] == '.' and scaf:
#             end = x - 1
#             scaf = False
#             if not start == end:
#                 hor += [(start, end, y)]
#     if scaf:
#         end = x
#         scaf = False
#         if not start == end:
#             hor += [(start, end, y)]

# ver = []
# for x in range(len(lines[0])):
#     scaf = False
#     start = -1
#     for y in range(len(lines) - 1):
#         if not view[(x, y)] == '.' and not view[(x, y)] == 'X' and not scaf:
#             start = y
#             scaf = True
#         elif view[(x, y)] == '.' and scaf:
#             end = y - 1
#             scaf = False
#             if not start == end:
#                 ver += [(start, end, x)]
#     if scaf:
#         end = y
#         scaf = False
#         if not start == end:
#             ver += [(start, end, x)]

# intersections = []
# for h in hor:
#     for v in ver:
#         if h[2] > v[0] and h[2] < v[1] and v[2] > h[0] and v[2] < h[1]:
#             intersections += [(v[2], h[2])]

# # print(len(intersections))
# # print(intersections)

# res = 0
# for p in intersections:
#     res += p[0] * p[1]

# print(res)

print(proc(mem, True))