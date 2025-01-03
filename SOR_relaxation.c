#include<stdio.h>
#include<math.h>
void main()
{
	float a[10][10],b[10],x[10],xn[10],epp=0.00001,sum,w;
	int i,j,flag,n;
	printf("\nEnter the number the variables= ");
	scanf("%d",&n);
	printf("Enter the coefficient matrix rowwise:\n");
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%f",&a[i][j]);
	printf("\nEnter the right hand vector: ");
	for(i=1;i<=n;i++)
		scanf("%f",&b[i]);
	printf("\nEnter the relaxtion factor w= ");
		scanf("%f",&w);
	for(i=1;i<=n;i++)
		x[i]=0; //Initialize 
	for(i=1;i<=n;i++)
		printf("    x[%d]    ",i);
	printf("\n");
	do
	{
		for(i=1;i<=n;i++){
			sum=b[i]*w+a[i][i]*x[i];
			for(j=1;j<=n;j++){
				if(j<i)
					sum=sum-a[i][j]*xn[j]*w;
				else if(j>=i)
					sum =sum-a[i][j]*x[j]*w;
				xn[i]=sum/a[i][i];
			}
		}
			for(i=1;i<=n;i++)
				printf("  %8.5f  ",xn[i]);
			printf("\n");
			flag=0; //Indecates |x[i]-xn[i]|<epp for all i
			for(i=1;i<=n;i++)
				if(fabs(x[i]-xn[i])>epp)
					flag=1;
			if(flag==1)
				for(i=1;i<=n;i++)
					x[i]=xn[i]; //Reset x[i]
	}
	while(flag==1);
	printf("Solution is- \n");
	for(i=1;i<=n;i++)
		printf("  %8.5f  ",xn[i]);
}