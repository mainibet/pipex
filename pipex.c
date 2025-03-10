/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:36:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/10 16:16:35 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//needed as a parameter of execve

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)//to compare the first 5 bytes
			return (envp[i] + 5);//to return the path with out :PATH="
		i++;
	}
	return (NULL);//if is not found
}


//get_path_testing
/*#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*path_env;

	path_env = get_path_env(envp);
	if (path_env)
		printf("PATH found: %s\n", path_env);
	else
		printf ("PATH not found\n");
	return (0);
}
*/
//just for testing this include:
#include <stdio.h>

//To find executables cmd1 or cmd2
char	*find_path(char *argv, char **envp)
{
	char	*file_path;//to hold the return
	char	**dir;
	char	*path;
	char	*each_path;
	int	i;

	path = get_path_env(envp);
	if (!path)
	{
		perror("PATH env not found");
		return (NULL);
	}
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		each_path = ft_strjoin(dir[i], "/");
		file_path = ft_strjoin(each_path, argv);
		free (each_path);
		if (access (file_path, F_OK) == 0)
		{	//just for testing
			printf("Path found for cmd1: %s\n", file_path);
			return (file_path);//free in other place
		}//for testing
		free (file_path);
		i++;
	}//maybe after this is needed to check memory and free
	return (NULL);
}
/*
//find_path specific for executable files testing cmd1 cmd2
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	*command_path;

	if (argc == 2)
	{
		command_path = find_path(argv[1], envp);
		printf("specific path: %s\n", command_path);
	}
	else
		printf ("Command path not found\n");
	return (0);
}
*/

#include <stdio.h>//just for testing
//to redirect input
int	redir_input(int file1)
{
	int	file1_dup;

	file1_dup = dup2(file1, STDIN_FILENO);
	if (file1_dup == -1)
	{
		perror ("Dup2 failed");
		return (1);
	}
	printf("Successfull redirection: now stdin comes from fd file1 %d\n", file1);
	if (close(file1) == -1)
	{
		perror ("Error closing the file");
		return (1);
	}
	return (0);
}

#include <stdio.h> //just for testing

int	execution(char	**argv, char **const envp)
{
	char	*cmd1_path;
//find the path of the cmd
	cmd1_path = find_path(argv[2], envp); //make it later for cmd2
	if (cmd1_path == NULL)
	{
		perror ("path not found for execution\n");
		exit (EXIT_FAILURE);
	}
	printf("cmd_path found for execution: %s\n", cmd1_path);//just for testing
	printf("Execution will begin\n");//testing
	//try to execute cmd
	if (execve(cmd1_path, argv, envp) == -1)
	{
		perror ("execve failed");//before the next step I have to check free that are needed from finding the path
		free (cmd1_path);
		exit (EXIT_FAILURE);
	}//pending to free somewhere else cmd1_when success but after execution
	return (0);	
}

#include <stdio.h> //just for testing
//initial checking: if file1 exist, if file1 has read permissions, if cmd1 is executable
int	ini_check(char **argv, char **envp)
{
	//in this first if condition include the check for argv[4] which is file2
	if (access("hi.txt", F_OK) == -1)//to check if the file exist
	{
		perror("Input file doesn't exist");
		return (1);
	}
	//in this second if condition include the check for argv[4] which is file2
	else if (access("hi.txt", R_OK) == -1)//to check if the file is readable
	{
		perror("Input file is not readable");
		return (1);
	}
	//in this final if condition include cmd2 to check if is executable argv[3]
	if (access(find_path(argv[2], envp), X_OK) == -1)//pending fix parameters, needs to be the path
 	{
		perror("cmd1 is not executable");
		return (1);
	}
	//for testing
	printf("File1 and cmd1 passed initial check\n");
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	file1;//to open fd file1

	ft_printf("argc including the program: %d\n", argc);//just for mvp
	if (argc != 3)//temporary, just for this mvp
		return (ft_printf("include 2 args\n"), 1);
	else
	{
		ini_check(argv, envp);//this will tak all argv to check them
		file1 = open("hi.txt", O_RDONLY);//to open file1 in read-only mode
		if ( file1 == -1)
		{
			perror ("Error opening file");
			return (1);
		}
		//to redirec fil1 as intput of cmd1
		if (redir_input(file1))
		{
			//if redirection fails, close file1
			if (close(file1) == -1)
			{
				perror("Error closing the file");
				return (1);
			}
		}
		//code to read the file if open() success
		if (argv[2])//temporal for mvp with cmd1
			execution(argv, envp);	
		//Need to close file1 when is not longer used
//This close(file1) was moved after the redirection file1
//check if this is the position for file1_dup. Temporary comment until fork()
//		if (close(file1_dup) == -1)
//		{
//			perror ("Error closing the file");
//			return (1);
//		}
	}
	return (0);
}

