#include <stdio.h> // printf() and perror()
#include <string.h> // strerror()
#include <errno.h> // int errno;

// char *strerror(int errnum);
// void perror(const char *s);

int    main(void)
{
    int    i;
    int    final;

    i = 0;
    final = 150;
    perror ("Current system error");
    while (i <= final)
    {
        printf ("error %d: %s\n", i, strerror(i));
        i++;
    }
    return (0);
}