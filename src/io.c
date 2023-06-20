#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadLines(char **lines, int lines_len, const char *filename)
{
    int i = 0;
    char line[6];

    FILE *file;
    file = fopen(filename, "r");

    while (fgets(line, sizeof(line), file) != NULL && i < lines_len)
    {
        int line_len = strlen(line);
        if (line_len < 5)
            continue;
        if (line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';

        lines[i] = malloc(line_len);
        strcpy(lines[i], line);
        i++;
    }

    fclose(file);
}