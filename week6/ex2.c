#include<stdio.h>
#include <stdlib.h>

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int exit_time;
    int complition_time;
    int waiting_time;
    int turnaround_time;
};

void swap(struct Process *xp, struct Process *yp)
{
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void sort_sj(struct Process processes[], int size){
   int i, j;
   for (i = 0; i < size-1; i++){
       for (j = 0; j < size-i-1; j++){
           if (processes[j].burst_time > processes[j+1].burst_time)
              swap(&processes[j], &processes[j+1]);
       }
   }
}

void fill_fields(struct Process processes[],  int size){
    struct Process * process;
    for (int i=0; i<size; i++){
        process = &processes[i];
        if (i==0){
            process->waiting_time = 0;
        }else{
            process->waiting_time = processes[i-1].complition_time - process->arrival_time;
        }
        process->complition_time = process->arrival_time + process->burst_time + process->waiting_time;
        process->turnaround_time = process->burst_time + process->waiting_time;
    }
}

void print_table(struct Process processes[],  int size){
    struct Process * process;
    printf("P#\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n\n");
    for (int i=0;i < size; i++){
        process = &processes[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process->id,
        process->arrival_time, process->burst_time, process->complition_time,
        process->turnaround_time, process->waiting_time);
    }
}

void print_extra_info(struct Process processes[],  int size){
    float av_tat = 0;
    float av_wt = 0;
    for (int i=0;i < size; i++){
        av_tat += processes[i].turnaround_time;
        av_wt += processes[i].waiting_time;
    }
    av_tat/=size;
    av_wt/=size;
    printf("Average Turnaround time: %f\nAverage Waiting time: %f\n", av_tat, av_wt);
}

int main(){
    int processes_num;
    printf("Enter number of processes: ");
    scanf("%d", &processes_num);
    printf("\n");
    printf("Please enter the Arrival time and Burst time for each process:\n");
    struct Process* processes = (struct Process*) malloc(processes_num * sizeof(struct Process));
    for (int i=0;i < processes_num; i++){
        processes[i].id = i+1;
        printf("Arrival time[%d]: ", i+1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time[%d]: ", i+1);
        scanf("%d", &processes[i].burst_time);
    }
    printf("\n");

    sort_sj(processes, processes_num);

    fill_fields(processes, processes_num);

    print_table(processes, processes_num);

    print_extra_info(processes, processes_num);

    return 0;
}