#include<stdio.h>
#include<stdlib.h>

int arr[100][100];
int visited[100];

typedef struct tag{
  struct tag*next;
  int u;
  int v;
  int weight;
}Edge;
int count=0;

int IsSetEmpty(Edge*e)
{
  //printf("IsSetEmpty\n");
  if(e==NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int LeastCost(Edge*e,int*min_u,int*min_v)
{
  //printf("LeastCost\n");
  int min;
  min=1000000;
  while(e!=NULL)
  {
    if(e->weight<min)
    {
      min=e->weight;
      *min_u=e->u;
      *min_v=e->v;
    }
    e=e->next;
  }
  return min;
}

int Traverse(int i,int n,int parent)
{
  visited[i]=1;
  int j,flag;
  for(j=0;j<n;j++)
  {
    if(arr[i][j]==1)
    {
      if(visited[j]==1)
      {
        if(j!=parent)
        {
          return 1;
        }
      }
      else
      {
        //flag=Traverse(j,n,i);
        if(Traverse(j,n,i)==1)
        {
          return 1;
        }
      }
    }
  }
  return 0;
}

int CheckCycle(Edge*e,int min_u,int min_v,int n)
{
  //printf("CheckCycle\n");
  /*int found_u=0,found_v=0;
  int flag=0;
  while(e!=NULL&&flag==0)
  {
    if(e->u==min_u)
    {
      found_u=1;
    }
    if(e->v==min_v)
    {
      found_v=1;
    }
    if(found_u==1&&found_v==1)
    {
      flag=1;
    }
    e=e->next;
  }
  return flag;*/
  int flag=0;
  arr[min_u-1][min_v-1]=1;
  arr[min_v-1][min_u-1]=1;
  int i,j;
  for(i=0;i<n;i++)
  {
    visited[i]=0;
  }
  for(i=0;i<n&&flag==0;i++)
  {
      if(visited[i]!=1)
      {
          flag=Traverse(i,n,-1);
      }
  }
  if(flag==1)
  {
    arr[min_u-1][min_v-1]=0;
    arr[min_v-1][min_u-1]=0;
  }
  return flag;

}

Edge* Delete(int min_u,int min_v,Edge*e)
{
    //printf("Delete\n");
    Edge*prev=NULL,*start=e,*temp;
    int flag=0;
    if(e!=NULL){
    while(e!=NULL&&flag==0)
    {
      if((e->u==min_u&&e->v==min_v)||(e->u==min_v&&e->v==min_u))
      {
        //printf("deleted\n");
        flag=1;
        temp=e;
        if(prev!=NULL)
        {
          prev->next=e->next;
        }
        else
        {
          start=e->next;
        }
        free(temp);
      }
      else
      {
        prev=e;
        e=e->next;
      }
    }
  }
    printf("After deletion\n");
    Edge*temp1=start;
    while(temp1!=NULL)
    {
      printf("u:%d,v:%d ,weight:%d\n",temp1->u,temp1->v,temp1->weight);
      temp1=temp1->next;
    }
    return start;
}

Edge* Insert(int min_u,int min_v,int min,Edge*s)
{
    //printf("Insert\n");
    printf("Inserting %d %d\n",min_u,min_v);
    Edge*temp=NULL,*start=s,*retval;
    temp=(Edge*)malloc(sizeof(Edge));
    temp->weight=min;
    temp->u=min_u;
    temp->v=min_v;
    temp->next=NULL;
    if(s==NULL)
    {
      //return temp;
      retval=temp;
    }
    else
    {
      while(s->next!=NULL)
      {
        s=s->next;
      }
      s->next=temp;
      retval=start;
      //return start;
    }
    return retval;
}

void Kruskal(Edge*e,int n,int edges)
{
    //printf("HHAH");
    count=0;
    int i,j;
    int done[n];
    for(i=0;i<n;i++)
    {
      done[i]=0;
    }
    Edge*s,*temp;
    s=NULL;

    int min,min_u,min_v;
    int flag;
    while(IsSetEmpty(e)!=1&&count<n)
    {
        min=LeastCost(e,&min_u,&min_v);
        //printf("LeastCost:%d %d\n",min_u,min_v);
        flag=CheckCycle(s,min_u,min_v,n);
        //printf("flag:%d",flag);
        if(flag==1)//Forms a cycle
        {
          printf("flag is 1");
          e=Delete(min_u,min_v,e);
        }
        else
        {
          //printf("Hello");
          s=Insert(min_u,min_v,min,s);
          /*if(done[min_v-1]==0)
          {
            done[min_v-1]=1;
            count++;
          }
          if(done[min_u-1]==0)
          {
            done[min_u-1]=1;
            count++;
          }*/
          printf("Inserting %d %d\n",min_u,min_v);
          arr[min_u-1][min_v-1]=1;
          arr[min_v-1][min_u-1]=1;
          count++;
          e=Delete(min_u,min_v,e);
        }
        Edge*t=e;
        printf("e=\n");
        while(t!=NULL)
        {
          printf("%d %d\n",t->u,t->v);
          t=t->next;
        }
        printf("s=\n");
        t=s;
        while(t!=NULL)
        {
          printf("%d %d\n",t->u,t->v);
          t=t->next;
        }
    }
    printf("Array\n");
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
      {
        printf("%d ",arr[i][j]);
      }
      printf("\n");
    }
}

int main()
{
  int flag,u,v,w,n,i,j;
  int edges;
  Edge* e;
  //e=(Edge*)malloc(sizeof(Edge));
  //printf("Enter edges\n");
  flag=0;
  Edge*nptr=NULL;
  printf("Enter number of vertices\n");
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      arr[i][j]=0;
    }
  }
  printf("Enter number of edges\n");
  scanf("%d",&edges);
  for(i=0;i<edges;i++)
  {
    e=(Edge*)malloc(sizeof(Edge));
    printf("Enter u and v\n");
    scanf("%d%d",&u,&v);
    e->u=u;
    e->v=v;
    //arr[u-1][v-1]=1;
    printf("Enter weight\n");
    scanf("%d",&w);
    e->weight=w;
    e->next=nptr;
    nptr=e;
  }
  Edge*t=e;
  printf("Main e=\n");
  while(t!=NULL)
  {
    printf("%d %d\n",t->u,t->v);
    t=t->next;
  }
  //printf("Here");
  Kruskal(e,n,edges);
}
