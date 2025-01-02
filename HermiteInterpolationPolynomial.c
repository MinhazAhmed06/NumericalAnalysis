/* HERMITE INTERPOLATION */
#include<stdio.h>
#include<math.h>
void main()
{
	int i,j,k,n;
	float x[100],y[100],yd[100],L[100],Ld[100],xp,sum,sum1,sum2,sum3,prod;
	printf("\nNumbers of tabular points n(0,1,2,...,n) is= ");
	scanf("%d",&n);
	printf("Tabular points\nx	\ty	\tyd	\n");
	for(i=0;i<=n;i++)
	{
		scanf("%f%f%f",&x[i],&y[i],&yd[i]);
	}
	printf("\nInterpolating point xp= ");
	scanf("%f",&xp);
	printf(" The values of Lagrangian function and its derivative:\n");
	for(i=0;i<=n;i++)
	{
		prod=1;
		for(j=0;j<=n;j++)
		{
			if(j!=i)
			{
				prod=prod*(xp-x[j])/(x[i]-x[j]);
			}
		}
		L[i]=prod;
		sum=0;
		for(k=0;k<=n;k++)
		{
			if(k!=i)
			{
				sum=sum+1/(x[i]-x[k]);
			}
		}
		Ld[i]=sum;
		printf("\n L[%d]=%f Ld[%d]=%f\n",i,L[i],i,Ld[i]);
	}
	printf("-----------------------------\n");
	sum1=0;
	sum2=0;
	for(i=0;i<=n;i++)
	{
		sum1=sum1+(1-2.0*(xp-x[i])*Ld[i])*L[i]*L[i]*y[i];
		sum2=sum2+(xp-x[i])*L[i]*L[i]*yd[i];
	}
	printf("sum1=%f\nsum2=%f\n",sum1,sum2);
	sum3=sum1+sum2;
	printf("\nsum3=%f+%f=%f\n",sum1,sum2,sum3);
	printf("\n The required value of y(%f) is equal to %f\n",xp,sum3);
} 
