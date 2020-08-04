//  ReplacementAlgorithms
//  Created by Nada AZ on 4/28/19.
//  Copyright © 2019 Nada AZ. All rights reserved.

#include <stdio.h>
void OPT(int frames, int pages, int stream[], int seq)
{
    int arr[frames],j=0,z, exist=0, fault=0,stop=0,target;
    
    for (int x=0;x<frames;x++) //replace garbage
         arr[x]=-1;
    int max[frames];
    for (int i=0;i<seq;i++) //12
    {
        for (int m=0;m<frames;m++)
            max[m]=seq+1;
        
        exist=0;
        for (z=0;z<frames;z++) //check if exist then nth
        {
            if (stream[i]==arr[z])
            {
                exist=1;
            }
        }
        
        if (exist==0) //el rkm mknsh already mwgod
        {
            if (j>=frames) //3mlna fill lly fat kolo
            {
                for (int x=0;x<frames;x++)
                {
                    stop=0;
                    for (int z=i+1;z<seq && stop==0;z++)
                    {
                        if(arr[x]==stream[z])
                        {
                            stop=1;
                            max[x]=z;
                        }
                    }
                }
                target=0;
                for (int z=0;z<frames;z++)
                {
                    if (max[z]>max[target])
                        target=z;
                }
                
                for(int z=0;z<frames;z++)
                    //printf("max:%d \n",max[z]);
                
                arr[target]=stream[i];
                fault++;
                printf("fault at %d \n",stream[i]);
            }
            else
            {
                arr[j]=stream[i]; //fill 3ady
                j++;
            }
        }
        for (int x=0;x<frames;x++)
            printf("%d \t",arr[x]);
        printf("\n");
    }
    printf("page faults= %d \n",fault);
    
}

void LRU (int frames, int pages, int stream[], int seq)
{
    int arr[frames],j=0,z, exist=0, fault=0;
    
    for (int x=0;x<frames;x++) //replace garbage
        arr[x]=-1;
    
    for (int i=0;i<seq;i++) //12
    {
        exist=0;
        for (z=0;z<frames;z++) //check if exist then nth
        {
            if (stream[i]==arr[z])
            {
                exist=1;
            }
        }
        
        if (exist==0) //el rkm mknsh already mwgod
        {
            if (j>=frames) //3mlna fill lly fat kolo
            {
                int stop=0;
                for (int x=0;x<frames && stop==0;x++) //check recent 2
                {
                    if (arr[x]!=stream[i-1] && arr[x]!=stream[i-2])
                    {
                        arr[x]=stream[i];
                        stop=1;
                    }
                }
                fault++;
                printf("fault at %d \n",stream[i]);
            }
            else
            {
                arr[j]=stream[i]; //fill 3ady
                j++;
            }
        }
        for (int x=0;x<frames;x++)
            printf("%d \t",arr[x]);
        printf("\n");
    }
    printf("page faults= %d \n",fault);
}

void FIFO (int frames, int pages, int stream[], int seq)
{
    int arr[frames],z,j=0, exist=0, fault=0,start=0;
    
    for (int x=0;x<frames;x++) //replace garbage
        arr[x]=-1;
    
    for (int i=0;i<seq;i++) //12
    {
        exist=0;
        for (z=0;z<frames;z++) //check if exist then nth
        {
            if (stream[i]==arr[z])
            {
                exist=1;
            }
        }
        
        if (exist==0) //el rkm mknsh already mwgod
        {
            if(j==frames)
            {
                j=0;
                start=1;
            }
            arr[j]=stream[i];
            j++;
            if(start==1)
            {
                fault ++;
                printf("fault at %d \n",stream[i]);
            }
        }
        
        for (int x=0;x<frames;x++)
            printf("%d \t",arr[x]);
        printf("\n");
    }
    printf("page faults= %d \n",fault);
}

