/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_initial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:58:46 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:58:48 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //just for testing

//needed as a parameter of execve
//strncmp is to compare the first 5 bytes
//the return will be +5 to get it withou :PATH="
//At the end it will return NULl if path is not found (hanlding error)
//Return NULL if is not found
char	*get_path_env(char **envp)
{
	int	i;

    if (!envp)
    {
        fprintf(stderr, "Error: no environment variables available.\n");//testing
        return (NULL);
    }
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

//To get the cmd name in the argv in cases like "echo hello world" or "cat -n" or "ls -l"
//This will make the function find_path work correctly before the execution and in the initial check
//If (space) means when space is not NULL
//I find len to get the length of the command name (without flags or parameters)
//When return(argv) it means there is no space so the return will be the same cmd name
//Other option I explored was to return(ft_strdup(argv)) but I think that would be ok 
//make strdup of argv makes easier manage the free only for that I decide it to do it
char *get_only_cmd(char *argv)
{
    char *space;
    char *cmd;
    size_t len;

    space = ft_strchr(argv, ' ');
    if (space)
    {
        len = space - argv;
        cmd = malloc (sizeof (char) * len + 1);
        if (!cmd)
        {
            perror ("Malloc in get only cmd");
            return (NULL);
        }
        ft_strlcpy (cmd, argv, len + 1);
    }
    else
    {
        cmd = ft_strdup(argv);
        if (!cmd)
        {
            perror ("Malloc in get only cmd");
            return (NULL);
        }
    }
    fprintf(stderr, "cmd_name in get_only_cmd is: %s\n", argv);//testing
    return (cmd);
}

//To find executables cmd1 or cmd2
//file_pat is to hold the return
//dir is the array with all the splited directories
char	*find_path(char *argv, char **envp)
{
	char	*file_path;
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
    if (!dir)
    {//tmp
        return (NULL);
    }//tmp
        i = 0;
	while (dir[i])
	{
		each_path = ft_strjoin(dir[i], "/");
        if (!each_path)
        {
            free (dir[i]);
            return (NULL);
        }
		file_path = ft_strjoin(each_path, argv);
        free (each_path);
        if (!file_path)
        {
            free(dir[i]);
            return (NULL);
        }
		if (access (file_path, F_OK) == 0)
		{
			fprintf(stderr, "Path found for cmd: %s\n", file_path);//TESTING
            while (dir[i])
            {
                free(dir[i]);
                i++;
            }
            free (dir);
            return (file_path);
		}
        free (dir[i]);
		free (file_path);
		i++;
	}
    free (dir);
	return (NULL);
}

//i begins in 2 which is the position of cmd1
//will be check until argv[argc -2] which will be the last cmd before file2
//argv[argc -1] is file2
//free cmd_path at the end of each loop
int check_cmd(int argc, char **argv, char **envp)
{
    int i;
    char    *cmd_name;
    char    *cmd_path;

    i = 2;
    while (i < argc - 1)
    {
        cmd_name = get_only_cmd(argv[i]);
		cmd_path = find_path(cmd_name,envp);
        if (!cmd_path)
        {
            perror("Not path found");
            free(cmd_name);
            return (-1);
        }
        if ((access(cmd_path, X_OK) == - 1))
		{
            perror("cmd2 is not executable");
			free(cmd_name);
			free(cmd_path);
            return (-1);
        }
        free (cmd_path);
        free (cmd_name);
        i++;
    }
    fprintf(stderr, "cmds passed initial check\n");//testing
	return (0);
}

//initial check
//check existence of file1 and file2
//check if file 1 has read permissions
//check if file 2 has write permissions
//check if cmds are executables
//file2 not need ti exit when calling tge program 
//if doesn't exist needs to be created
//O_TRUNC truncates the file, over wrtes the one
//gives it the permissions 0644: rw-r--r--
int	ini_check(int argc, char **argv, char **envp)
{
	if (access(argv[1], F_OK) == - 1)
	{
		perror("At least 1 file doesn't exist");
		return (-1);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror("No read permissions for file1");
		return (-1);
	}
    fprintf(stderr, "File1 passed initial check\n");//testing
    if (check_cmd(argc, argv, envp) != 0)
    {
        perror("Non executable command");
        return (-1);
    }
    return (0);
}




