/**
 * @file longincsubseq.cpp
 * @author Annie Wång (annwa858@student.liu.se)
 * @brief solution for well known problem of finding longest increasing
 *        subsequence using DP and binary search. Complexity is O(nlogn).
 * @date 2022-02-16
 */
#include <iostream>
#include <math.h>

using namespace std;

/**
 * @brief sudocode for algorithm found on wikipedia as the problem is well known:
 *        https://en.wikipedia.org/wiki/Longest_increasing_subsequence
 * 
 * @param seq the sequence we're searching in.
 * @param n the length of seq.
 * @param res where the resulting indexes of the longest increasing subsequence
 *            are placed.
 * @return int the length of our res. 
 */
int findLongest(int *seq, int n, int *res) {
    // store our current results.
    int prevSmallest[n];
    // dynamic programming array keeping track of the index of our smallest
    // value from a point.
    int lastIndexDP[n + 1];

    int longestSeq = 0;
    for(int i = 0; i < n; i++) {
        int low = 1;
        int high = longestSeq + 1;

        // binary searching for finding the largest sequence length.
        while(low < high) {
            int middle = low + floor((high - low) / 2);
            if(seq[lastIndexDP[middle]] < seq[i]) {
                low = middle + 1;
            } else {
                high = middle;
            }
        }
        int newLongest = low;

        // the previous element in seq will be the the last index of the
        // subsequence of length newLongest - 1.
        prevSmallest[i] = lastIndexDP[newLongest - 1];
        lastIndexDP[newLongest] = i;

        // we found a new longest sequence.
        if(newLongest > longestSeq) {
            longestSeq = newLongest;
        }
    }

    // reconstruct the result.
    int index = lastIndexDP[longestSeq];
    for(int i = longestSeq - 1; i >= 0; i--) {
        res[i] = index;
        index = prevSmallest[index];
    }
    return longestSeq;
}

int main() {
    // c++ io slow
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // put away enough space stated in the kattis problem.
    int res[100000];
    
    // read the data and apply algorithm.
    while(cin >> n) {
        int seq[n];
        for(int i = 0; i < n; i++) {
            cin >> seq[i];
        }
        int len = findLongest(seq, n, res);
        cout << len << "\n";
        for(int i = 0; i < len; i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}