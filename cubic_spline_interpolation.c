#include <stdio.h>
#include <stdlib.h>

float z[101]; // Solution array for TDMA

// Function to solve a tridiagonal matrix using TDMA
void TDMA(float p[101], float q[101], float r[101], float s[101], int n) {
    for (int i = 1; i < n; i++) { // Adjusted indexing to fit TDMA
        float factor = p[i] / q[i - 1];
        q[i] -= factor * r[i - 1];
        s[i] -= factor * s[i - 1];
    }

    z[n - 1] = s[n - 1] / q[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        z[i] = (s[i] - r[i] * z[i + 1]) / q[i];
    }
}

int main() {
    int n, k = -1;
    float f[101], x[101], a[101], b[101], c[101], d[101];
    float p[101], q[101], r[101], s[101], h[101], xp, value;

    printf("Enter the number of tabulated points (n): ");
    scanf("%d", &n);

    printf("Enter the x and f(x) values:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%f", &x[i]);
        printf("f[%d]: ", i);
        scanf("%f", &f[i]);
    }

    printf("Enter the value of x at which the cubic polynomial is to be determined: ");
    scanf("%f", &xp);

    // Compute h values
    for (int i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
    }

    // Compute coefficients for TDMA
    for (int i = 1; i < n - 1; i++) {
        p[i] = h[i - 1];
        q[i] = 2 * (h[i - 1] + h[i]);
        r[i] = h[i];
        s[i] = 3 * ((f[i + 1] - f[i]) / h[i] - (f[i] - f[i - 1]) / h[i - 1]);
    }

    // Boundary conditions
    p[0] = r[n - 1] = 0;
    q[0] = q[n - 1] = 1;
    s[0] = s[n - 1] = 0;

    // Solve for c using TDMA
    TDMA(p, q, r, s, n);

    // Calculate coefficients a, b, c, d
    for (int i = 0; i < n - 1; i++) {
        a[i] = f[i];
        c[i] = z[i];
        b[i] = (f[i + 1] - f[i]) / h[i] - h[i] * (2 * c[i] + z[i + 1]) / 3;
        d[i] = (z[i + 1] - c[i]) / (3 * h[i]);
    }

    // Display the cubic polynomials
    printf("The coefficients of the cubic polynomials are:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("s[%d](x) = %.6f + %.6f*(x - %.6f) + %.6f*(x - %.6f)^2 + %.6f*(x - %.6f)^3\n",
               i, a[i], b[i], x[i], c[i], x[i], d[i], x[i]);
    }

    // Evaluate the spline at xp
    for (int i = 0; i < n - 1; i++) {
        if (xp >= x[i] && xp <= x[i + 1]) {
            k = i;
            break;
        }
    }

    if (k != -1) {
        value = a[k] + b[k] * (xp - x[k]) + c[k] * (xp - x[k]) * (xp - x[k]) +
                d[k] * (xp - x[k]) * (xp - x[k]) * (xp - x[k]);
        printf("\nThe value of the cubic polynomial at x = %.6f is %.6f\n", xp, value);
    } else {
        printf("\nThe value x = %.6f is outside the interpolation range.\n", xp);
    }

    return 0;
}
