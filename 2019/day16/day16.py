f = open('input', 'r')

signal = f.read().splitlines()[0]

def genpattern(base, repeat, size):
    pattern = []
    for i in range(len(base)):
        pattern += [base[i]] * repeat
    pattern += [base[0]]
    return pattern[1:]

def transform(sig, base):
    s = ''
    i = 0
    while i < len(sig):
        pattern = genpattern(base, i + 1, len(sig))
        res = 0
        for j in range(len(sig)):
            res += int(sig[j]) * pattern[j % len(pattern)]
        s += str(abs(res) % 10)
        i += 1
    return s

def fft(sig, base, phase):
    res = sig
    for i in range(phase):
        res = transform(res, base)
    return res

def fastfft(sig, offset):
    t = sig[offset:]
    n = len(sig)
    for k in range(100):
        if offset > n / 2:
            s = ''
            res = 0
            for i in range(n - offset):
                res += int(t[i])
            s += str(abs(res) % 10)
            for i in range(1, n - offset):
                res -= int(t[i - 1])
                s += str(abs(res) % 10)
            t = s
        else:
            return 'nyi'
    return t

print(fft(signal, [0, 1, 0, -1], 100)[:8])
offset = int(signal[:7])
result = fastfft(signal * 10000, offset)
print(result[:8])