void MFU(int frames, int pages, int stream[], int seq)
{
    int arr[frames],z,j=0, exist=0, fault=0, empty=0,flag=0,stop;
    int index[pages], current[pages], tally[pages];
    int pointer=0,min=0,mint=0,minP1=0,minP2=0,minP=0;
    for (int x=0;x<frames;x++) //replace garbage
        arr[x]=-1;
    
    for (int x=0;x<pages;x++)
    {
        index[x]=-1;
        current[x]=-1;
        tally[x]=0;
    }
    
    for (int i=0;i<seq;i++) //12
    {
        exist=0;
        for (z=0;z<frames;z++) //check if exist then nth
        {
            if (stream[i]==arr[z])
            {
                exist=1;
                for (int x=0;x<pages;x++)
                {
                    if (current[x]==stream[i])
                    {
                        tally[x]++;
                        index[x]=i;
                    }
                }
                
            }
        }
        
        if (exist==0) //el rkm mknsh already mwgod
        {
            if(j>=frames)
            {
                flag=0;
                for (int x=0;x<frames;x++)
                {
                    stop=0;
                    for (int z=0;z<pages && stop==0;z++)
                    {
                        if (arr[x]==current[z])
                        {
                            if (flag==0) //1st time only
                            {
                                mint=tally[z];
                                minP1=index[z];
                                min=current[z];
                                
                            }
                            
                            else if (tally[z]<mint && flag==1)
                            {
                                //printf("test tally:%d  min:%d \n",tally[z],min);
                                mint=tally[z];
                                minP1=index[z];
                                min=current[z];
                            }
                            
                            else if (tally[z]==mint && flag==1) //passed 1st time already
                            {
                                
                                minP2=index[z];
                                if(minP2<minP1)
                                {
                                    mint=tally[z];
                                    min=current[z];
                                    minP=minP2;
                                }
                                else
                                    minP=minP1;
                                
                            }
                            stop=1;
                            flag=1;
                        }
                    }
                }
                for (int x=0;x<frames;x++)
                {
                    if (arr[x]==min)
                    {
                        arr[x]=stream[i];
                        for (int z=0;z<pages;z++)
                        {
                            if (min==current[z])
                            {
                                current[z]=stream[i];
                                index[z]=i;
                                tally[z]=1;
                            }
                        }
                    }
                        
                }
                printf("fault at %d \n",stream[i]);
                fault++;
            }
            else //1st cycle
            {
                arr[j]=stream[i]; //fill 3ady
                empty=0;
                for (int x=0;x<pages && empty==0;x++)
                {
                    if (current[x]==-1)
                    {
                        empty=1;
                        pointer=x;
                    }
                    
                }
                index[pointer]=i;
                current[pointer]=stream[i];
                tally[pointer]++;
                j++;
                
            }
        }
        
        for (int x=0;x<frames;x++)
            printf("%d \t",arr[x]);
        printf("\n");
    }
    printf("page faults= %d \n",fault);
}

void CLK(int frames, int pages, int stream[], int seq)
{
    int arr[frames],z, exist=0, fault=0,j=0,pointer=0;
    int temp[frames],used[frames],f=0;
    for (int x=0;x<frames;x++) //replace garbage
    {
        arr[x]=-1;
        used[x]=0;
        temp[x]=-1;
    }
    
    for (int i=0;i<seq;i++) //12
    {
        exist=0;
        for (z=0;z<frames;z++) //check if exist then nth
        {
            if (stream[i]==arr[z])
            {
                exist=1;
                for (int x=0;x<frames;x++)
                {
                    if (temp[x]==stream[i])
                    {
                        if (used[x]==0)
                        {
                            used[x]=1;
                            pointer++;
                        }
                    }
                }
            }
        }
        
        if (exist==0) //el rkm mknsh already mwgod
        {
            if (j>=frames) //3mlna fill lly fat kolo
            {
                if(f==3) //reset pointer
                    f=0;
                if (pointer==3)
                    pointer=0;
                if (used[pointer]==0)
                {
                    temp[pointer]=stream[i];
                    used[pointer]=1;
                    arr[pointer]=stream[i];
                }
                else if (used[pointer]==1)
                {
                    temp[pointer]=stream[i];
                    for(int c=pointer+1;c<frames;c++)
                        used[c]=0;
                    
                    arr[pointer]=stream[i];
                }
                pointer++;
                fault++;
                printf("fault at %d \n",stream[i]);
            }
            else
            {
                arr[j]=stream[i]; //fill 3ady
                temp[f]=stream[i];
                used[f]=1;
                f++;
                j++;
            }
        }
        
        for (int x=0;x<frames;x++)
            printf("%d \t",arr[x]);
        printf("\n");
    }
    printf("page faults= %d \n",fault);
}

int main(int argc, const char * argv[])
{
    int frames,pages,seq,alg;
    while (1)
    {
        printf("Enter number of page frames given to any process \n"); //3
        scanf("%d",&frames);
        
        printf("Enter number of distinct pages will be used by a specific process \n"); //5
        scanf("%d",&pages);
        
        printf("Enter the number of referenced pages \n"); //12
        scanf("%d",&seq);
    
    int stream []={2,3,2,1,5,2,4,5,3,2,5,2};
        
        //printf("Enter the sequence the process will use its pages with \n"); //2 3 2 1 5 2 4 5 3 2 5 2
    
        //for (i=0;i<seq;i++)
            //scanf("%d",&stream[i]);
        
        printf("Select ur target replacement algorithm 1.OPT  2.LRU  3.FIFO  4.MFU  5.CLOCK \n"); //LRU
        scanf("%d",&alg);
    
        if (alg==1)
            OPT(frames,pages,stream,seq);
        else if (alg==2)
            LRU(frames,pages,stream,seq);
        else if (alg==3)
            FIFO(frames,pages,stream,seq);
        else if (alg==4)
            MFU(frames,pages,stream,seq);
        else if (alg==5)
            CLK(frames,pages,stream,seq);
    
    }
    return 0;
}
