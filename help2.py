""" Implementation of kattis problem Help! """
import sys


def unify(first, second):
    """ Returns a string containing either '-' or a unified match """

    # iterate through the words to find all simple replacements
    for i, w1 in enumerate(first):
        # replace all instances of placeholder with corresponding word in
        # other pattern
        if w1[0] == '<' and not second[i][0] == '<':
            return unify([x if not x == w1 else second[i] for x in first], second)
        if not w1[0] == '<' and second[i][0] == '<':
            return unify(first, [x if not x == second[i] else w1 for x in second])
    # iterate through again to find all placeholders without any corresponding word
    for i, w1 in enumerate(first):
        if w1[0] == '<' and second[i][0] == '<':
            return unify([x if not x == w1 else 'random' for x in first], [x if not x == second[i] else 'random' for x in second])
    # if the patterns don't match after all placeholders have been found, stop
    # searching no match possible
    if not first == second:
        return '-'
    # return the unified pattern
    return ' '.join(first)



def solve(first, second):
    """ Prints a string containing either '-' or a unified match """

    # if they are not of the same length they cannot be unified
    if not len(first) == len(second):
        print('-')
    else:
        # try to unify the patterns
        print(unify(first, second))


def main():
    """ Main method tries to unify two patterns """

    # read the input
    inp = sys.stdin.readlines()
    cases = int(inp.pop(0))
    # solve each case
    for i in range(cases):
        # read both patterns for each case
        first = inp.pop(0).splitlines()[0].split()
        second = inp.pop(0).splitlines()[0].split()
        solve(first, second)


if __name__ == "__main__":
    main()
