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

void splitInput(char *inputString,char* tokens[]){
    char *token = strtok(inputString," ");
    int counter = 0;
    while (token != NULL)
    {
        tokens[counter] = token;
        token = strtok(NULL, " ");
        counter++;
    }
}

void handleTokens(char* tokens[]){
    if(!strcmp(tokens[0],"فهرست")){
        system("ls");
    }
}


int main()
{
    char inputString[MAXCOM];
    char *tokens[10];
    while (1)
    {
        //print information
        printDir();

        //check if input is valid
        if (!takeInput(inputString))
            continue;

        //split input to tokens to process
        splitInput(inputString,tokens);

        //main token handler
        handleTokens(tokens);
        
    }
    return 0;
}
