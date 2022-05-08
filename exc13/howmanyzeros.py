def CZ(n):
    result = 1 # count from 0
    i = 1

    while True:
        q1, r1 = divmod(n, i)
        q2, r2 = divmod(q1, 10)

        if q2 == 0:
            return result

        if r2 == 0:
            result += (q2 - 1) * i + r1 + 1
        else:
            result += q2 * i

        i *= 10

def main():
    m, n = map(int, input().split())

    while(m >= 0):
        if(m == 0):
            print(CZ(n))
        else:
            print(CZ(n) - CZ(m - 1))
        m, n = map(int, input().split())

if __name__ == "__main__":
    main()
