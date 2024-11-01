import hashlib
import random

for i in range(10**6):
    randomstring = str(random.getrandbits(64))
    md5hash = hashlib.md5(randomstring.encode()).hexdigest()

    print(md5hash + '\t' + randomstring)