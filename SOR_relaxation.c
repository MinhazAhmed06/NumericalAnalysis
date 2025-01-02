#include <stdio.h>
#include <math.h>

void main() {
    float a[10][10], b[10], x[10], xn[10], epp = 0.00001, sum, w;
    int i, j, flag, n;

    // Input number of variables and coefficient matrix
    printf("\nEnter the number of variables: ");
    scanf("%d", &n);
    printf("Enter the coefficient matrix (rowwise):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%f", &a[i][j]);

    // Input right-hand vector
    printf("\nEnter the right-hand vector: ");
    for (i = 0; i < n; i++)
        scanf("%f", &b[i]);

    // Input relaxation factor
    printf("\nEnter the relaxation factor w: ");
    scanf("%f", &w);

    // Initialize solution vector to 0
    for (i = 0; i < n; i++) x[i] = 0;

    printf("\nIteration results:\n");
    
    do {
        flag = 0; // Indicate if convergence is achieved
        
        for (i = 0; i < n; i++) {
            sum = b[i];
            for (j = 0; j < n; j++) {
                if (i != j) 
                    sum -= a[i][j] * x[j];
            }
            xn[i] = (sum) / a[i][i]; // Update new solution
        }

        // Display current iteration results
        for (i = 0; i < n; i++) 
            printf("  %8.5f  ", xn[i]);
        printf("\n");

        // Check if convergence is reached
        for (i = 0; i < n; i++) {
            if (fabs(x[i] - xn[i]) > epp) {
                flag = 1;
                break;
            }
        }

        // Update solution vector for next iteration
        if (flag == 1) 
            for (i = 0; i < n; i++) 
                x[i] = xn[i];

    } while (flag == 1);

    // Display final solution
    printf("\nFinal solution is:\n");
    for (i = 0; i < n; i++)
        printf("  %8.5f  ", xn[i]);
}
