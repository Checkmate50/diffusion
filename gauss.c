/*
 *
 * Written by Dietrich Geisler
 * Last Modified 1/7/16
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int displacement_death(int n, double sig, double range, double* pos);
double displacement(int n, double sig);
double gauss(double sig, int fidelity);
double average(double* vals, int size);

int main() {
    srand((unsigned)time(NULL));

    FILE* ofile;
    double* vals, * avgs,* mean_sqr, *pos;
    int* hist_vals;
    int i, j, n, size, count, live;

    size = 10000;
    count = 10;
    vals = malloc(size*sizeof(double));
    avgs = malloc(count*sizeof(double));
    mean_sqr = malloc(count*sizeof(double));

    //Calculates the mean and mean-squared displacement with sig=1
    /*printf("n\tmean\t\tmean_sqr\n");

    for (i = 0; i < count; i++) {
	n = 10*(i +1);
	for (j = 0; j < size; j++) {
	    vals[j] = displacement(n, 3);
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
    fclose(ofile);*/

    //Calculates the probability that a particle will live
    /*ofile = fopen("gauss_results.txt", "w");
    printf("n\tp(live)\tsig=0.1\n");
    fprintf(ofile, "n\tp(live)\tsig=0.1\n");
    for (i = 0; i < count; i++) {
	n = 10*(i +1);
	live = 0;
	for (j = 0; j < size; j++) {
	    live += displacement_death(n, .1, 0.5, pos);
	}
	printf("%i\t%f\n", 10*(i+1), (double)live/(double)size);
	fprintf(ofile, "%i\t%f\n", 10*(i+1), (double)live/(double)size);
    }
    fclose(ofile);*/

    //Creates a histogram of the final positions of particles that live
    ofile = fopen("gauss_results.txt", "w");
    n = 50;
    hist_vals = malloc(100*sizeof(int));
    pos = malloc(sizeof(double));
    for (i = 0; i < 100; i++) {
	hist_vals[i] = 0;
    }
    for (i = 0; i < size; i++) {
	if (displacement_death(n, .1, .5, pos)) {
	    j = (int)((*pos+.5)*100);
	    hist_vals[j]++;
	    printf("%f\t%i\n", *pos, hist_vals[j]);
	    fprintf(ofile, "%f\t%i\n", *pos, hist_vals[j]);
	}
    }

    return 0;
}

int displacement_death(int n, double sig, double range, double* pos) {
    int i;
    *pos = 0;
    for (i = 0; i < n; i++) {
	*pos += gauss(sig, 1000);
	if (*pos > range || *pos < -range) {
	    return 0;
	}
    }
    return 1;
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
