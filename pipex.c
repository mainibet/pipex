/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:36:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/13 15:06:36 by albetanc         ###   ########.fr       */
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
//To get the cmd name in the argv in cases like "echo hello world" or "cat -n" or "ls -l"
//This will make the function find_path work correctly before the execution and in the initial check

char *get_only_cmd(char *argv)
{
    char *space;
    char *cmd;
    size_t len;

    space = ft_strchr(argv, ' ');
    if (space)//if space is not NULL
    {
        len = space - argv; //to get the lenth of the command
        cmd = malloc (sizeof (char) * len + 1); //check if succed where to free
        if (!cmd)
        {
            perror ("Malloc failed to get only cmd");
            free (cmd);
            return (NULL);
        }
        if (cmd)
        {
            ft_strlcpy (cmd, argv, len + 1);
            return (cmd); //follow where to free from here
        }
    }
    //return (ft_strdup(argv));//if there is no space it till be return the same cmd name
    return (argv);                       //would be ok to return argv directly instead of strdup? check this
}

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
/*
int	redir_input(int file1)
{
	int	file1_dup;

	file1_dup = dup2(file1, STDIN_FILENO);
	if (file1_dup == -1)
	{
		perror ("Dup2 failed stdin file1 to cmd1");
		return (1);
	}
	printf("Successfull redirection: now stdin comes from fd file1 %d\n", file1);
	if (close(file1) == -1)
	{
		perror ("Error closing the file1 after redirection file1 to cmd1");
		return (1);
	}
	return (0);
}
*/
//to redirect output. first MVP cmd2 to file2
int redir_output(int file2)
{
    printf("Now will begin redir_output to file2");
    int file2_dup;//the one created to work with
    
    file2_dup = dup2(file2, STDOUT_FILENO);
    if (file2_dup == -1)
    {
        perror ("Dup2 failed with cmd2 to file2");
        return (1);
    }
    printf("Successfull redirection: now cmd2 stdout goes to file2 %d\n", file2);
    if (close (file2) == - 1)//close file2 after dup2 in redirection
    {
        perror ("Error closing file2 after redirection cmd2 to file2");
        return (1);
    }
    return (0);
}
//function to get the right args for 
//execve() consider the firs argv the file that needs to be process by the cmd//about it man says:  By convention, the first of these  strings (i.e.,  argv[0])  should  contain the filename associated with the file being executed.

char    **exec_argv(int argc, char **argv)
{
    char    **new_arg;
    int i;
    int j;

    if (argc <= 1)//if there are not enought arg
        return (NULL);
    new_arg = malloc (sizeof(char *) * argc);//check where will be free if success. It will be with malloc to make possible the bonus
    if (!new_arg)
    {
        perror ("malloc failed in remove_first_argv");
        return (NULL);
    }
//    i = 2;//to skip original argv[0] and the argv[1] from original args
    i = 1;//testing for cmd2 to file2. to skip argv[0] and argv[2]
    j = 0;//to loop in the new array
//while loop only for cmd1
//    while (i < argc)//execve only needs as argv the cmds. In a future version needs to loop until argv[arc-1] to skip file2
       while (i < argc -1)
    {
        new_arg[j] = ft_strdup(argv[i]);//to duplicate each argv original so after need to be freed each one if success
        if (!new_arg[j])
        {
            perror ("strdup failed in removed_first_arg");
            while (j > 0)
            {
                free (new_arg[j - 1]);//to free each argument argv created before the one that failed. It is j - 1 because the final position is a badone
                j--;
            }
            free(*new_arg);//to free the array when somethin failed
            return (NULL);//because it failed
        }
        i++;
        j++;
    }
    new_arg[j] = NULL;
    return (new_arg);
}

#include <stdio.h> //just for testing

int	execution(char	**nargv, char **const envp)
{
//    char    *cmd1_name;//pending testing
    char    *cmd2_name;
//    char    *cmd1_name;//pending testing
//	char	*cmd1_path;
    char    *cmd2_path;
//finr cmd name in the argv and then find the path of the cmd1 and then cmd2
/*
    cmd1_name = get_only_cmd(nargv[0]);//pending testing
    cmd1_path = find_path(cmd1_name, envp); //make it later for cmd2
	if (cmd1_path == NULL)
	{
		perror ("path of cmd1 not found for execution");
		exit (EXIT_FAILURE);
	}
	printf("cmd1_path found for execution: %s\n", cmd1_path);//just for testing
	printf("Execution of cmd1 will begin\n");//testing
	//try to execute cmd
	if (execve(cmd1_path, nargv, envp) == -1)
	{
		perror ("execve failed in cmd1");//before the next step I have to check free that are needed from finding the path
		free (cmd1_path);
		exit (EXIT_FAILURE);
	}//pending to free somewhere else cmd1_path when success but after execution
*/  
    cmd2_name = get_only_cmd(nargv[0]);
    cmd2_path = find_path(cmd2_name, envp);
    if (cmd2_path == NULL)
    {
        perror ("path of cmd2 not found for execution");
        exit (EXIT_FAILURE);
    }
    printf ("cmd2_path found for execution: %s\n", cmd2_path);
    printf ("Execution of cmd2 will begin\n");//testing
        //try to executes cmd2
    if (execve (cmd2_path, nargv, envp) == - 1)
    {
        perror ("execve failed in cmd2");
        free (cmd2_path);
        exit (EXIT_FAILURE);
    }//pending to free cmd2_path somewhere when success and after the execution
    return (0);	
}

