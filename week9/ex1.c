#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_BITS 8

float hits = 0;
float misses = 0;

struct page
{
    int pageNumber;
    int R;
    unsigned char counter;
};

int ask_page_frames_number()
{
    printf("Enter number of page frames: ");
    int n;
    scanf("%d", &n);
    printf("\n");
    return n;
}

void print_info()
{
    printf("Number of hits: %f\nNumber of misses: %f\nRation Hit/Miss: %f\n", hits, misses, hits/misses);
}

void initialize(struct page *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        list[i].pageNumber = -1;
    }
}

int get_page_numbers()
{
    FILE *ptrfile;
    int k = 0;
    int s;
    ptrfile = fopen("input.txt", "r");
    while ((fscanf(ptrfile, "%d", &s) != EOF))
    {
        if (!ptrfile)
            break;
        k += 1;
    }
    return k;
}

void fill_page_numbers(int *pageNumbers, int n)
{
    FILE *ptrfile;
    ptrfile = fopen("input.txt", "r");
    for (int i = 0; i < n; i++)
    {
        fscanf(ptrfile, "%d", &pageNumbers[i]);
    }
    fclose(ptrfile);
}

int find_page(struct page *list, int n, int page_number)
{
    for (int i = 0; i < n; i++)
    {
        if (list[i].pageNumber == page_number)
            return i;
    }
    return -1;
}

void update_r_bits(struct page *list, int n, int idx)
{
    for (int i = 0; i < n; i++)
    {
        list[i].R = 0;
    }
    list[idx].R = 1;
}

void update_pages(struct page *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        list[i].counter >>= 1;
        if ( list[i].R == 1){
            list[i].counter |= 1 << (NUMBER_OF_BITS - 1);
        }
    }
}

void replace_page(struct page *list, int idx, int page_number)
{
    list[idx].counter = 0;
    list[idx].R = 1;
    list[idx].pageNumber = page_number;
}

int find_free(struct page *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (list[i].pageNumber == -1)
            return i;
    }
    return -1;
}

int ageing_algo(struct page *list, int n)
{
    unsigned char min_counter = 255;
    int page_to_remove_idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (list[i].counter <= min_counter)
        {
            page_to_remove_idx = i;
            min_counter = list[i].counter;
        }
    }
    return page_to_remove_idx;
}

int insert_page(struct page *list, int n, int page_number)
{
    int idx = find_free(list, n);
    if (idx == -1) // there is no free page frame
    {
        idx = ageing_algo(list, n);
    }
    replace_page(list, idx, page_number);
    return idx;
}

void start_simulation(struct page *list, int n)
{
    int p_n = get_page_numbers();
    int *pageNumbers = malloc(sizeof(int) * p_n);
    fill_page_numbers(pageNumbers, p_n);

    int next_page;
    int idx;
    for (int i = 0; i < p_n; i++)
    {
        next_page = pageNumbers[i];
        idx = find_page(list, n, next_page);
        if (idx == -1) // there is no such page
        {
            misses++;
            idx = insert_page(list, n, next_page);
        }
        else // there is such page
        {
            hits++;
        }
        update_r_bits(list, n, idx);
        update_pages(list, n);
    }
}

int main()
{

    int n = ask_page_frames_number();
    struct page *list = malloc(sizeof(struct page) * n);
    initialize(list, n);

    start_simulation(list, n);
    print_info();

    return 0;
}