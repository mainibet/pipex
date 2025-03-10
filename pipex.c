/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:36:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/10 10:17:52 by albetanc         ###   ########.fr       */
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
//To find the file path rather file1, file2, cmd1 or cmd2
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
			return (file_path);//free in other place
		free (file_path);
		i++;
	}//maybe after this is needed to check memory and free
	return (NULL);
}

//find_path specific for files testing
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

/*
int	cmd1_execution(const char *path_env, char **cmd1, char **const evnp[])
{
	//path?
		
	//int execve(const char *pathname, char *const argv[], char *const envp[]);
}

//initial checking: if file1 exist, if file1 has read permissions, if cmd1 is executable
int	ini_check(char *argv)
{
	char	*path_file1;
	char	*path_cmd1;
//poner aca la ruta de archivos
	path_file1 = 
	if (access(argv[1], F_OK) == -1)//to check if the file exist
	{
		perror("Input file doesn't exist");
		return (1);
	}
	else if (access(argv[1], R_OK) == -1)//to check if the file is readable
	{
		perror("Input file is not readable");
		return (1);
	}
	if (access(argv[2], X_OK) == -1)//pending fix parameters, needs to
 be the path
 	{
		perror("cmd1 is not executable");
		return (1);
	}
}

int	main(int argc, char **argv, char *envp)
{
	int	file1;//to open fd file1

	ft_printf("argc including the program: %d\n", argc);//just for mvp
	(void) *argv;//temporary just for mvp
	if (argc != 3)//temporary, just for this mvp
		return (ft_printf("include 2 args\n"), 1);
	else
	{
		ini_check(argv[1]);
		ini_check(argv[2]);
		file1 = open("hi.txt", O_RDONLY);//to open file1 in read-only mode
		if ( file1 == -1)
		{
			perror ("Error opening file");
			return (1);
		}
		//code to read the file if open() success
		if (close(file1) == -1)
		{
			perror("Error closing the file");
			return (1);
		}
	}
	return (0);
}
*/