#include <stdio.h> //just for testing
//initial checking: if file1 exist, if file1 has read permissions, if cmd1 is executable
//Temporary changed to cmd2 for testing needs to be fixed later for all
int	ini_check(char **argv, char **envp)
{
    char    *cmd_name;

	//in this first if condition include the check for argv[4] which is file2
	if (access(argv[2], F_OK) == -1)//to check if the file2 exist
	{
		perror("Input file doesn't exist");
		return (1);
	}
	//in this second if condition is for cmd2 because is reading permision maybe for another fd in pipe read_end
//	else if (access(argv[1], R_OK) == -1)//to check if the file is readable
//	{
//		perror("No read permissions for file1");
//		return (1);
//	}
    else if (access(argv[2], W_OK) == - 1)
    {
        perror ("No write permissions for file2");
        return (1);
    }
	//in this final if condition include cmd2 to check if is executable argv[3]
	cmd_name = get_only_cmd(argv[1]);//argv[1] is to test cmd2 pending to test cmd1
    if (access(find_path(cmd_name, envp), X_OK) == -1)//pending fix parameters, needs to be the path
 	{
		perror("cmd2 is not executable");
		return (1);
	}
	//for testing
//	printf("File1 and cmd1 passed initial check\n");
    printf("cmd2 and file2 passed initial check\n");
	return (0);
}

int	main(int argc, char **argv, char **envp)//mandatory part has to work exactly with 4arg
{
//	int	file1;//to open fd file1
	int file2;//to opoen file2
    char    **nargv;
    int pipefd[2];//check if norminette is happy with this

	ft_printf("argc including the program: %d\n", argc);//just for mvp
	if (argc != 3)//temporary, just for this mvp with file1 cmd1 AT THE END MUST BE EXACTLY 4
		return (ft_printf("include 2 args\n"), 1);
	else
	{
		ini_check(argv, envp);//this will tak all argv to check them
        pipe(pipefd);//to create pipefd[0] to read and pipfd[1] to write
        if (pipe(pipefd) == - 1)
        {
            perror("pipe failed");
            exit (EXIT_FAILURE);
        }
//open file1 and redirection file1 to cmd1
        /*
        file1 = open(argv[1], O_RDONLY);//to open file1 in read-only mode
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
*/
 //redirection cmd1 to pipefd[0]
        
        //code to read the file if open() success and then redirect cmd2 to file2
        file2 = open(argv[2], O_WRONLY);//temporary for MVP file2 cmd2 at the end most be argv[5]
		if (file2 == -1)
        {
            perror ("Error opening file2");
            return (1);
        }
        printf("Successfully opened: %s (fd = %d)\n", argv[2], file2);//testing
        //correct order of redirections: file1 - cmd1, cmd1- pipefd[0], pipefd[1] to cmd2 and cmd2 to file2
/*commented temporary to test pipe()
        if (redir_output(file2))//if redirection fails
        {
            printf("redirection cmd2 file2 good");
            //if redirection failes, close file2
            if (close (file2) == - 1)//if redirection fails
            {
                perror ("Error closing file2 after failed redirection cmd2");
                return (1);
            }
        }
    	if (argv[1])//temporal for mvp with cmd1
        {
            	//need to be found right args before execution
            	//nargv has mallocs to check if succeed after use it
            	nargv = NULL;
                nargv = exec_argv(argc,argv);//will remove original argv[0]
		        if (!nargv)
            	{
            		perror ("Failed to remove first argv called from main");
                	return (1);
            	}
            	else
                	execution(nargv, envp);
        	}
		//Need to close file1 when is not longer used
//This close(file1) was moved after the redirection file1
//check if this is the position for file1_dup. Temporary comment until fork()
//		if (close(file1_dup) == -1)
//		{
//			perror ("Error closing the file");
//			return (1);
//      }
//      include close file2_dup (after use)
*/	
    }
	return (0);
}
