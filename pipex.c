/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:36:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/08 11:53:50 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

//get_path_testing
#include <stdio.h>
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

/*
char	*find_path(char *cmd1, char **envp)
{
	char **pathi
}

int	cmd1_execution(const char *path_env, char **cmd1, char **const evnp[])
{
	//path?
		
	//int execve(const char *pathname, char *const argv[], char *const envp[]);
}


int	main(int argc, char **argv)
{
	int	file1;//to open fd file1

	ft_printf("argc including the program: %d\n", argc);//just for mvp
	(void) *argv;//temporary just for mvp
	if (argc != 3)//temporary, just for this mvp
		return (ft_printf("include 2 args\n"), 1);
	else
	{
		if (access(argv[1], F_OK == -1))//to check if the file exist
		{
			perror("Input file doesn't exist");
			return (1);
		}
		else if (access(argv[1], R_OK) == -1)//to check if the file is readable
		{
			perror("Input file is not readable");
			return (1);
		}
		if (access(argv[2], X_OK == -1))
		{
			perror("cmd1 is not executable");
			return (1);
		}
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
