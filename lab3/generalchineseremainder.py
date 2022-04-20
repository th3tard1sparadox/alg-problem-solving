def lcm(a, b, g):
    return (a * b) // g


def ext_gcd(a, b):
    if(a == 0):
        return b, 0, 1
    g, x1, y1 = ext_gcd(b % a, a)

    x = y1 - (b // a) * x1
    y = x1

    return g, x, y


def GCRT(a, n, b, m):
    g, p, q = ext_gcd(n, m)
    K = lcm(n, m, g)
    if(not a % g == b % g):
        return -1, -1

    # use bezout's identity:
    # (n/g)*p + (m/g)*q = 1

    res1 = (a * (m // g) * q) % K
    res2 = (b * (n // g) * p) % K
    res = res1 + res2

    return K, res


def main():
    T = int(input())

    for i in range(T):
        line = input().split()
        a = int(line[0])
        n = int(line[1])
        b = int(line[2])
        m = int(line[3])
        K, x = GCRT(a, n, b, m)
        if(x == -1):
            print('no solution')
        else:
            print(str(x % K) + ' ' + str(K))

if __name__ == "__main__":
    main()
