import json

def gcd(x, y):
    if x % y == 0:
        return False
    if y % x == 0:
        return False
    return True

def uzajamnoProst(x, l):
    if len(l) == 0:
        return True
    for i in range(len(l)):
        if not gcd(x, l[i]):
            return False
    return True

def get_primes():
    x = 2
    l = []
    while True:
        if uzajamnoProst(x, l):
            l.append(x)
            yield x
        x = x + 1
        
def nth_prime(n):
    prime_gen = get_primes()
    prime = None
    for _ in range(n):
        prime = next(prime_gen)
    return prime

def pub(p, q):
    n = p * q
    ojlerN = (p - 1) * (q - 1)
    e = None
    for i in range(1, ojlerN):
        if gcd(i, ojlerN):
            e = i
            break
    return (n, e)

def priv(p, q, k, pubKey):
    ojlerN = (p - 1) * (q - 1)
    _, e = pubKey
    return (k * ojlerN + 1) / e

if __name__ == "__main__":
    with open('conf.json', 'r') as f:
        obj = json.load(f)
        
    m = obj["m"]
    n = obj["n"]
    k = obj["k"]
    
    Pm = nth_prime(m)
    Pn = nth_prime(n)
    
    pubKey = pub(n, m)
    privKey = priv(n, m, k, pubKey)
    
    print(privKey)