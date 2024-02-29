#include <stdio.h>
#include <math.h>

double min(double a, double b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int q1a_helper(double closest_approx, int p, int q) {

    double new_closest_approx = closest_approx;
    double bestp = p;

    for (double thisp = 1; thisp <= 142; ++thisp) {
        if (fabs(thisp / q - sqrt(2)) < fabs(new_closest_approx - sqrt(2))) {
            new_closest_approx = thisp/q;
            bestp = thisp;
        }
    }

    return bestp;
}


// Prints each term of the sequence for (a)
void print_q1a(int p, int q, double closest_approx) {

    printf("l(%d, %d) = |√2 - %d/%d| = |√2 - %lf| = %.*lf\n", p, q, p, q, closest_approx, 20, fabs(sqrt(2) - closest_approx));
}

void q1a() {
    int p = 1;
    double closest_approx = 1;

    print_q1a(1, 1, closest_approx);

    for (int q = 2; q <= 100; ++q) {

        p = q1a_helper(closest_approx, p, q);

        closest_approx = fabs((double)p/q);

        print_q1a(p, q, closest_approx);

    }

}

int main(void) {
    q1a();
}