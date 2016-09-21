import string, random, itertools

def randomword(length):
    return "".join(random.choice(string.ascii_lowercase) for i in range(length))

def write_file(filename):
    f = open(filename, "w")
    for i in range(10):
        w = randomword(10)
        p = ["".join(perm) for perm in itertools.permutations(w)]
        for j in range(5):
            f.write(w + "\n")
            f.write(random.choice(p) + "\n")
    f.close()
