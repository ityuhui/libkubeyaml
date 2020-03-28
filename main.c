#include <stdio.h>
#include <kubeyaml.h>

int main()
{
    printf("hello,yuhui!\n");

    kubeyaml_loadkubeconfig(./config);

    return 0;
}
