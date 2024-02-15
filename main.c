#include <stdio.h>
#include <math.h>

// ℓ(p, q) := |√2 − p/q|
double l_1(double p, double q) {
    return fabs(sqrt(2) - p / q);
}

// ℓ(p, q) := |q√2 - p|
double l_2(double p, double q) {
    return fabs(q * sqrt(2) - p);
}

// ℓ(p, q) := |2 - p/q|
double l_3(double p, double q) {
    return fabs(2 - p / q);
}

// Function to find the sequence of best approximations
void best_approximations(double (*l)(double, double)) {
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

// Check if the condition holds for a given δ
int condition_holds(double delta) {
    int q;
    for (q = 2; q <= 100; ++q) {
        double error = l_1((int)(sqrt(2) * q + 0.5), q); // Compute error for p = (int)(√2 * q + 0.5)
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

// Function to compare sequences and find pairs (p, q) that appear in one sequence but not all of them
void compare_xor(int pq1[][2], int pq2[][2], int pq3[][2]) {
    int i = 0, j = 0, k = 0;
    
    printf("\nPairs that appear in one sequence but not all:\n");
    
    while (i < 100 || j < 100 || k < 100) {
        if ((i < 100 && j < 100) && (pq1[i][0] == pq2[j][0] && pq1[i][1] == pq2[j][1])) {
            // Pair (p, q) appears in sequences 1 and 2
            i++;
            j++;
        } else if ((j < 100 && k < 100) && (pq2[j][0] == pq3[k][0] && pq2[j][1] == pq3[k][1])) {
            // Pair (p, q) appears in sequences 2 and 3
            j++;
            k++;
        } else if ((k < 100 && i < 100) && (pq3[k][0] == pq1[i][0] && pq3[k][1] == pq1[i][1])) {
            // Pair (p, q) appears in sequences 3 and 1
            k++;
            i++;
        } else {
            // Pair (p, q) appears in only one sequence
            if (i < 100) {
                printf("(%d, %d) - Sequence 1\n", pq1[i][0], pq1[i][1]);
                i++;
            }
            if (j < 100) {
                printf("(%d, %d) - Sequence 2\n", pq2[j][0], pq2[j][1]);
                j++;
            }
            if (k < 100) {
                printf("(%d, %d) - Sequence 3\n", pq3[k][0], pq3[k][1]);
                k++;
            }
        }
    }
}

int main(void) {

    // Compute the first 100 terms of the sequence for ℓ(p, q) := |√2 − p/q|
    printf("Using l_1:\n");
    best_approximations(l_1);     
    // The largest η for which |√2 − p/q| ≤ 1/q^η, since the sequence converges to √2, is 1/2
    // The largest δ such that the error term diminishes faster than 1/q^δ is greater than 1/2. I got 1.16?

    // Compute the first 100 terms of the sequence for ℓ(p, q) := |q√2 - p|
    printf("\nUsing l_2:\n");
    best_approximations(l_2);

    // Compute the first 100 terms of the sequence for ℓ(p, q) := |2 - p/q|
    printf("\nUsing l_3:\n");
    best_approximations(l_3);

    // Compare the sequences and find pairs (p, q) that appear in one sequence but not all of them
    int pq1[100][2], pq2[100][2], pq3[100][2];
    compare_xor(pq1, pq2, pq3);


    double largest_delta = find_largest_delta();
    printf("Largest delta satisfying the condition: %.2f\n", largest_delta);
}