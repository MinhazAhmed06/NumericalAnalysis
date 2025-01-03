#include <stdio.h>
#include <math.h>

#define N 3 
#define TOL 1e-6 
#define MAX_ITER 1000 

void printMatrix(int n, double A[n][n], double b[n]) {
	int i,j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%.3f\t", A[i][j]);
        }
        printf("| %10.4f\n", b[i]);
    }
    printf("\n");
}

void sur(int n, double A[n][n], double b[n], double x[n], double omega) {
	int i,iter,j;
    double x_old[n];
    for (i = 0; i < n; ++i) {
        x[i] = 0.0;
        x_old[i] = 0.0;
    }

    for (iter = 0; iter < MAX_ITER; ++iter) {
        double max_error = 0.0;
        
        for (i = 0; i < n; ++i) {
            double sum = 0.0;
            for (j = 0; j < n; ++j) {
                if (j != i) {
                    sum = sum + A[i][j] * x[j];
                }
            }
            
            double x_new = (1 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sum);
            max_error = fmax(max_error, fabs(x_new - x[i]));
            x[i] = x_new;
        }

        if (max_error < TOL) {
            break;
        }
    }
}

// Function to perform SOR iteration
int rfd(double A[N][N], double b[N], double omega, double x[N], int max_iter, double tol) {
    double x_new[N];
    int iter,i,j;
    for (iter = 0; iter < max_iter; iter++) {
        for (i = 0; i < N; i++) {
            x_new[i] = x[i];
        }
        for (i = 0; i < N; i++) {
            double sigma = 0.0;
            for (j = 0; j < N; j++) {
                if (j != i) {
                    sigma += A[i][j] * x_new[j];
                }
            }
            x_new[i] = (1 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sigma);
        }
        double norm_diff = 0.0;
        for (i = 0; i < N; i++) {
            norm_diff = fmax(norm_diff, fabs(x_new[i] - x[i]));
        }
        if (norm_diff < tol) {
            return iter + 1;
        }
        for (i = 0; i < N; i++) {
            x[i] = x_new[i];
        }
    }
    return iter;
}

int main() {
	int i;
    double A[N][N] = {
        {4, 1, 2},
        {3, 5, 1},
        {1, 1, 3}
    };
    double b[N] = {4, 7, 3};
    double x[N] = {0, 0, 0}; 
    double omega, best_omega;
    int best_iter = MAX_ITER;

    for (omega = 0.05; omega < 1.0; omega += 0.05) {
        double x_temp[N] = {0, 0, 0}; 
        int iter = rfd(A, b, omega, x_temp, MAX_ITER, TOL);
        if (iter < best_iter) {
            best_iter = iter;
            best_omega = omega;
        }
    }
    
    sur(3,A,b,x,best_omega);

    printf("Optimal omega: %.3f, Iterations: %d\n", best_omega, best_iter);
    
    printf("\n Matrix A and vector b:\n");
    printMatrix(3, A, b);

    printf("\n Solution vector x:\n");
    for (i = 0; i < 3; ++i) {
        printf("%.3f\n", x[i]);
    }

    return 0;
}