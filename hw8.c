#include<stdio.h>
#include<string.h>

typedef struct time{
    int minute;
    int second;
}timer;

typedef struct runner{
    char name[30];
    char last_name[30];
    char ID[30];
    timer* record;
    timer running_time;
}runner_info;

int bettertime(timer a, timer b){
    if ((a.minute>b.minute)||((a.minute==b.minute)&&(a.second>b.second))){
        return 1;
    }    
    else
        return 0;
}
int main(){
    int n;
    printf("Enter the number of racers: ");
    scanf("%d", &n);
    runner_info run_list[n];
    timer timers[n];
    for (int i=0; i<n; i++){
        run_list[i].record=&timers[i];
        printf ("Enter the following info for the %dth runner in correct order: \n", i+1);
        printf ("Runner's name/Last name/Id/Best record by minute/Best record by second/Ran time by minute/Ran time by second\n");
        scanf("%s %s %s",run_list[i].name,run_list[i].last_name, run_list[i].ID);
        scanf("%d %d",&run_list[i].record->minute, &run_list[i].record->second);
        scanf("%d %d",&run_list[i].running_time.minute, &run_list[i].running_time.second);
        getchar();
    }

    int bestrun=0;
    timer besttime={run_list[0].running_time.minute, run_list[0].running_time.second};
    timer bestrecord={run_list[0].record->minute, run_list[0].record->second}; 
    for (int i=0; i<n; i++){
        if (bettertime(besttime, run_list[i].running_time)){
            besttime.minute=run_list[i].running_time.minute;
            besttime.second=run_list[i].running_time.second;
            bestrun=i;
        }   
    }
    for (int i=0; i<n; i++){
        if (bettertime(bestrecord, *run_list[i].record)){
            bestrecord.minute=run_list[i].record->minute;
            bestrecord.second=run_list[i].record->second;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("//Results//\n\n");
    printf("Runner number %d is the winner of the race,\n", bestrun+1);
    if(bettertime(*(run_list[bestrun].record), besttime)){
        printf("Winner has suceeded in breaking their previous record!\n");
        if(bettertime(bestrecord, besttime))
            printf("And they succesfully broke the overall record!\n");
        else 
            printf("But they failed to break the best overall record.\n");
    }
    else{
        printf("Winner didn't break their own record.\n");
        printf("Winner didn't break the overall best record.\n");
    }
    printf("\n//Match overlook//\n\n");
    printf("Name\tLast Name\tID\tRun time(min:sec)\tRank\n");
    printf("------------------------------------------------------------\n");
    runner_info temp[n*n];
    for (int j=0; j<n-1;j++){
        for(int i=0; i<n-1; i++){
            if(bettertime(run_list[i].running_time, run_list[i+1].running_time)){
                temp[i+n*j]=run_list[i+1];
                run_list[i+1]=run_list[i];
                run_list[i]=temp[i+n*j];
            }
        }
    }
    for (int i=0; i<n; i++){
        printf("%s\t%s\t\t%s\t%d:%d\t\t\t%d\n",run_list[i].name,run_list[i].last_name, run_list[i].ID, run_list[i].running_time.minute, run_list[i].running_time.second, i+1);
        printf("------------------------------------------------------------\n");
    }
}   