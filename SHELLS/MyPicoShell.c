#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void execute_command(char **args);
char **parse_input(char *input);
void free_args(char **args);

int main()
{
    char input[MAX_INPUT_SIZE];
    char **args;
    //main program
    while (1)
    {
        //printing the promt
        printf("Mohie-shell> ");
        //if failed to get commands
        if (!fgets(input, MAX_INPUT_SIZE, stdin))
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        //truncating the string by removing the /n and replacing it with 0(null)
        //strcspn : it searches for the first occurence of /n and return its number 
        input[strcspn(input, "\n")] = 0; // Remove newline
        //parsing and tokenizing the input into the array of pointers
        args = parse_input(input);
        //if there's any arg we execute it
        if (args[0] != NULL)
        {
            execute_command(args);
        }
        //after finishing we free the dynamic memory from the args.
        free_args(args);
    }
    return 0;
}

//for executing the commands
void execute_command(char **args)
{
    //comparing the first token with exit to exit the prompt 
    if (strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        exit(0);
    }
    //if the command is PWD we use "getcwd" func and store the working directory inside a buffer and then print it
    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) 
        {
            printf("%s\n", cwd);
        }
        //else we print errors
        else
        {
            perror("getcwd");
        }
    }
    //if change directory was the command(cd) we use chdir() func and get the second argument as it will be the path for the chdir() func
    else if (strcmp(args[0], "cd") == 0) {
        //if we dont have any paths we print error of missing args 
        if (args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        //else we change it if we dont have errors for CD
        else if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
    //checking if echo is the command used
    else if (strcmp(args[0], "echo") == 0)
    {
        //printing each token after the first one as first token is echo
        for (int i = 1; args[i] != NULL; i++)
        {
            printf("%s ", args[i]);
        }
        //printing a new line
        printf("\n");
    }
    //if none of the saved commands is created we excute an external command
    else
    {
        //we create a child process by calling fork
        pid_t pid = fork();
        //if the return of fork is less than 0 it means that it couldnt create a child process and we should print the error
        if (pid < 0)
        {
            perror("fork");
        }
        //if the return is 0 it means it created a new child process which has a parent pid of the same mohie shell
        else if (pid == 0)
        {
            //we create a whole new process in the child process which will be terminated after finishing
            //we call execvp() function as it takes the command as a string and search for it in the system paths like bin paths .
            //we pass the arguments "tokenized arguments" we cereated
            execvp(args[0], args);
            //check if there's any error from execvp we print it using perror()
            perror("execvp");
            //exiting after finishing the new process
            exit(EXIT_FAILURE);
        }
        //we need to make sure that the parent is waiting for the child process to be finished not to execute anything in parallel with the child
        //Null was used as we r not interested in the return value of exiting from child 
        else
        {
            wait(NULL);
        }
    }
}
//a function for parsing the aguments 
char **parse_input(char *input)
{
    //creating a dynamic memory for the args
    char **args = malloc(sizeof(char *) * MAX_INPUT_SIZE);
    //if it failed to allocate memory we exit and print the error using PERROR()
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    //we create a pointer to point for each token using strtok() with " " as our delimiter between tokens
    char *token = strtok(input, " ");
    int index = 0;
    while (token)
    {
        //if there's a token we duplicate it using strdup and added to args[] array which will be returned to the main function
        args[index] = strdup(token);
        //if there's no tokens in args we exit and print the error
        if (!args[index])
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        //incrementing the index and looking for the next tokens (calling strtok with NULL) to repeat the process if no other tokens it prints null
        index++;
        token = strtok(NULL, " ");
    }
    //putting the last token to NUll
    args[index] = NULL;
    //returning the last token
    return args;
}

//a function to free the arguments(tokens)array
void free_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        free(args[i]);
    }
    free(args);
}
