#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
	int r[20],n,i,cp,mov=0,st=6;
	printf("ENTER NUMBER OF REQUEST\n");
	scanf("%d",&n);
	printf("ENTER REQUEST ORDER\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&r[i]);
	}
	printf("ENTER CURRENT POSITION(STARTING POSITION)\n");
	scanf("%d",&cp);
	mov = mov + abs(cp-r[0]);
	printf("%d -> %d",cp,r[0]);
	for(i=1;i<n;i++)
	{
		mov = mov + abs(r[i] - r[i-1]);
		printf(" -> %d ",r[i]);
	}
	printf("\nTOTAL HEAD MOBEMENT: %d\n",mov);
	printf("TOTAL SEEK TIME: %dmsec\n",(mov*st));
	
}
