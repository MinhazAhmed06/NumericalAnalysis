#include <stdio.h>
#include <math.h>

#define N 3
#define TOL 1e-6
#define MAX_ITER 1000

// Function to print matrix A and vector b
void printMatrix(int n, double A[n][n], double b[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%.3f\t", A[i][j]);
        }
        printf("| %.4f\n", b[i]);
    }
    printf("\n");
}

// Function to perform SOR iteration and return number of iterations
int rfd(double A[N][N], double b[N], double omega, double x[N], int max_iter, double tol) {
    double x_new[N];
    for (int iter = 0; iter < max_iter; iter++) {
        for (int i = 0; i < N; i++) {
            x_new[i] = x[i];
        }
        for (int i = 0; i < N; i++) {
            double sigma = 0.0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sigma += A[i][j] * x_new[j];
                }
            }
            x_new[i] = (1 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sigma);
        }
        double norm_diff = 0.0;
        for (int i = 0; i < N; i++) {
            norm_diff = fmax(norm_diff, fabs(x_new[i] - x[i]));
        }
        if (norm_diff < tol) {
            return iter + 1;
        }
        for (int i = 0; i < N; i++) {
            x[i] = x_new[i];
        }
    }
    return max_iter;
}

int main() {
    double A[N][N] = {
        {4, 1, 2},
        {3, 5, 1},
        {1, 1, 3}
    };
    double b[N] = {4, 7, 3};
    double x[N] = {0, 0, 0};
    double omega, best_omega;
    int best_iter = MAX_ITER;

    // Find the optimal omega by testing values between 0.05 and 1.0
    for (omega = 0.05; omega < 1.0; omega += 0.05) {
        double x_temp[N] = {0, 0, 0};
        int iter = rfd(A, b, omega, x_temp, MAX_ITER, TOL);
        if (iter < best_iter) {
            best_iter = iter;
            best_omega = omega;
        }
    }

    // Perform SOR with the optimal omega
    rfd(A, b, best_omega, x, MAX_ITER, TOL);

    printf("Optimal omega: %.3f, Iterations: %d\n", best_omega, best_iter);

    printf("\nMatrix A and vector b:\n");
    printMatrix(N, A, b);

    printf("\nSolution vector x:\n");
    for (int i = 0; i < N; ++i) {
        printf("%.3f\n", x[i]);
    }

    return 0;
}
