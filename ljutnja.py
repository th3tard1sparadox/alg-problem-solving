""" Tired of proper doumentation, this is ljutnja look at the filename """
import sys


def angi(m, n, wishes):
    """ Angi smol child calculator """

    # Remember to not assume a sorted input kids
    wishes.sort()

    # Some constants
    anger = 0
    desire = sum(wishes)
    desire_left = desire - m # Sort of what is left of the desired candy
    kids_left = n

    # Iterate children
    for i in range(n):
        # Choose to give the smallest amount of candy that we can "justify"
        best_amount = min(wishes[i], desire_left // kids_left)
        anger += best_amount ** 2
        # We filled some desire
        desire_left -= best_amount
        kids_left -= 1

    return anger


def main():
    """ Main method """

    # read the input
    first_row = sys.stdin.readline()
    m, n = [int(x) for x in first_row.split()] # m = candies, n = children

    data = sys.stdin.readlines()
    wishes = []
    for i in range(n):
        wishes.append(int(data.pop(0)))

    print(angi(m, n, wishes))


if __name__ == "__main__":
    main()
