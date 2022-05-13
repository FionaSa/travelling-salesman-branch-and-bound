#include "header.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int **mat;

    mat = getconfig("config.txt");

    resolve(mat);

    return 0;
}
