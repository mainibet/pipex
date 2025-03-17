/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:36:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/17 12:47:52 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//needed as a parameter of execve
//strncmp is to compare the first 5 bytes
//the return will be +5 to get it withou :PATH="
//At the end it will return NULl if path is not found (hanlding error)
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
//If (space) means when space is not NULL
//I find len to get the length of the command name (without flags or parameters)
//When return(argv) it means there is no space so the return will be the same cmd name
//Other option I explored was to return(ft_strdup(argv)) but I think that would be ok to return directly argv because I won't change anything and avoid to malloc
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
            perror ("Malloc failed to get only cmd");
            free (cmd);
            return (NULL);
        }
        if (cmd)
        {
            ft_strlcpy (cmd, argv, len + 1);
            return (cmd); //follow where to free cmd from here
        }
    }
    return (argv);
}

#include <stdio.h>

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
	i = 0;
	while (dir[i])
	{
		each_path = ft_strjoin(dir[i], "/");
		file_path = ft_strjoin(each_path, argv);
		free (each_path);
		if (access (file_path, F_OK) == 0)
		{	//just for testing
			printf("Path found for cmd1: %s\n", file_path);//testing
			return (file_path);//free in other place
		}//for testing
		free (file_path);
		i++;
	}
	return (NULL);
}
/*
//TESTING: find_path specific for executable files cmd1 cmd2
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
//reusable handling error when close fd
int close_fd(int fd)
{
    if (close(fd) == - 1)
    {
        perror ("error closing fd");
        return (1);
    }
    return (0);
}
#include <stdio.h>//just for testing
//child1
//to redirect input from file1 to cmd1 and from pipe[1] to cmd2

int	redir_input(int fd)
{
	int	fd_dup;

	fd_dup = dup2(fd, STDIN_FILENO);//el fd que entra como parametro seria pipefd[0] o file1
	if (fd_dup == -1)//creo que falta cerrar en caso de error el fd_dup
	{
		perror ("Dup2 failed stdin");
		return (1);
	}
	fprintf(stderr, "Successfull redirection\n");//testing in stderr to see it in terminal
    close_fd(fd);//shorter version, test it if close the correct fd, deberia ser el que se duplico, o sea pipefd[0] o file1.
//	if (close(fd) == -1)
//	{
//		perror ("Error closing the file1 after redirection file1 to cmd1");
//		return (1);
//	}//check where to close fd_dup after is used.
	return (0);
}

//to redirect output. firsti MVP cmd2 to file2 then cmd1 to pipe[0]
//child2
#include <stdio.h> //testing
int redir_output(int fd)
{
    fprintf(stderr, "Now will begin redir_output to file2");//testing
    int fd_dup;//the one created to work with
    
    fd_dup = dup2(fd, STDOUT_FILENO);//fd is the one parameter can be pipefd[1] or file2
    if (fd_dup == -1)//needs to be close fd_dup it fails
    {
        perror ("Dup2 failed with cmd2 to file2");
        return (1);
    }
    fprintf(stderr, "Successfull redirection\n");//testing
    close_fd(fd);//this will be file2 or pipfed[1] after dup2
    //if (close (fd) == - 1)//close file2 after dup2 in redirection
    //{
      //  perror ("Error closing file2 or pipefd[0] after redirection cmd2 to file2");
    //    return (1);
   // }//pending to close fd_dup after use
    return (0);
}
//find the arg with the cmd and duplicate it to include it later in the new array as argv[[0]]
char *get_narg(char *argv)
{
    char    *cmd_arg;

    cmd_arg = ft_strdup(argv);
    if (!cmd_arg)
    {
        perror ("strdup failed in get_arg");
        return (NULL);//because it failed
    }
    else
        return (cmd_arg);//check where to free after use
}
//clean-up memory if there was an error when creating the new arrary to exec
void    free_memory (char **narg, int   j)
{
    while (j > 0)
    {
        free (narg[j - 1]);
        j--;
    }
    free (narg);
}

//function to get the right args for execution
//execve() consider the firs argv the file that needs to be process by the cmd//about it man says:  By convention, the first of these  strings (i.e.,  argv[0])  should  contain the filename associated with the file being executed.
//if (argc <= 1) to check there are enough arg
//malloc is for (argc -3) because we exclude the programs name, file1 and file2
//i is the index of the old array
//j is the index in the new array
//index i begins in 2 position of cmd1
//loop until argc -1 to exclude file2
//new_arg[j] doesn't occupy memory, so doesn't need to be included in malloc
char    **exec_arg(int argc, char **argv)
{
    char    **new_arg;
    int i;//loop in old arr
    int j;//loop in new array

    if (argc <= 1)
        return (NULL);
    new_arg = malloc (sizeof(char *) * (argc - 3));//check
        if (!new_arg)
    {
        perror ("malloc failed in exec_arg");
        return (NULL);
    }
    j = 0;
    i = 2;
    while (i < argc - 1)
        {
            new_arg[j] = get_narg(argv[i]);
            if (!new_arg[j])
            {
                free_memory(new_arg, j);
                return (NULL);
            }
            i++;
            j++;
        }
    new_arg[j] = NULL;
    return (new_arg);//check later where to free after use
}

#include <stdio.h> //just for testing
//it will need cmd name in the argv and then find the path with that
//the execute the cmd
//i = 2 where is the position of cmd1
//i will loop until argc -1 where is the final cmd, excluding file2
//final free after successfulexecve call
//REFACTOR: make it work with any command, depend on how is called.
int	execution(int argc, char	**nargv, char **const envp)
{
    char    *cmd_name;
    char    *cmd_path;
    int i;

    i = 2;
    while (i < argc - 1)
    {
        cmd_name = get_only_cmd(nargv[i]);
        cmd_path = find_path (cmd_name, envp);
        if (!cmd_path)
        {
            perror ("command_path not found");//check if previous mallocs needs to be free here
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "cmd_path found for execution: %s\n", cmd_path);//testing
        fprintf(stderr, "Execution of cmd[%d] will begin\n", i - 1);//testing
        if (execve(cmd_path, nargv, envp) == - 1)
        {
            perror ("execve failed");
		    free (cmd_path);//check if previous mallocs needs to be free here
		    exit (EXIT_FAILURE);
        }
        free(cmd_path);// //check if previous mallocs needs to be free here
        i++;
    }
    return (0);
}

#include <stdio.h> //just for testing
//i begins in 2 which is the position of cmd1
//will be check until argv[argc -2] which will be the last cmd before file2
//argv[argc -1] is file2
int check_cmd(int argc, char **argv, char **envp)
{
    int i;
    char    *cmd_name;

    i = 2;
    while (i < argc - 1)
    {
        cmd_name = get_only_cmd(argv[i]);
        if (access(find_path(cmd_name, envp), X_OK) == -1)//pending fix parameters, needs to be the path
        {
            perror("cmd2 is not executable");
            return (1);
        }
        i++;
    }
    printf("cmds passed initial check\n");//testing
    return (0);
}

//initial check
//check existence of file1 and file2
//check if file 1 has read permissions
//check if file 2 has write permissions
//check if cmds are executables
int	ini_check(int argc, char **argv, char **envp)
{
	if ((access(argv[1], F_OK) == -1) || (access(argv[argc - 1], F_OK) == -1))//to check if the file2 exist
	{
		perror("At least 1 file doesn't exist");
		return (1);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror("No read permissions for file1");
		return (1);
	}
    if (access(argv[argc - 1], W_OK) == - 1)
    {
        perror ("No write permissions for file2");
        return (1);
    }
    printf("File1 and file2 passed initial check\n");//for testing
    if (check_cmd(argc, argv, envp) != 0)
    {
        perror("Non executable command");
        return (1);
    }
	return (0);
}
//process for cmd1 (FORK1)
//pipefd[0] not needed in this process but inherited
//redirect file1 as input of cmd1
//refirect cmd1 to piepfd[1] stdout
//If any redirection fail the fd will be close (file1 or pipefd[1])
//After all redirections will be done the execution
//before execution needs to be found the correct arg for execve with exec_arg
int child1(int argc, int  *pipefd, char **argv, char **envp)//make it more general
{
    close_fd(pipefd[0]);
		if (redir_input(*argv[1]))//I change file1 to **file1 check it
			close_fd (*argvp1[1]);//I changed file1 to **file1, check it
        if (redir_output(pipefd[1]))
            close_fd (pipefd[1]);
        if (argv[1])//temporal for mvp with cmd1
        {
            	//need to be found right args before execution
            	//nargv has mallocs to check if succeed after use it
            	nargv = NULL;
                nargv = exec_arg(argc,argv);//will remove original argv[0] and will exclude file1 and file2
		        if (!nargv)
            	{
            		perror ("Failed to remove first argv called from main");
                	return (1);
            	}
            	else
                	execution(nargv, envp);
        	}
        execution(cmd1, envp);//here the first param is the one calle nargv in the main
        //after execution close fd used
    return (0);//check if this is ok
}

//process for cmd2(FORK2)
//pipefd[1] not needed in this process
//If any reirection fails will be close the used fd pipefd[0] or file2
//After all the reirection will be done the execution
int child2 (int  *pipefd, char **cmd1, char **file2, char **envp)//make it more general
{
    close(pipefd[1]);
    //redirection pipefd[0] to cmd2 stdin
    if (redir_input(pipefd[0]))
        close_fd(pipefd[0]);
    //redirection cmd2 to file2
    if (redir_output(**file2))//check if works, i change it from file2 to **file2
    {//testing
        fprintf("redirection cmd2 file2 good");//testing
        close_fd(**file2)//check if works, I changed from file2 to **file2
    }//close pipefd[0] after using it, same file2
    //before execution call execv_arg
    if (argv[1])//temporal for mvp with cmd1
        {
            	//need to be found right args before execution
            	//nargv has mallocs to check if succeed after use it
            	nargv = NULL;
                nargv = exec_arg(argc,argv);//will remove original argv[0] and will exclude file1 and file2
		        if (!nargv)
            	{
            		perror ("Failed to remove first argv called from main");
                	return (1);
            	}
            	else
                	execution(nargv, envp);
        	}
    execution(cmd2, envp);//here the first param is the one calle nargv in the main
    //after execution close fd use
    return (0);//check is this is ok
}
//clean main version
int	main(int argc, char **argv, char **envp)//mandatory part has to work exactly with 4arg
{
	int	file1;//to open fd file1
	int file2;//to open file2
    char    **nargv;
    int pipefd[2];//check if norminette is happy with this
    pid_t   pid1;
    pid_t   pid2;
    int status1;
    int status2;

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
        //first child
        pid1 = fork();
        if (pid1 == 0)//check explanation in obsidian
        {
            child1(pipefd, argv, NULL, envp);//ojo que debe ser nargv y revisar si ese NULL si se necesita
            exit (0);
        }
        else
        {
            pid2 = fork();
            if (pid2 == 0)
            {
                child2(pipefd, argv, NULL, envp);//revisar que arg necesita y que recibe
                exit(0);
            }
            else
            {
                waitpid(pid1, &status1, 0);  
                waitpid(pid2, &status2, 0);          
            }
        }
//open file1 to be used in child1 when redirection file1 to cmd1

        file1 = open(argv[1], O_RDONLY);//to open file1 in read-only mode
		if (file1 == - 1)
		{
			perror ("Error opening file");
			return (1);
		}
//open file2 to be used in child2 when redirection cmd2 to file2
 
        file2 = open(argv[2], O_WRONLY);//temporary for MVP file2 cmd2 at the end most be argv[5]
		if (file2 == -1)
        {
            perror ("Error opening file2");
            return (1);
        }
        fprintf(stderr, "Successfully opened\n");//testing
//correct order of redirections (this will happen in childs): file1 - cmd1, cmd1- pipefd[0], pipefd[1] to cmd2 and cmd2 to file2
//the following to get nargv will be moved to each child	
    // if (argv[1])//temporal for mvp with cmd1
        // {
        //     	//need to be found right args before execution
        //     	//nargv has mallocs to check if succeed after use it
        //     	nargv = NULL;
        //         nargv = exec_arg(argc,argv);//will remove original argv[0] and will exclude file1 and file2
		//         if (!nargv)
        //     	{
        //     		perror ("Failed to remove first argv called from main");
        //         	return (1);
        //     	}
        //     	else
        //         	execution(nargv, envp);
        // 	}
//after child process close all fd opened
		close_fd(file1_dup);
        close_fd(file2_dup);//check
        close_fd(pipefd[0]);//check
        close_fd(pipefd[1]);//check
    }
	return (0);
}

//previous main

// int	main(int argc, char **argv, char **envp)//mandatory part has to work exactly with 4arg
// {
// //	int	file1;//to open fd file1
// 	int file2;//to opoen file2
// //    char    **nargv;
//     int pipefd[2];//check if norminette is happy with this
//     pid_t   pid1;
//     int status1;

// 	ft_printf("argc including the program: %d\n", argc);//just for mvp
// 	if (argc != 3)//temporary, just for this mvp with file1 cmd1 AT THE END MUST BE EXACTLY 4
// 		return (ft_printf("include 2 args\n"), 1);
// 	else
// 	{
// 		ini_check(argv, envp);//this will tak all argv to check them
//         pipe(pipefd);//to create pipefd[0] to read and pipfd[1] to write
//         if (pipe(pipefd) == - 1)
//         {
//             perror("pipe failed");
//             exit (EXIT_FAILURE);
//         }
//         //first child
//         pid1 = fork();
//         if (pid1 == 0);
//         {
//             child1(pipefd, argv, NULL, envp);//ojo que debe ser nargv y revisar si ese NULL si se necesita
//             exit (0);
//         }
//         else
//         {
//             child2(pipefd, argv, NULL, envp);//revisar que arg necesita y que recibe
//             exit(0);
//         }
//         else
//         {
//             waitpid(pid1, &status1, 0);  
//             eaitpid(pid2, &status2, 0);          
//         }
// //open file1 and redirection file1 to cmd1
//         /*
//         file1 = open(argv[1], O_RDONLY);//to open file1 in read-only mode
// 		if (file1 == - 1)
// 		{
// 			perror ("Error opening file");
// 			return (1);
// 		}
// 		//to redirec file1 as intput of cmd1
// 		if (redir_input(file1))
// 		{
// 			//if redirection fails, close file1
// 			if (close(file1) == -1)
// 			{
// 				perror("Error closing the file");
// 				return (1);
// 			}
// 		}
// */
//  //redirection cmd1 to pipefd[1] stdout
//  /*
//         if (redir_output(pipefd[1]))//in the child process before this close pipefd[0];
//         {
//             if (close(pipefd[1]))
//             {
//                 perror ("Error closing pipfd[1]");
//                 return (1);
//             }
//         }//in the child process close pipefd[1] after using it
//          //can be close like: if (close(pipefd[1]) == -1) { perror("error closing pipfd[1]"); return (1) }
// */
//         //redirection pipefd[0] to cmd2 stdin
//         if (redir_input(pipefd[0]))
//         {
//             if (close(pipefd[0] == - 1))
//             {
//                 perror ("Error closing pipefd[0]");
//                 return (1);
//             }
//         }//close pipefd after using it
//         //code to read the file if open() success and then redirect cmd2 to file2
//         file2 = open(argv[2], O_WRONLY);//temporary for MVP file2 cmd2 at the end most be argv[5]
// 		if (file2 == -1)
//         {
//             perror ("Error opening file2");
//             return (1);
//         }
//         fprintf(stderr, "Successfully opened\n");//testing
//         //correct order of redirections: file1 - cmd1, cmd1- pipefd[0], pipefd[1] to cmd2 and cmd2 to file2
// /*commented temporary to test pipe()
//         if (redir_output(file2))//if redirection fails
//         {
//             printf("redirection cmd2 file2 good");
//             //if redirection failes, close file2
//             if (close (file2) == - 1)//if redirection fails
//             {
//                 perror ("Error closing file2 after failed redirection cmd2");
//                 return (1);
//             }
//         }//close pipefd after using it
//     	if (argv[1])//temporal for mvp with cmd1
//         {
//             	//need to be found right args before execution
//             	//nargv has mallocs to check if succeed after use it
//             	nargv = NULL;
//                 nargv = exec_argv(argc,argv);//will remove original argv[0]
// 		        if (!nargv)
//             	{
//             		perror ("Failed to remove first argv called from main");
//                 	return (1);
//             	}
//             	else
//                 	execution(nargv, envp);
//         	}
// 		//Need to close file1 when is not longer used
// //This close(file1) was moved after the redirection file1
// //check if this is the position for file1_dup. Temporary comment until fork()
// //		if (close(file1_dup) == -1)
// //		{
// //			perror ("Error closing the file");
// //			return (1);
// //      }
// //      include close file2_dup (after use)
// */	
//     }
// 	return (0);
// }
