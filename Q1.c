#include <stdio.h>
#include <math.h>

// Prints each term of the sequence for (a)
void printer(int p, int q) {
    int diff = abs(sqrt(2) - (p / q));

    printf("l(%d, %d) = |√2 - %d/%d| = %d", p, q, p, q, diff);
}

int main(void) {

}