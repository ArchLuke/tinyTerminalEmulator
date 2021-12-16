#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
int takeInput(char* str)
{
	char* buf;
	buf = readline("\n>>> ");
	if (strlen(buf) != 0) {
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}
void execArgs(char** parsed)
{
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child");
		return;
	} else if (pid == 0) {
		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command");
		}
		exit(0);
	} else {
		wait(NULL);
		return;
	}
}
void parseSpace(char* str, char** parsed)
{
	int i;
	for (i = 0; i <100; i++) {
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}
int main()
{
	char inputString[1000], *parsedArgs[100];
	while (1) {
		if (takeInput(inputString))
			continue;
		parseSpace(inputString, parsedArgs);
		execArgs(parsedArgs);
	}
	return 0;
}
