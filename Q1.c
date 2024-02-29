#include <stdio.h>
#include <math.h>

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

// Prints each term of the sequence for (a)
void print_q1a(int p, int q, double closest_approx) {

    printf("l(%d, %d) = |√2 - %d/%d| = |√2 - %.*lf| = %.*lf\n", p, q, p, q, 20, closest_approx, 20, fabs(sqrt(2) - closest_approx));
}

void q1a() {

    int terms_found = 0;
    int p = 1;
    double closest_approx = 1;

    // begin with p=1, q=1
    print_q1a(1, 1, closest_approx);

    int q = 275807;

    while (terms_found <= 3) {
        p = q1a_helper(closest_approx, q);

        if (p > 0) {
            closest_approx = fabs((double)p/q);
            print_q1a(p, q, closest_approx);
            ++terms_found;
        }

        ++q;
    }
}

int main(void) {
    q1a();
}