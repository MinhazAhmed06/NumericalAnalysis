#include<stdio.h>
#include<math.h>
void main ()
{
	int i,j,k,n;
	float a[20][20],l[20][20],u[20][20],b[20],z[20],x[20];
	printf("\n Enter the size of the cofficient matrix A:");
	scanf("%d",&n);
	printf("\n Enter the element of the matrix rowwise\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			scanf("%f",&a[i][j]);
	}
	printf("\n Enter the right hand vector b:  ");
	for(i=1;i<=n;i++)
		scanf("%f",&b[i]);
	//for l[i][1]
	for(i=1;i<=n;i++)
		l[i][1]=a[i][1];
	//for u[1][j]
	for(j=2;j<=n;j++)
		u[1][j]=a[1][j]/l[1][1];
	//for u[i][i]
	for(i=1;i<=n;i++)
		u[i][i]=1;
	//for l[i][j] and u[i][j]
	for(i=2;i<=n;i++)
	{
		for(j=2;j<=n;j++)
		{
			if(i>=j)
			{
				l[i][j]=a[i][j];
				for(k=1;k<=j-1;k++)
					l[i][j]=l[i][j]-(l[i][k]*u[k][j]);
			}
			else
			{
				u[i][j]=a[i][j];
				for(k=1;k<=i-1;k++)
					u[i][j]=u[i][j]-(l[i][k]*u[k][j]);
				u[i][j]=u[i][j]/l[i][i];
			}
		}
	}
	printf("\n The lower trianguler matrix L= \n");
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
			printf("%f  ",  l[i][j]);
		printf(" \n");
	}
	printf("\n The upper Trangular matrix U= \n");
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
			printf("%f  ",  u[i][j]);
		printf(" \n");
	}
	z[1]=b[1]/l[1][1];
	for(i=2;i<=n;i++)
	{
		z[i]=b[i];
		for(j=1;j<=i-1;j++)
			z[i]=z[i]-(l[i][j]*z[j]);
		z[i]=z[i]/l[i][i];
	}
	x[n]=z[n];
	for(i=n-1;i>=1;i--)
	{
		x[i]=z[i];
		for(j=i+1;j<=n;j++)
			x[i]=x[i]-(u[i][j]*x[j]);
	}
	printf("\n Solution is ");
	for(i=1;i<=n;i++)
		printf("%f ", x[i]);
}