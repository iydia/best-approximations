#include <stdio.h>
#include <math.h>

// q1a helper to filter the q's
int q1a_helper(double prev_closest_approx, int q) {

    double closest_this_round = 1;
    double bestp = 0;
    double root2 = sqrt(2);

    for (double thisp = q; thisp <= 2*q; ++thisp) {
        double p_by_q = (double)thisp/q;
        double diff = fabs((double)(p_by_q - root2));
        if (diff < fabs((double)(closest_this_round - root2))) {
            if (diff < fabs((double)(prev_closest_approx - root2))) {
                closest_this_round = (double)p_by_q;
                bestp = thisp;
            }
        }
    }

    return bestp;
}

// q1b helper to filter the q's
int q1b_helper(double prev_closest_approx, int q) {

    double root2 = sqrt(2);
    double closest_this_round = root2 - 1;
    double bestp = 0;

    for (double thisp = q; thisp <= 2*q; ++thisp) {
        double abs_q_root2_minus_p = (double)fabs(q*root2 - thisp);
        if (abs_q_root2_minus_p < closest_this_round) {
            if (abs_q_root2_minus_p < fabs(prev_closest_approx)) {
                closest_this_round = abs_q_root2_minus_p;
                bestp = thisp;
            }
        }
    }

    return bestp;
}

// Prints each term of the sequence for (a)
void print_q1a(int p, int q, double closest_approx) {

    printf("l(%d, %d) = |√2 - %d/%d| = |√2 - %.*lf| = %.*lf\n", p, q, p, q, 20, closest_approx, 20, fabs(sqrt(2) - closest_approx));
}

// Prints each term of the sequence for (b)
void print_q1b(int p, int q, double closest_approx) {

    printf("l(%d, %d) = |%d√2 - %d| = %.*lf\n", p, q, q, p, 20, fabs(closest_approx));
}

// later, make a calculate() function that abstracts all these
// q1a main function
void q1a() {
    int terms_found = 0;
    int p = 1;
    double closest_approx = 1;

    // begin with p=1, q=1
    print_q1a(1, 1, closest_approx);

    int q = 2;

    while (terms_found <= 20) {
        p = q1a_helper(closest_approx, q);
        if (p > 0) {
            closest_approx = fabs((double)p/q);
            print_q1a(p, q, closest_approx);
            ++terms_found;
        }
        ++q;
    }
}

// q1b main function
void q1b() {

    double root2 = sqrt(2);
    int terms_found = 0;
    int p = 1;
    double closest_approx = sqrt(2) - 1;

    // begin with p=1, q=1
    print_q1b(1, 1, closest_approx);

    int q = 2;
    
    while (terms_found <= 15) {
        p = q1b_helper(closest_approx, q);
        if (p > 0) {
            closest_approx = (double)(q*root2-p);
            print_q1b(p, q, closest_approx);
            ++terms_found;
        }
        ++q;
    }
}

int main(void) {
    //q1a();
    //q1b();
}