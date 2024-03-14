#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXCOM 1024 // max number of letters to be supported
#define MAXLIST 10  // max number of commands to be supported

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

char* handleInput(char *inputString){
    char *token = strtok(inputString," ");
    char *tokens[10];
    int counter = 0;
    while (token != NULL)
    {
        tokens[counter] = token;
        token = strtok(NULL, " ");
        counter++;
    }
    return tokens;
}


int main()
{
    char inputString[MAXCOM];

    while (1)
    {
        printDir();

        if (!takeInput(inputString))
            continue;

        handleInput(inputString);
    }
    return 0;
}
