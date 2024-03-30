#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int takeInput(char *str)
{
    char *buf = readline("");
    if (strlen(buf) != 0)
    {
        strcpy(str, buf);
        return 1;
    }
    else
    {
        return 0;
    }
}

void printDir()
{
    char *user = getlogin();

    char path[1024];
    getcwd(path, sizeof(path));

    char host[1024];
    gethostname(host, sizeof(host));

    printf("%s@%s-%s$ ", user, host, path);
}

void splitInput(char *inputString, char *tokens[])
{
    char *token = strtok(inputString, " ");
    int counter = 0;
    while (token != NULL)
    {
        tokens[counter] = token;
        token = strtok(NULL, " ");
        counter++;
    }
}

void handleTokens(char *tokens[])
{
    if (!strcmp(tokens[0], "فهرست"))
    {
        char command[100];
        sprintf(command, "ls %s", tokens[1]);
        system(command);
    }
    else if (!strcmp(tokens[0], "برو"))
    {
        char command[100];
        sprintf(command, "cd %s", tokens[1]);
        system(command);
    }
    else if (!strcmp(tokens[0], "محتوا"))
    {
        char command[100];
        sprintf(command, "cat %s", tokens[1]);
        system(command);
    }
    else if (!strcmp(tokens[1], ">"))
    {
        char command[100];
        sprintf(command, "%s > %s", tokens[0], tokens[2]);
        system(command);
    }
    else if (!strcmp(tokens[0], "فهرستـمخفی"))
    {
        char command[100];
        sprintf(command, "ls %s | sed 's/......$/______/g'", tokens[1]);
        system(command);
    }
    else if (!strcmp(tokens[0], "تنظیم"))
    {
        char command[100];
        sprintf(command, "%s=%s", tokens[1], tokens[3]);
        system(command);
    }
    else if (!strcmp(tokens[0], "تنظیمات"))
    {
        char command[100];
        sprintf(command, "echo $%s", tokens[1]);
        system(command);
    }
    else if (!strcmp(tokens[1], "&"))
    {
        char command[100];
        sprintf(command, "%s &", tokens[0]);
        system(command);
    }
    else if (tokens[0][0] == '$')
    {
        system(tokens[0]);
    }
}

int main()
{
    char inputString[1024];
    char *tokens[5];

    while (1)
    {
        // print shell information
        printDir();

        // check if input is valid
        if (!takeInput(inputString))
            continue;

        // split input to tokens to process
        splitInput(inputString, tokens);

        // main token handler
        handleTokens(tokens);
    }

    return 0;
}
