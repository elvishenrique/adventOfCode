f = open('input', 'r')

mem = f.read().split(',')

g = open('output', 'w')

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

def blocks(screen):
    return list(screen.values()).count(2)

def ballpos(screen):
    for pos in screen:
        if screen[pos] == 4:
            return pos
    return (-1, 0)

def paddlepos(screen):
    for pos in screen:
        if screen[pos] == 3:
            return pos
    return (-1, 0)

def prtscr(screen):
    g.seek(0)
    for y in range(26):
        s = ''
        for x in range(37):
            if screen[(x,y)] == 0:
                s += ' '
            elif screen[(x,y)] == 1:
                s += 'x'
            elif screen[(x,y)] == 2:
                s += '#'
            elif screen[(x,y)] == 3:
                s += '-'
            elif screen[(x,y)] == 4:
                s += 'o'
        print(s)
        # g.write(s)
        # g.write('\n')

def target(pos, vel, y):
    if vel[1] < 0 and pos[1] < y:
        return -1
    if vel[1] > 0 and pos[1] > y:
        return -1
    if vel[0] == 0:
        return pos[0]
    return pos[0] + vel[0] * (y - pos[1])

def decision(ballp, prevballp, paddlep):
    vel = (ballp[0] - prevballp[0], ballp[1] - prevballp[1])
    dest = target(ballp, vel, paddlep[1] - 1)
    if dest == -1:
        if paddlep[0] < ballp[0]:
            return '1'
        elif paddlep[0] > ballp[0]:
            return '-1'
        else:
            return '0'
    elif paddlep[0] < dest:
        return '1'
    elif paddlep[0] > dest:
        return '-1'
    else:
        return '0'

def proc(tape, play):
    if play:
        tape[0] = '2'
    pos = 0
    rel = 0
    tile = 0
    scr = {}
    oldballpos = (0,0)
    score = '0'
    x = 0
    y = 0
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
            prtscr(scr)
            print('blocks: '+ str(blocks(scr)))
            print('score: '+ score)
            bp = ballpos(scr)
            # g.write('\n')
            # g.write('blocks: '+ str(blocks(scr)))
            # g.write('\n')
            # g.write('score: '+ score)
            # s = input()
            # if s == 'a':
            #     tape[i] = '-1'
            # elif s == 's':
            #     tape[i] = '0'
            # elif s == 'd':
            #     tape[i] = '1'
            tape[i] = decision(bp, oldballpos, paddlepos(scr))
            oldballpos = bp
            pos += 2
        elif tape[pos][-1] == '4': #output
            o = getparam(tape, pos, rel)
            if tile % 3 == 0:
                x = int(o[0])
            elif tile % 3 == 1:
                y = int(o[0])
            if tile % 3 == 2:
                if x == -1 and y == 0:
                    score = o[0]
                else:
                    scr[(x,y)] = int(o[0])
            tile += 1
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
    return (scr, score)

game = proc(mem, True)
prtscr(game[0])
print(blocks(game[0]))
print(game[1])