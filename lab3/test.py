def bezout_coefs(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, u, v = bezout_coefs(b, a % b)
        return gcd, v, u - (a // b) * v


for _ in range(int(input())):
    a, n, b, m = map(int, input().split())
    gc, j, k = bezout_coefs(n, m)
    x, K = a + j * n * (b - a), (m * n)
    print(x % K, K)
