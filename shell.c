#include "shell.h"

char *prompt;
int commandLen;

int main(int argc, char **argv)
{
	initShell();
	handleArgs(argc, argv);
	char command[commandLen];
	while(1)
	{
		printf("%s", prompt);
		if (fgets(command, commandLen, stdin) != NULL)
		{
			int count;
			char **args;
			parseCommand(&count, &args, command);
			handleCommand(count, args);
		}
		else
		{
			printf("Error with stdin\n");
		}
	}
}

void handleCommand(int argc, char **argv)
{
	// int i;
	// for(i=0; i<argc; i++)
	// {
	// 	printf("Option %d is \"%s\"\n", i, argv[i]);
	// }
	
	if(strcmp(argv[0], "exit") == 0)
	{
		bExit();
	}
	else if(strcmp(argv[0], "pid") == 0)
	{
		printf("shell: PID: %d\n", pid());
	}
	else if(strcmp(argv[0], "ppid") == 0)
	{
		printf("shell: PPID: %d\n", ppid());
	}
	else if(strcmp(argv[0], "cd") == 0)
	{
		char *path;
		if (argv[1] != NULL)
		{			
			path = argv[1];
		}
		else
		{
			path = getenv("HOME");
		}
		cd(path);
	}
	else if(strcmp(argv[0], "pwd") == 0)
	{
		char *path = pwd();
		printf("%s\n", path);
		free(path);
	}
	else if(strcmp(argv[0], "set") == 0)
	{
		char *env;
		char *value;
		if(argv[1] != NULL)
		{
			env = argv[1];
			if(argv[2] != NULL)
			{
				value = argv[2];
				setenv(argv[1], argv[2], 1);
			}
			else
			{
				unsetenv(env);
			}
		}
		else
		{
			printf("shell: get: Missing environment operand\n");
		}
	}
	else if(strcmp(argv[0], "get") == 0)
	{
		if(argc > 1)
		{
			printf("%s: %s\n", argv[1], get(argv[1]));
		}
		else
		{
			printf("shell: get: Missing environment operand\n");
		}
	}
	else
	{
		printf("Placeholder for exec\n");
	}
}
