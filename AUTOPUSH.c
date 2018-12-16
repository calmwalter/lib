#include <stdio.h>
#include <string.h>
#include <windows.h>
int main(int argc, char const *argv[])
{
    char args[256] = "git commit -m \"";
    if (argc == 1)
    {
        strcat(args, "update");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            strcat(args, argv[i]);
            i == argc - 1 ?: strcat(args, " ");
        }
    }
    strcat(args, "\"");
    system("git add .");
    system(args);
    system("git push origin master");
    return 0;
}
