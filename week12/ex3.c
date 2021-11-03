#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>

void print_shotcuts()
{
    printf("SHORTCUTS\n");
    printf("\tP + E\n");
    printf("\tC + A + P\n");
    printf("\tI + U\n");
}

void update_used_shortcuts(char *history, char *used){
    // P + E
    if (history[18] == 0)
    {
        used[0] = 0;
    }

    // C + A + P
    if (history[25] == 0)
    {
        used[1] = 0;
    }

    // I + U
    if (history[22] == 0)
    {
        used[2] = 0;
    }
}

void check_for_schortcuts(char *history, char *used, FILE *f)
{

    // P + E
    if (!used[0] && history[25] == 1 && history[18] == 1)
    {
        used[0] = 1;
        fprintf(f, "I passed the exam!\n");
    }

    // C + A + P
    if (!used[1] && history[46] == 1 && history[30] == 1 && history[25] == 1)
    {
        used[1] = 1;
        fprintf(f, "Get some cappuccino!\n");
    }

    // I + U
    if (!used[2] && history[23] == 1 && history[22] == 1)
    {
        used[2] = 1;
        fprintf(f, "Wellcome to Innopolis University!\n");
    }
}

void initialize_array(char *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
    }
}

int main()
{
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    struct input_event event;
    ssize_t n;
    int fd;

    fd = open(dev, O_RDONLY);
    if (fd == -1)
    {
        printf("Can not open %s\n", dev);
        return 1;
    }

    print_shotcuts();

    FILE *output_f;
    fclose(fopen("./ex3.txt", "w"));

    const int history_size = 256;
    char history[history_size];
    initialize_array(history, history_size);

    const int shortcuts_size = 3;
    char used_shortcuts[history_size];
    initialize_array(used_shortcuts, shortcuts_size);

    while (1)
    {
        n = read(fd, &event, sizeof event);
        if (event.code != 0)
        {
            output_f = fopen("./ex3.txt", "a");
            if (event.value == 0)
            {
                // released
                history[event.code] = 0;
            }
            else if (event.value == 1)
            {
                // pressed
                history[event.code] = 1;
            }
            else if (event.value == 2)
            {
                // repeated
            }
            update_used_shortcuts(history, used_shortcuts);
            check_for_schortcuts(history, used_shortcuts, output_f);
            fclose(output_f);
        }
    }
    return 0;
}