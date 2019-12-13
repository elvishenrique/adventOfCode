import math

f = open('input', 'r')

lines = f.read().splitlines()

def sign(x):
    if x == 0:
        return 0

    return abs(x)//x


class moon:
    def __init__(self, start):
        self.pos = start
        self.vel = (0,0,0)

    def applyv(self):
        self.pos = (self.pos[0] + self.vel[0], self.pos[1] + self.vel[1], self.pos[2] + self.vel[2])

    def applyg(self, grav):
        self.vel = (self.vel[0] + grav[0], self.vel[1] + grav[1], self.vel[2] + grav[2])

    def pot(self):
        return abs(self.pos[0]) + abs(self.pos[1]) + abs(self.pos[2])

    def kin(self):
        return abs(self.vel[0]) + abs(self.vel[1]) + abs(self.vel[2])

    def energy(self):
        return self.pot() * self.kin()

def getstate(univ):
    # state = []
    # for m in univ:
    #     state += [m.pos]
    return ((univ[0].pos[0], univ[0].vel[0]), (univ[1].pos[0], univ[1].vel[0]), (univ[2].pos[0], univ[2].vel[0]), (univ[3].pos[0], univ[3].vel[0]))

def energystate(univ):
    return (univ[0].energy(), univ[1].energy(), univ[2].energy(), univ[3].energy())

def totalenergy(univ):
    res = 0
    for m in univ:
        res += m.energy()
    return res

def mmc(a, b):
    return (a * b) // math.gcd(a,b)

moons = []

for line in lines:
    info = line[1:-1].split(', ')
    x = int(info[0].split('=')[1])
    y = int(info[1].split('=')[1])
    z = int(info[2].split('=')[1])
    m = moon((x,y,z))
    moons += [m]

# print(getstate(moons))
states = set()
states.add(getstate(moons))
st = set()
energies = {}
# energies.add(energystate(moons))
energies[totalenergy(moons)] = [0]
steps = 0
rep = False
while not rep:
#for j in range(1000000):
    # simulate universe start
    # apply gravity
    g = []
    for m in moons:
        gx = 0
        gy = 0
        gz = 0
        for n in moons:
            gx += sign(n.pos[0] - m.pos[0])
            gy += sign(n.pos[1] - m.pos[1])
            gz += sign(n.pos[2] - m.pos[2])
        g += [(gx, gy, gz)]

    # s = (moons[0].vel, g[0], moons[1].vel, g[1], moons[2].vel, g[2], moons[3].vel, g[3])
    # if s in st:
    #     print(j)
    #     print(s)
    # st.add(s)

    for i in range(len(moons)):
        moons[i].applyg(g[i])

    # apply velocity
    for m in moons:
        m.applyv()

    # simulate universe end


    # check state
    # if totalenergy(moons) == 0:
    #     rep = True
        # print(getstate(moons))
        # print(g)

    # if totalenergy(moons) == 11460:
    #     print(getstate(moons))
        #print(totalenergy(moons))

    # if totalenergy(moons) in energies:
    #     energies[totalenergy(moons)] += [steps + 1]
    #     if len(energies[totalenergy(moons)]) == 10:
    #         rep = True
    # else:
    #     energies[totalenergy(moons)] = [steps + 1]

    # if energystate(moons) in energies:
    #     rep = True
    #     # print(j)
    #     # print(energystate(moons))
    # energies.add(energystate(moons))

    state = getstate(moons)
    if state in states:
        print(state)
        rep = True
    states.add(state)

    # #if j % 1386 == 1385 or j % 2772 == 1525:
    #     # print(state)
    #     #print(energystate(moons))

    steps += 1
    if steps % 1000000 == 0:
        print(steps)

print(getstate(moons))
# print(energies[totalenergy(moons)])
# print(totalenergy(moons))
print(steps)

rx = 186028
ry = 286332
rz = 96236

print(mmc(mmc(rx, ry), rz))