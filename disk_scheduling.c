#include<stdio.h>
#include<math.h>
#include<limits.h>
void sort(int temp[],int n,int flag)
{
int j,t,k;
for(j=0;j<flag-1;j++)
{
for(k=j+1;k<flag;k++)
{
if(temp[k]<temp[j])
{
t=temp[k];
temp[k]=temp[j];
temp[j]=t;
}
}
}
for(j=flag;j<n-1;j++)
{
for(k=j+1;k<n;k++)
{
if(temp[k]>temp[j])
{
t=temp[k];
temp[k]=temp[j];
temp[j]=t;
}
}
}
}
int find_above(int tracks[],int n,int init)
{
int j,next=INT_MAX,flag;int temp[n];int k=0;
for(j=0;j<n;j++)
{
if(tracks[j]>=init)
temp[k++]=tracks[j];
}
flag=k;
for(j=0;j<n;j++)
if(tracks[j]<init)
temp[k++]=tracks[j];
sort(temp,n,flag);
for(j=0;j<n;j++)
{
tracks[j]=temp[j];
//printf("\n%d",tracks[j]);
}
return flag;
}
void display(int a[],int n)
{
int i;
printf("\n");
for(i=0;i<n;i++)
{
printf("%d->",a[i]);
}
printf("\n");
}
void swap(int tracks[],int n,int cur,int i)
{
int j;int temp;
for(j=0;j<n-i;j++)
{
if(tracks[j]==cur)
{
temp=tracks[j];
tracks[j]=tracks[(n-i)-1];
tracks[(n-i)-1]=temp;
break;
}
}
//display(tracks,n);
}
int find_next(int tracks[],int n,int i,int cur)
{
int j,next=INT_MAX;int next_index;
for(j=0;j<n-i;j++)
{
if(tracks[j]!=cur)
{
if(abs(tracks[j]-cur)<next)
{
next=abs(tracks[j]-cur);
next_index=tracks[j];
//printf("\n^%d\n",next);
}
}
}
//printf("\n%d",next);
swap(tracks,n,next_index,i);
return next_index;
}
void scan(int tracks[],int n,int init,int high,int low)
{
int flag,tracks_switched=0;
flag=find_above(tracks,n,init);
tracks_switched=abs(init-tracks[0]);
int i;
printf("\n%d->",init);
for(i=1;i<=flag;i++)
{
printf("%d -> ",tracks[i-1]);
tracks_switched+=abs(tracks[i]-tracks[i-1]);
}
tracks_switched+=abs(high-tracks[i-2]);
printf("%d ->",high);
for(i=flag+1;i<n;i++)
{
printf("%d -> ",tracks[i-1]);
tracks_switched+=abs(tracks[i]-tracks[i-1]);
}
printf("%d",tracks[i-1]);
printf("\nTracks Switched = %d",tracks_switched);

}
void fcfs(int tracks[],int n,int init)
{
int tracks_switched=0;tracks_switched=abs(init-tracks[0]);
int i;
printf("\n%d->",init);
for(i=1;i<n;i++)
{
printf("%d -> ",tracks[i-1]);
tracks_switched+=abs(tracks[i]-tracks[i-1]);
}
printf("%d",tracks[i-1]);
printf("\nTracks Switched = %d",tracks_switched);
}
void ssts(int tracks[],int n,int init)
{
int next,i;int tracks_switched=0;int cur=init;
printf("%d -> ",init);
for(i=0;i<n;i++)
{
next=find_next(tracks,n,i,cur);
printf("%d -> ",next);
tracks_switched+=abs(cur-next);
cur=next;
}
printf("\nTracks Switched = %d",tracks_switched);
}
void main()
{
int n,i,init_head_pos;
printf("\nEnter the no. of track request in queue:");
scanf("%d",&n);
int tracks[n];
printf("\nEnter the requests:\n");
for(i=0;i<n;i++)
scanf("%d",&tracks[i]);
printf("\nEnter initial head position:");
scanf("%d",&init_head_pos);
int low,high;
printf("\nEnter disk range:(Low and High)");
scanf("%d",&low);
scanf("%d",&high);
int choice;
printf("\nEnter the type of scheduling ,\n 0. FCFS \n 1. SSTS \n 2.SCAN \n:");
scanf("%d",&choice);
switch(choice)
{
case 0:fcfs(tracks,n,init_head_pos);break;
case 1:ssts(tracks,n,init_head_pos);break;
case 2:scan(tracks,n,init_head_pos,high,low);break;
default:printf("\nInvalid choice...");break;
}
}
