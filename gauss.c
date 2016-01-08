/*
 *
 * Written by Dietrich Geisler
 * Last Modified 1/6/16
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double displacement(int n, double sig);
double gauss(double sig, int fidelity);
double average(double* vals, int size);

int main() {
    srand((unsigned)time(NULL));

    FILE* ofile;
    double* vals, * avgs,* mean_sqr;
    int i, j, n, size, count;

    size = 10000;
    count = 10;
    vals = malloc(size*sizeof(double));
    avgs = malloc(count*sizeof(double));
    mean_sqr = malloc(count*sizeof(double));

    printf("n\tmean\t\tmean_sqr\n");

    for (i = 0; i < count; i++) {
	n = 10*(i +1);
	for (j = 0; j < size; j++) {
	    vals[j] = displacement(n, 1);
	}
	avgs[i] = average(vals, size);
	for (j = 0; j < size; j++) {
	    vals[j] = pow(vals[j], 2);
	}
	mean_sqr[i] = average(vals, size);
	printf("%i\t%f\t%f\n", 10*(i+1), avgs[i], mean_sqr[i]);
    }

    ofile = fopen("gauss_results.txt", "w");
    fprintf(ofile, "n\tmean\t\tmean_sqr\n");
    for (i = 0; i < count; i++) {
	fprintf(ofile, "%i\t%f\t%f\n", 10*(i+1), avgs[i], mean_sqr[i]);
    }
    fclose(ofile);

    return 0;
}

double displacement(int n, double sig) {
    int i;
    double to_return = 0;
    for (i = 0; i < n; i++) {
	to_return += gauss(sig, 1000);
    }
    return to_return;
}

double gauss(double sig, int fidelity) {
    double to_return = 0;
    int i;
    for (i = 0; i < fidelity; i++) {
	double r = ((double)rand()/(double)RAND_MAX);
	to_return += (2*r - 1) * sqrt(3)*sig;
    }
    to_return = to_return / sqrt(fidelity);
    return to_return;
}

double average(double* vals, int size) {
    double sum = 0;
    int i;
    for (i = 0; i < size; i++) {
	sum += vals[i];
    }
    return sum / size;
}
