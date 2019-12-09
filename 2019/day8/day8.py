f = open('input', 'r')

width = 25
height = 6
size = width * height
layers = f.read()

x = []

for i in range(len(layers)//size):
    cur = i*size
    x += [layers[cur:cur+size]]

for k in x:
    if not len(k) == size:
        print(len(k))

l = size
res = -1
for i in range(len(x)):
    if x[i].count('0') < l:
        l = x[i].count('0')
        res = i

print(x[res].count('1')*x[res].count('2'))

image = ['2']*size

for layer in x:
    for i in range(size):
        if image[i] == '2':
            image[i] = layer[i]

for i in range(height):
    cur = i*width
    print(image[cur:cur+width])