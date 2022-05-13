#include <header.h>

int main(int argc, char const *argv[])
{
    int **mat;

    if (argc < 2)
    {

        printf("Usage: ./%s <name_config_file>\nYou didn't set a config file name so the default one will be used (config.txt in this directory)\n",argv[0]);
        mat = getConfig("default");
    }
    else
        mat = getConfig(argv[1]);

    resolve(mat);

    return 0;
}
