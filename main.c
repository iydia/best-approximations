#include <stdio.h>
#include <math.h>

// ℓ(p, q) := |√2 − p/q|
double l(double p, double q) {
    return fabs(sqrt(2) - p / q);
}

// Function to find the sequence of best approximations
void best_approximations() {
    int q = 1; // Start with q1 = 1
    int p = (int)(sqrt(2) * q); // Initial value for p
    int n;

    for (n = 1; n <= 100; ++n) {
        printf("l(%d, %d) = %f\n", p, q, l(p, q));
        
        // Find the next p and q using the property of continued fractions
        double min_diff = l(p, q);
        int new_p = p;
        int new_q = q + 1;
        for (int i = 1; i <= q + 1; ++i) {
            double diff = l(i, q + 1);
            if (diff < min_diff) {
                min_diff = diff;
                new_p = i;
            }
        }
        
        // Update p and q for the next iteration
        p = new_p;
        q = new_q;
    }
}

int main(void) {
    // Compute the first 100 terms of the sequence for ℓ(p, q) := |√2 − p/q|
    // The largest η for which |√2 − p/q| ≤ 1/q^η, since the sequence converges to √2, is 1/2
    best_approximations();
    return 0;
}