#include <stdio.h>
#include <stdlib.h>

void TriDiag(float a[], float b[], float c[], float d[], float x[], int n);

int main() {
    int n, i;
    printf("Enter the size of the coefficient matrix: ");
    scanf("%d", &n);

    float a[n], b[n], c[n], d[n], x[n];

    printf("Enter the first row (non-zero elements): ");
    scanf("%f %f", &b[0], &c[0]);

    printf("Enter rows 2 to n-1:\n");
    for (i = 1; i < n - 1; i++) 
        scanf("%f %f %f", &a[i], &b[i], &c[i]);

    printf("Enter the last row: ");
    scanf("%f %f", &a[n - 1], &b[n - 1]);

    printf("Enter the right-hand side vector: ");
    for (i = 0; i < n; i++) 
        scanf("%f", &d[i]);

    TriDiag(a, b, c, d, x, n);

    printf("The solution is:\n");
    for (i = 0; i < n; i++) 
        printf("%f ", x[i]);

    return 0;
}

void TriDiag(float a[], float b[], float c[], float d[], float x[], int n) {
    float b1[n], d1[n];
    int i;

    b1[0] = b[0];
    for (i = 1; i < n; i++) {
        if (b1[i - 1] == 0.0) {
            printf("A minor is zero: Method fails\n");
            exit(1);
        }
        b1[i] = b[i] - a[i] * c[i - 1] / b1[i - 1];
    }

    d1[0] = d[0];
    for (i = 1; i < n; i++) 
        d1[i] = (d[i] - a[i] * d1[i - 1]) / b1[i];

    x[n - 1] = d1[n - 1];
    for (i = n - 2; i >= 0; i--) 
        x[i] = d1[i] - c[i] * x[i + 1]/ b1[i];
}