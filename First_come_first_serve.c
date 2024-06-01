#include <stdio.h>
void fcfs(int pro[],int bt[],int n);
void main()
{
    int bt[10];
    int pro[10];
    int n;
    printf("Enter no. of process\n");
    scanf("%d",&n);
    printf("Enter process name\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pro[i]);
    }
    printf("Enter brust time of process respectively\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&bt[i]);
    }
    fcfs(pro,bt,n);
}
void fcfs(int pro[],int bt[],int n)
{
	int wt[10]={0}, tt[10]={0},sum_wt=0,i,sum_tt=0;
	float avg_wt,avg_tt;
	for(i=1;i<n;i++)
	{
		wt[i]=wt[i-1]+bt[i-1];
		
	}
	for(i=1;i<n;i++)
	{
		tt[i]=wt[i]+bt[i];
		
	}

	printf("\nPROCESS\t\tBURST TIME\t\tWAITING TIME\t\tTURNAROUND TIME\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t%d\t\t\t%d\t\t\t%d",pro[i],bt[i],wt[i],tt[i]);
		printf("\n");
	}
	for(i=1;i<n;i++)
	{
		sum_wt=sum_wt+wt[i];
		
	}
	avg_wt=(float)sum_wt/n;
	printf("\nAverage waititng Time %f\n",avg_wt);
	for(i=1;i<n;i++)
	{
		sum_tt=sum_tt+tt[i];
		
	}
	avg_tt=(float)sum_tt/n;
	printf("\nAverage waititng Time %f\n",avg_tt);
	
	
	
}