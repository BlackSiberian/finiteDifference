#include <stdio.h>
#include <math.h>

#define T 1.0
#define tau 0.05
#define h 0.01

void initialConditions(double *u0, double *u1) {
    int nx = 1 / h;
    for(int i = 0; i < nx; i++){
        u0[i] = 2 * cos(h * i);
        u1[i] = u0[i] + 2 * sin(h * i) * tau;
    }
}

void boundaryConditions(double *u, int t) {
    int nx = 1 / h;
    u[0] =(h * 2 * (cos(t * tau) - sin (t * tau)) + u[1]) / (h + 1);
    u[nx-1] = h * 2 * cos(1 - t * tau) / h;
}

void equation(double (*u)[(int)(T / tau)], int t) {
    int nx = 1 / h;
    for(int i = 1; i < nx - 1; i++) 
        u[t+1][i] = 2 * u[t][i] - u[t-1][i] + pow(tau / h, 2) * 0.5 * (u[t][i+1] - 2 * u[t][i] + u[t][i-1]) + pow(tau, 2) * (-1) * (cos(t * tau - i * h)); 
}

int main() {
    int nx = 1 / h; // Number of elements along X axis
    int nt = T / tau; // Number of elements along T axis
    double u[nt][nx]; // Initialize function values table

    initialConditions(u[0], u[1]);
    
    // Counting values for each step
    for(int t = 2; t < nt; t++) {
        equation(u, t-1);
        boundaryConditions(u[t], t);
    }

    // Printing values to the file
    FILE *table = fopen("values.csv", "w");
    fprintf(table, "%lf;%lf;%lf\n", h, T, tau);
    for(int i = 0; i < nx-1; i++) 
        fprintf(table, "%lf;", u[nt-1][i]);
    fprintf(table, "%lf", u[nt-1][nx-1]);
    fclose(table);
    return 0;
}