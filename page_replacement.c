#include<stdio.h>
#include<limits.h>
void display(int frame[],int n)
{
int i;for(i=0;i<n;i++)
{
printf("\n%d",frame[i]);
}
}
int search(int frame[],int n,int ele)
{
int i;
for(i=0;i<n;i++)
{
if(frame[i]==ele)
{
break;
}
}
if(i!=n)
return 1;
else
return 0;
}
void optimal(int page_req[],int n,int fsize)
{
  int i,j;int frame[fsize];int farthest;int k=0;int l;int dist;int farthest_index,pg_fault_count=0;
  for(i=0;i<n;i++)
  { 
    printf("\nPage requested: %d",page_req[i]);
    if(k<fsize)
    {
      if((search(frame,k,page_req[i])==1))
      { 
             printf("\nPage Hit !\n");
      }
      else
      {
     frame[i]=page_req[i];
     k++;
     pg_fault_count++;
      }
    }
    else
    {  
       if((search(frame,fsize,page_req[i])==1))
       {
        printf("\nPage Hit !\n");
       }
       else
       {
       //dist=0;
       farthest=0;
       for(l=0;l<fsize;l++)
       { 
          //printf("\nFor %d",frame[l]);
          dist=0;
          for(j=i+1;j<n;j++)
          {
              if(page_req[j]==frame[l])
                  break;
              else
                  dist++;               
          }
          //printf("distance is %d",dist);
          if(dist>farthest)
          {
          farthest=dist;
          farthest_index=l;
          }
       //dist=0;
       }
       //printf("\n Farthest is %d",frame[farthest_index]);
       frame[farthest_index]=page_req[i];
       pg_fault_count++;
    }
}
  display(frame,fsize);
  printf("\n*************\n");
  }
printf("\nPage Fault Count is : %d\n",pg_fault_count);
}
void lfu(int page_req[],int n,int fsize)
{
  int i,l,j;int k=0;int pg_fault_count=0,frequency=0,least_freq=INT_MAX;int least_freq_index;
  int frame[fsize];
  for(i=0;i<n;i++)
  {
    printf("\nPage requested: %d",page_req[i]);
    if(k<fsize)
    {
      if((search(frame,k,page_req[i])==1))
      { 
             printf("\nPage Hit !\n");
      }
      else
      {
     frame[i]=page_req[i];
     k++;
     pg_fault_count++;
      }
    }
    else
    {  
       if((search(frame,fsize,page_req[i])==1))
       {
        printf("\nPage Hit !\n");
       }
       else
       {
         for(l=0;l<fsize;l++) 
         {
            for(j=i-1;j>-1;j--)
            {
               if(page_req[j]==frame[l]) 
               frequency++;
            }
            if(frequency<=least_freq)
            {
               least_freq=frequency;
               least_freq_index=l;
            }
            frequency=0;
         } 
        frame[least_freq_index]=page_req[i];
        pg_fault_count++;       
       }
    }
   display(frame,fsize);
  }
printf("\nPage Fault Count is : %d\n",pg_fault_count);

}
void lru(int page_req[],int n,int fsize)
{
  int i,j;int frame[fsize];int farthest;int k=0;int l;int dist;int farthest_index,pg_fault_count=0;
  for(i=0;i<n;i++)
  { 
    printf("\nPage requested: %d",page_req[i]);
    if(k<fsize)
    {
      if((search(frame,k,page_req[i])==1))
      { 
             printf("\nPage Hit !\n");
      }
      else
      {
     frame[i]=page_req[i];
     k++;
     pg_fault_count++;
      }
    }
    else
    {  
       if((search(frame,fsize,page_req[i])==1))
       {
        printf("\nPage Hit !\n");
       }
       else
       {
       //dist=0;
       farthest=0;
       for(l=0;l<fsize;l++)
       { 
          //printf("\nFor %d",frame[l]);
          dist=0;
          for(j=i-1;j>-1;j--)
          {
              if(page_req[j]==frame[l])
                  break;
              else
                  dist++;               
          }
          //printf("distance is %d",dist);
          if(dist>=farthest)
          {
          farthest=dist;
          farthest_index=l;
          }
       //dist=0;
       }
       //printf("\n Farthest is %d",frame[farthest_index]);
       frame[farthest_index]=page_req[i];
       pg_fault_count++;
    }
}
  display(frame,fsize);
  printf("\n*************\n");
  }
printf("\nPage Fault Count is : %d\n",pg_fault_count);
}


void main()
{
int n;
printf("\nEnter number of page requests:");
scanf("%d",&n);
int i;
int page_req[n];
printf("\nEnter page requests:");
for(i=0;i<n;i++)
{
scanf("%d",&page_req[i]);
}
int choice;
printf("\nEnter choice \n 2->Optimal page replacement \n 1->LRU \n 0->LFU \n");
scanf("%d",&choice);
int frame_size;
printf("\nEnter frame size:");
scanf("%d",&frame_size);
switch(choice)
{
case 0:lfu(page_req,n,frame_size);break;
case 1:lru(page_req,n,frame_size);break;
case 2:optimal(page_req,n,frame_size);break;
default:printf("---Invalid Choice!---");
}
}
