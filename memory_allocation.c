#include<stdio.h>
#include<limits.h>
#include<math.h>
int buddy_system(int part,int page)
{
if(part<page)
{
part*=2;
printf("\nInserted @ partition with size = %d",part);
return part;
}
else
{
printf("\n%d\n",part);
printf("\n/ \t \\ \n \t %d",part/2);
return buddy_system(part/2,page);
}
}
int find_best(int part[],int n,int page)
{
int i,best=abs(part[0]-page),best_index=0;
//printf("%d",best);
for(i=0;i<n;i++)
{
if(part[i]!=0&&(abs(part[i]-page)<best))
{
best_index=i;
best=abs(part[i]-page);
}
//printf("\n%d",best);

}
return best_index;
}
void display(int part[],int n)
{
printf("\nAvailablity --");
int i;for(i=0;i<n;i++)printf("->%d",part[i]);
}
int checkfull(int part[],int n,int page)
{
//printf("000000");
int flag=0;
int i;
for(i=0;i<n;i++)
{
	if(part[i]<page)
	flag++;
}
if(flag==n)
{
int sum=0;
	for(i=0;i<n;i++)
	{
	sum+=part[i];
	if(sum>=page)
	break;
	}
if(i==n)
return 1;
else
return 2;
}
else
return 0;
}
void first_fit(int part[],int n,int page,int flag)
{
//printf("\nflag in first_fit() %d",flag);
	int i=0;
	if(flag==2)
	{
	//printf("\nInside");
		while(i<n)
		{
			if(part[i]!=0)
			{
			//printf("\n***");
			 if(part[i]<=page)
			 {
				//printf("\n\t+++");
				if(part[i]==page)
				{
				//printf("\n\t\t---");
					part[i]=0;
					printf("\nInserted @ %d ",i);
					break;
				}
				else
				{
					
					printf("\nInserted @ %d ",i);
					page-=part[i];
					//printf("\nPage===%d",page);
					part[i]=0;
					i++;
				}
			 }
			 else
			 {
			 	part[i]-=page;
				printf("\nInserted @ %d",i);
				break;
			 }
			}
			else
			i++;
		}	
	}
	else
	{
	while(i<n)
	{
		if(part[i]>=page)
		{
		part[i]-=page;
		printf("\nInserted @ %d ",i);
		break;
		}
		else
		i++;
	}
	}
display(part,n);
}
void best_fit(int part[],int n,int page,int flag)
{
//printf("$$$$");
int i=0;int best,best_index;
if(flag==2)
{
//printf("\nInside");
while(page>=0)
{
//printf("\n\tInside");
best_index=find_best(part,n,page);
	if(page>=part[best_index])
	{
		if(part[best_index]==page)
		{
		 part[best_index]=0;
		 //printf("\nInserted @ %d",best_index);
		 break;
		}
		else
		{
		//printf("\n\t\tInside...");
		page-=part[best_index];
		printf("\nInserted @ %d",best_index);
		part[best_index]=0;
		}
	}
	else
	{
	part[best_index]-=page;
	printf("\nInserted @ %d ",best_index);
	break;
	}
}
}
else
{
        //printf("HEllo form the other side!!");
	best=part[0];best_index=0;
	while(i<n)
	{
		if(part[i]<best&&part[i]>=page)
		{
		best=part[i];
		best_index=i;
		}	
        i++;
	}
	part[best_index]-=page;
	printf("\nInserted @ %d",best_index);
}
display(part,n);
}
void next_fit(int part[],int n,int page,int flag)
{
static int current=0;int i;
//printf("\ni=%d",current);
if(current==n)
i=0;
else
i=current;

	if(flag==2)
	{
	//printf("\nInside");
//int i=current+1;
		while(i<n)
		{
			if(part[i]!=0)
			{
			//printf("\n***");
			 if(part[i]<=page)
			 {
				//printf("\n\t+++");
				if(part[i]==page)
				{
				//printf("\n\t\t---");
					part[i]=0;
					printf("\nInserted @ %d ",i);
					current=i+1;
					break;
				}
				else
				{
					
					printf("\nInserted @ %d ",i);
					current=i+1;
					page-=part[i];
					//printf("\nPage===%d",page);
					part[i]=0;
					i++;
				}
			 }
			 else
			 {
			 	part[i]-=page;
				printf("\nInserted @ %d",i);
				current=i+1;
				break;
			 }
			}
			else
			i++;
		}	
	}
	else
	{
	while(i<n)
	{
		if(part[i]>=page)
		{
		part[i]-=page;
		printf("\nInserted @ %d ",i);
		current=i+1;
		//printf("\ni=%d",current);
		break;
		}
		else
		i++;
	}
	}
display(part,n);
}
void insert(int part[],int n,int page,int choice,int flag)
{
//printf("---------");
switch(choice)
{
	case 0:first_fit(part,n,page,flag);break;
	case 1:best_fit(part,n,page,flag);break;
	case 2:next_fit(part,n,page,flag);break;
}
}
void main()
{
int choice;
printf("\n How do you want to insert the page ? \n 0->First fit \n 1->Best fit \n 2->Next fit \n 3->Buddy system \n");
scanf("%d",&choice);
fflush(stdout);
if(choice<3)
{	
	int n;
	printf("\nEnter no partitions:");
	scanf("%d",&n);
	int partition[n];
	printf("\nEnter the size of partitions:");
	int i;
	for(i=0;i<n;i++)
	{
		scanf("%d",&partition[i]);
	}
	printf("\nThe paritions available are:\n");
	for(i=0;i<n;i++)
	printf("->%d",partition[i]);
	int page;int full_flag;
	do
	{
	printf("\nEnter page size to be inserted:");
	//printf("...");
	scanf("%d",&page);
	//printf("Hello!!!");
	full_flag=checkfull(partition,n,page);
	//printf("full_flag :%d",full_flag);
		if(full_flag==1)
		{
		printf("\nPage cannot be inserted...");
		}
		else
		{
		insert(partition,n,page,choice,full_flag);
		}
	}
        while(1);
}
else
{
int partition_size,page_size,part;
do
{
printf("\nEnter the partition size:");
scanf("%d",&partition_size);
printf("\nEnter the page size you wish to insert:");
scanf("%d",&page_size);
if(partion_size<page_size)
printf("\n Cannot insert ! Not enough space ...");
else
{
part=buddy_system(partition_size,page_size);
partition_size-=part;
printf("\nRemaining memory is %d ",partition_size);
}
}
while(1);
}
}
