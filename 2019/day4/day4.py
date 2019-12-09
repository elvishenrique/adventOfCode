f = open('input', 'r')

def verify(n):
    s = str(n)
    double = False
    for i in range(len(s)-1):
        if int(s[i]) > int(s[i+1]):
            return False
        if int(s[i]) == int(s[i+1]):
            double = True
    return double

def verify2(n):
    s = str(n)
    for c in s:
        if s.count(c) == 2:
            return True
    return False

start = 240920
end = 789857
accept = 0
acc = 0

for i in range(start, end):
    if verify(i):
        accept += 1
        if verify2(i):
            acc += 1

print(verify(111111))
print(verify(223450))
print(verify(123789))
print(accept)

print(verify2(112233))
print(verify2(123444))
print(verify2(111122))
print(acc)