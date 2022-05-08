'''
@file generalchineseremainder.py
@author Annie Wång (annwa858@student.liu.se)
@brief finds solution to the equations x = a (mod n) and
       x = b (mod m). It does this using the extended euclidean
       algorithm. The time complexity for this is in total O(nlogn).
       the only difference to the normal chinese remainder theorem is
       how we put the answer together, see this resource for mathematical proof:
       https://forthright48.com/chinese-remainder-theorem-part-2-non-coprime-moduli/
@date 2022-05-01
'''

# least common multiplier.
def lcm(a, b, g):
    return (a * b) // g

# extended euclidean, recursively.
def ext_gcd(a, b):
    if(a == 0):
        return b, 0, 1
    g, x1, y1 = ext_gcd(b % a, a)

    x = y1 - (b // a) * x1
    y = x1

    return g, x, y

# general chinese remainder theorem.
def GCRT(a, n, b, m):
    g, p, q = ext_gcd(n, m)
    # set K to the least common multiplier.
    K = lcm(n, m, g)
    # no solution.
    if(not a % g == b % g):
        return -1, -1

    # use bezout's identity:
    # (n/g)*p + (m/g)*q = 1

    res1 = (a * (m // g) * q) % K
    res2 = (b * (n // g) * p) % K
    res = res1 + res2

    return K, res

# main loop.
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
