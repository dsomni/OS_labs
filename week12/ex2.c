#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>

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

    FILE *output_f;
    fclose(fopen("./ex2.txt", "w"));
    while (1)
    {
        n = read(fd, &event, sizeof event);
        if (event.code != 0)
        {
            output_f = fopen("./ex2.txt", "a");
            if (event.value == 0)
            {
                fprintf(output_f, "RELEASED 0x%04x (%i)\n", (int)event.code, event.code);
            }
            else if (event.value == 1)
            {
                fprintf(output_f, "PRESSED 0x%04x (%i)\n", (int)event.code, event.code);
            }
            else if (event.value == 2)
            {
                fprintf(output_f, "REPEATED 0x%04x( %i)\n", (int)event.code, event.code);
            }
            fclose(output_f);
        }
    }
    return 0;
}