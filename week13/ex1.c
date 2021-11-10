#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct process
{
    int id;
    int *requestedResources;
    int isFinished;
};

void askInputFileName(char *fileName)
{
    printf("Input file: ");
    scanf("%s", fileName);
    printf("\n");
}

void askResourcesClassesNumbers(int *r)
{
    printf("Number of resources classes: ");
    scanf("%d", r);
    printf("\n");
}

void askProcessesNumbers(int *p)
{
    printf("Number of processes: ");
    scanf("%d", p);
    printf("\n");
}

void initializeProcesses(struct process *processes, int n, int size)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i;
        processes[i].requestedResources = malloc(sizeof(int) * size);
        processes[i].isFinished = 0;
    }
}

void initializeCurrentAllocationMatrix(int **currentAllocationMatrix, int n, int size)
{
    for (int i = 0; i < n; i++)
    {
        currentAllocationMatrix[i] = malloc(sizeof(int) * size);
    }
}

void readTotalResources(FILE *f, int *totalResources, int n)
{
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%i", &totalResources[i]);
    }
}

void readAvaliableResources(FILE *f, int *avaliableResources, int n)
{
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%i", &avaliableResources[i]);
    }
}

void readCurrentAllocationMatrix(FILE *f, int **currentAllocationMatrix,
                                 int processesN, int resourcesClassesN,
                                 int *totalResources, int *avaliableResources)
{
    for (int j = 0; j < resourcesClassesN; j++)
    {
        avaliableResources[j] = totalResources[j];
    }
    for (int i = 0; i < processesN; i++)
    {

        for (int j = 0; j < resourcesClassesN; j++)
        {
            fscanf(f, "%i", &currentAllocationMatrix[i][j]);
            avaliableResources[j] -= currentAllocationMatrix[i][j];
        }
    }
}

void readProcessesMatrix(FILE *f, struct process *processes,
                         int processesN, int resourcesClassesN)
{
    for (int i = 0; i < processesN; i++)
    {
        for (int j = 0; j < resourcesClassesN; j++)
        {
            fscanf(f, "%i", &processes[i].requestedResources[j]);
        }
    }
}

void handleProcess(struct process* process, int *currentAllocation,
                   int *avaliableResources, int resourceClassesN, int* modified)
{
    int assigned = 1;
    for (int j = 0; j < resourceClassesN; j++)
    {
        if (process->requestedResources[j] > avaliableResources[j] + currentAllocation[j])
        {
            assigned = 0;
            break;
        }
    }
    if (assigned == 1)
    {
        *modified = 1;
        process->isFinished = 1;
        for (int j = 0; j < resourceClassesN; j++)
        {
            avaliableResources[j] += currentAllocation[j];
            currentAllocation[j] = 0;
        }
    }
}

void displayInfo(struct process process)
{
    printf("Process #%i -> isFinished=%i\n", process.id, process.isFinished);
}

int main()
{
    char fileName[255];
    int resourceClassesN, processesN;
    askInputFileName(fileName);
    askResourcesClassesNumbers(&resourceClassesN);
    askProcessesNumbers(&processesN);

    int *totalResources = malloc(sizeof(int) * resourceClassesN);
    int *avaliableResources = malloc(sizeof(int) * resourceClassesN);
    int **currentAllocationMatrix = malloc(sizeof(int *) * processesN);
    initializeCurrentAllocationMatrix(currentAllocationMatrix, processesN, resourceClassesN);
    struct process *processes = malloc(sizeof(struct process) * processesN);
    initializeProcesses(processes, processesN, resourceClassesN);

    FILE *f;
    f = fopen(fileName, "r");
    readTotalResources(f, totalResources, resourceClassesN);
    readAvaliableResources(f, avaliableResources, resourceClassesN);
    readCurrentAllocationMatrix(f, currentAllocationMatrix, processesN,
                                resourceClassesN, totalResources, avaliableResources);
    readProcessesMatrix(f, processes, processesN, resourceClassesN);

    int modified = 1;
    while (modified == 1)
    {
        modified = 0;
        for (int i = 0; i < processesN; i++)
        {
            if (processes[i].isFinished == 0){
                handleProcess(&processes[i], currentAllocationMatrix[i],
                              avaliableResources, resourceClassesN, &modified);
            }
            displayInfo(processes[i]);
        }
        printf("\n");
    }

    printf("\n");
    int hasDeadlock = 0;
    for (int i = 0; i < processesN; i++)
    {
        if (processes[i].isFinished == 0)
        {
            hasDeadlock = 1;
            printf("Process %i has a Deadlock!\n", processes[i].id);
        }
    }
    if (hasDeadlock == 0)
    {
        printf("Congratulations! There are no Deadlocks!\n");
    }

    return 0;
}