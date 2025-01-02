//finding inverse and det of a matrix
#include<stdio.h>
#include<math.h>
void swap(float *a, float *b) /* swapping function */
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void main()
{
    float a[30][30], temp,det=1;
    int i,j,k,n,p;
    printf("Enter the size of the matrix= ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("Please enter a[%d][%d]= ", i+1, j+1);
            scanf("%f", &a[i][j]);
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=n; j<2*n; j++)
        {
            if(j==i+n)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(fabs(a[i][i]) < fabs(a[j][i])) /* partial pivoting */
            {
                for(k=0; k<2*n; k++)
                    swap(&a[i][k], &a[j][k]);
            }
            p=pow(-1,j);
        }
    }
    for(i=0; i<n; i++) /* it transforms the user given matrix into upper triangular matrix */
    {
        for(j=i+1; j<n; j++)
        {
            temp = a[j][i] / a[i][i];
            for(k=0; k<2*n; k++)
            {
                a[j][k] = a[j][k] - temp * a[i][k];
            }
        }
        det=det*a[i][i]*p;
    }
    for(i=n-1; i>=0; i--) /* it transforms the upper triangular matrix into an identity matrix */
    {
        temp = a[i][i];
        for(k=0; k<2*n; k++)
        {
            a[i][k] = a[i][k] / temp;
        }
        for(j=i-1; j>=0; j--)
        {
            temp = a[j][i];
            for(k=0; k<2*n; k++)
            {
                a[j][k] = a[j][k] - a[i][k] * temp;
            }
        }
    }
    // Print the determinant
    printf("\n Determinant of the matrix is: %f\n", det);
    printf("\n The inverse is:-\n ");
    for(i=0; i<n; i++)
    {
        for(j=n; j<2*n; j++)
        {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
}