#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int complition_time;
    int waiting_time;
    int turnaround_time;

    int remain_burst_time;
    int prev_preempt_time;
};

void swap(struct Process *xp, struct Process *yp)
{
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_fcfs(struct Process processes[], int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
                swap(&processes[j], &processes[j + 1]);
        }
    }
}

void fill_fields(struct Process processes[], int size, int quantum)
{
    struct Process *process;
    int flag = 1;
    int time = 0;
    while (flag == 1)
    {
        flag = 0;
        for (int i = 0; i < size; i++)
        {
            process = &processes[i];

            if (process->complition_time!=-1){
                continue;
            }else{
                // printf("%d %d %d %d\n", process->id, process->waiting_time, process->prev_preempt_time, time );
                process->waiting_time += time - process->prev_preempt_time;
                if (process->remain_burst_time > quantum){
                    flag = 1;
                    process->remain_burst_time -= quantum;
                    time+=quantum;
                    process->prev_preempt_time = time;
                }else{
                    time+=process->remain_burst_time;
                    process->remain_burst_time = 0;
                    process->complition_time = time;
                    process->turnaround_time = time - + process->arrival_time;
                }
            }
        }
    }
}

void print_table(struct Process processes[], int size)
{
    struct Process *process;
    printf("P#\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n\n");
    for (int i = 0; i < size; i++)
    {
        process = &processes[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process->id,
               process->arrival_time, process->burst_time, process->complition_time,
               process->turnaround_time, process->waiting_time);
    }
}

void print_extra_info(struct Process processes[], int size)
{
    float av_tat = 0;
    float av_wt = 0;
    for (int i = 0; i < size; i++)
    {
        av_tat += processes[i].turnaround_time;
        av_wt += processes[i].waiting_time;
    }
    av_tat /= size;
    av_wt /= size;
    printf("Average Turnaround time: %f\nAverage Waiting time: %f\n", av_tat, av_wt);
}

int main()
{
    int processes_num;
    int quantum;
    printf("Enter number of processes: ");
    scanf("%d", &processes_num);
    printf("\n");
    printf("Please enter the Arrival time and Burst time for each process:\n");
    struct Process *processes = (struct Process *)malloc(processes_num * sizeof(struct Process));
    for (int i = 0; i < processes_num; i++)
    {
        processes[i].id = i + 1;
        processes[i].complition_time = -1;
        processes[i].waiting_time = 0;
        processes[i].prev_preempt_time = 0;
        printf("Arrival time[%d]: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time[%d]: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remain_burst_time = processes[i].burst_time;
    }
    printf("\n");
    printf("Enter quantum: ");
    scanf("%d", &quantum);
    printf("\n");

    sort_fcfs(processes, processes_num);

    fill_fields(processes, processes_num, quantum);

    print_table(processes, processes_num);

    print_extra_info(processes, processes_num);

    return 0;
}