/*
 *
 * Written by Dietrich Geisler
 * Last Modified 1/10/16
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double p(double x, double t, double D);

int main() {
    FILE* ofile;
    int i, j;
    double fidelity, range, sig, t, x;

    fidelity = 1;
    range = 5;
    sig = 3;
    ofile = fopen("analytical_results.txt", "w");

    for (i = 0; i < 10; i++) {
	t = 10*(i+1);
	printf("For sig=%f\tt=%f\t\n", sig, t);
	fprintf(ofile, "For sig=%f\tt=%f\t\n", sig, t);
	for (j = 0; j <= (int)2*range/fidelity; j++) {
	    x = fidelity*j-range;
	    printf("x=%f\tp=%f\n", x, p(x, t, sig*sig/2));
	    fprintf(ofile, "x=%f\tp=%f\n", x, p(x, t, sig*sig/2));
	}
	printf("\n");
	fprintf(ofile, "\n");
    }

    fclose(ofile);
}

double p(double x, double t, double D) {
    double e = 2.718281828459045;
    double pi = 3.141592653589793;
    double val1 = pow(e, -(x*x)/(4*D*t));
    double val2 = sqrt(4*pi*D*t);
    return val1/val2;
}
