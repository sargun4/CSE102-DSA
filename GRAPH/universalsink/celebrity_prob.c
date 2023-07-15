#include <stdio.h>
#include <stdbool.h>

#define N 4

bool knows(int i, int j) {
    // Function to check if person i knows person j
    // Return true if person i knows person j, false otherwise
    // You need to implement this function based on your problem's definition
    // This is just a dummy implementation
    if (i == 0 && j == 1)
        return true;
    else if (i == 0 && j == 2)
        return true;
    else if (i == 0 && j == 3)
        return true;
    else if (i == 1 && j == 2)
        return true;
    else if (i == 1 && j == 3)
        return true;
    else if (i == 2 && j == 3)
        return true;
    else
        return false;
}

int findCelebrity(int n) {
    int candidate = 0;

    // Find potential candidate for being the celebrity
    for (int i = 1; i < n; i++) {
        if (knows(candidate, i))
            candidate = i;
    }

    // Verify if the candidate is a celebrity
    for (int i = 0; i < n; i++) {
        if (i != candidate && (knows(candidate, i) || !knows(i, candidate)))
            return -1;  // Candidate is not a celebrity
    }

    return candidate;  // Candidate is a celebrity
}

int main() {
    int n = N;  // Number of people

    int celebrity = findCelebrity(n);

    if (celebrity != -1)
        printf("Celebrity found at index %d\n", celebrity);
    else
        printf("No celebrity found\n");

    return 0;
}
