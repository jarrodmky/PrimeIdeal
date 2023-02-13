#include "output.h"

#include "stdio.h"
#include "string.h"

void output_newline()
{
    static char newline[1] = "\n";
    fwrite(newline, sizeof(char), 1, stdout);
}

void output_text(cstring const message)
{
    fwrite(message, sizeof(char), strlen(message), stdout);
}

void output_integer(integer number)
{
    fprintf(stdout, "%lld", number);
}

void output_line(cstring const message)
{
    output_text(message);
    output_newline();
}