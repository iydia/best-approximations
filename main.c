#include <stdio.h>
#include <math.h>

// ℓ(p, q) := |√2 − p/q|
double l(double p, double q) {
    return fabs(sqrt(2) - p / q);
}

// Check if the condition holds for a given δ
int condition_holds(double delta) {
    int q;
    for (q = 2; q <= 100; ++q) {
        double error = l((int)(sqrt(2) * q + 0.5), q); // Compute error for p = (int)(√2 * q + 0.5)
        if (error > pow(q, -delta)) {
            return 0; // Condition does not hold for this δ
        }
    }
    return 1; // Condition holds for this δ
}

// Find the largest δ satisfying the condition
double find_largest_delta() {
    double delta = 0.5; // Start with a reasonable initial value
    while (condition_holds(delta)) {
        delta += 0.01; // Increment δ (you can adjust the step size)
    }
    return delta - 0.01; // Return the largest δ that satisfies the condition
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
    // The largest δ such that the error term diminishes faster than 1/q^δ is greater than 1/2. I got 1.16?
    best_approximations();

    double largest_delta = find_largest_delta();
    printf("Largest delta satisfying the condition: %.2f\n", largest_delta);
}