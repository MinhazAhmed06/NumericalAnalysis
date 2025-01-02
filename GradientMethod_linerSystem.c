// SOLUTION OF THE LINEAR SYSTEM OF EQUATION BY CONJUGATE GRADIENT METHOD //
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int N;
    // Input size of the matrix
    printf("Enter the size of the matrix (N x N): ");
    scanf("%d", &N);

    double A[N][N];
    double b[N], x[N];
    double r[N], p[N], Ap[N];
    double alpha, beta, r_norm, r_norm_new;

    printf("Enter the elements of the matrix A (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Enter the elements of the solution vector b (%d elements):\n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%lf", &b[i]);
    }

    for (int i = 0; i < N; i++)
    {
        x[i] = 0; // Initial guess
    }

    for (int i = 0; i < N; i++)
    {
        r[i] = b[i];
        for (int j = 0; j < N; j++)
        {
            r[i] -= A[i][j] * x[j];
        }
        p[i] = r[i];
    }

    // Conjugate Gradient iteration
    for (int k = 0; k < N; k++)
    {
        // Compute Ap = A * p
        for (int i = 0; i < N; i++)
        {
            Ap[i] = 0;
            for (int j = 0; j < N; j++)
            {
                Ap[i] += A[i][j] * p[j];
            }
        }

        r_norm = 0;
        double pAp = 0;
        for (int i = 0; i < N; i++)
        {
            r_norm += r[i] * r[i];
            pAp += p[i] * Ap[i];
        }
        alpha = r_norm / pAp;
        // Update solution x = x + alpha * p
        for (int i = 0; i < N; i++)
        {
            x[i] += alpha * p[i];
        }
        // Update residual r = r - alpha * Ap
       for (int i = 0; i < N; i++)
         {
          r[i] -= alpha * Ap[i];
         }

        // Check for convergence
        r_norm_new = 0;
        for (int i = 0; i < N; i++)
        {    
    		r_norm_new += r[i] * r[i];
		}
		if (r_norm_new <= 1e-10)
		{
    	break;
		}

		// Compute beta = (r_new^T * r_new) / (r^T * r)
		beta = r_norm_new / r_norm;
		// Update direction p = r + beta * p
		for (int i = 0; i < N; i++)
		{
    		p[i] = r[i] + beta * p[i];
		}
	}

printf("Solution:\n");
for (int i = 0; i < N; i++)
{
    printf("x[%d] = %.6f\n", i, x[i]);
}
return 0;
}