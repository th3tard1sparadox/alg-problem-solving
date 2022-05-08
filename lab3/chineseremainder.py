'''
@file chineseremainder.py
@author Annie Wång (annwa858@student.liu.se)
@brief finds solution to the equations x = a (mod n) and
       x = b (mod m). It does this using the extended euclidean
       algorithm. The time complexity for this is in total O(nlogn).
@date 2022-05-01
'''

import sys

# extended euclidean, iteratively.
def eucl(a, m):
    m0 = m
    x0 = 0
    x1 = 1

    if(m == 1):
        return 1

    while(a > 1):
        q = a // m
        t = m

        m = a % m
        a = t
        t = x0
        x0 = x1 - q * x0
        x1 = t

    if(x1 < 0):
        x1 = x1 + m0

    return x1

# put the results together, always mod to keep number small.
def CR(a, n, b, m):
    K = n * m

    res = (((a * m) % K) * eucl(m, n)) % K
    res = res + (((b * n) % K) * eucl(n, m)) % K

    return res % K

# main loop.
def main():
    T = int(input())

    for i in range(T):
        line = input().split()
        a = int(line[0])
        n = int(line[1])
        b = int(line[2])
        m = int(line[3])
        x = CR(a, n, b, m)
        print(str(x) + " " + str(n * m))

if __name__ == "__main__":
    main()
