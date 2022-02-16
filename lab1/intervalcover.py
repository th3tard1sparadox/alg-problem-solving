import sys


def coverage(interval, intervals):
    sol = []
    tried = False
    while interval[1] - interval[0] > 0 or not tried:
        tried = True
        covers_min = []
        for i in intervals:
            if i[0] <= interval[0]:
                covers_min.append(i)

        if not covers_min:
            return 'impossible'

        longest = [0, float('-inf')]
        for i in covers_min:
            if i[1] >= longest[1] and i[1] >= interval[0]:
                longest = i

        for i in covers_min:
            intervals.remove(i)

        if longest[1] == float('-inf'):
            return 'impossible'

        interval[0] = longest[1]
        sol.append(longest[2])

    print(len(sol))
    return ' '.join([str(x) for x in sol])


def main():
    inp = sys.stdin.readlines()
    while inp:
        interval = [float(x) for x in inp.pop(0).splitlines()[0].split()]
        nr_intervals = int(inp.pop(0))
        intervals = []
        for i in range(nr_intervals):
            intervals.append([float(x) for x in inp.pop(0).splitlines()[0].split()] + [i])
        print(coverage(interval, intervals))


if __name__ == "__main__":
    main()
