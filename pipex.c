/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:58:29 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:58:32 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //just for testing

//process for cmd1 (FORK1)
//Function void because it succees or 
//exit to go back to the parent
//pipe_data includes pipefd
//COMMENTS OF THE PREVIOUS VERSION OF CHILD1
//*nargv is the new array of arguments needed for execution
//fd_dup is the dup of file1 after the redirection
//pipefd_dup is the dup of pipefd after the redirection 
//pipefd[0] not needed in this process but inherited
//redirect file1 as input of cmd1
//refirect cmd1 to piepfd[1] stdout
//If any redirection fail the fd dups will be close 
//(the original fd are close in the redir functions)
//After all redirections will be done before the execution
//The execution will be done with the duplicated fd
//Need to be found the right arg for execution (nargv) to get in position 0 the cmd file
//If the execution succees pipefd[1] can't manually be closed in the child1 and nargv 
//can't be free, needs to be close in the parent and the child close it automatically
//if fails needs to exit(1) to stop the process and go back to the parent
//struct fd initialized with arg important for child2
//child process called with that struct
//process for cmd2(FORK2)
//pipefd[1] not needed in this process
void    child1(t_pipe_data *data)
{
    int child_num;
    t_initial_fd    fd;

    child_num = 1;
    fprintf(stderr, "\nCHILD1 WILL BEGIN\n\n\n");//testing
    close_fd(data -> pipefd[0]);
    fd = (t_initial_fd){data->fd_in, data->pipefd[1]};//check norm
    child_process(data, &fd, child_num);
}

//COMMENTS OF THE PREVIOUS VERSION OF CHILD2

//If any reirection fails will be close the dup fd opened before
//File2 and pipfd are close in redir functions if that fails
//After all the reirection will be done the execution
//First redir input from pipe to cmd2
//then redirection output from cmd2 to file2
//void child2 (int argc, char **argv, char **envp, int  *pipefd, int fd_in)
void    child2(t_pipe_data *data)
{
    int child_num;
    t_initial_fd    fd;
    int fd_out;

    child_num = 2;
    fprintf(stderr, "\nCHILD2 WILL BEGIN\n\n\n");//testing
    close(data -> pipefd[1]);
    close(data -> fd_in);
    fd_out = open(data -> argv[data -> argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == - 1)
	{
	    perror ("open output file");
		exit (- 1);
	}
    fd = (t_initial_fd){data -> pipefd[0], fd_out};
    child_process(data, &fd, child_num);
}

//pid1 is child1 (cmd1)
//pid2 is child2 (cmd2)
//pid == 0 means we are in child process
//pid > 0 means we are in the parent process
//fork() returns -1 if something fails
int parent(struct s_pipe_data *data)
{
    pid_t   pid1;
    pid_t   pid2;
    int status1;
    int status2;

    pid1 = fork();
    if (pid1 == - 1)
    {
        perror ("Fork failed for child1");
        return (fork_error(data->fd_in, data->pipefd));
    }
    else if (pid1 == 0)
        child1(data);
    pid2 = fork();
    if (pid2 == -1)
    {
        perror ("Fork failed for child2");
        if (wait_child(pid1, &status1) == -1)
            perror("Error waiting child1");
        return (fork_error(data->fd_in, data->pipefd));
    }
    else if (pid2 == 0)
        child2(data);
    fprintf(stderr, "We will close in the parent all the fd opened and after forks\n");//testing
    close_fd(data -> fd_in);
    fprintf(stderr, "Closed correctly fd_in which is file1\n");//testing
    close_fd(data -> pipefd[0]);
    fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
    close_fd(data -> pipefd[1]);
    fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
    if (wait_child(pid1, &status1) == - 1)
    {
        perror ("error waiting child1");
        return (-1);
    }
    fprintf(stderr, "Child1 finished now we are in the parent about to begin child2\n");//testing
    if (wait_child(pid2, &status2) == - 1)
    {
        perror ("Error waiting child2");
        return (-1);
    }
    fprintf(stderr, "We are again in the parent after success of child2\n");//testing
    return (0);
}

//mandatory part has to work exactly with 4arg
//pipefd[2] Pipe for inter-process communication
//correct order of redirections (this will happen in childs):
//file1 - cmd1, cmd1- pipefd[0], pipefd[1] to cmd2 and cmd2 to file2
//open_fd will do the initial check of all arg and open file1 and file2
//at the end closed std fd
int	main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    int fd_in;
    t_pipe_data data;//check norm
				
    ft_printf("argc including the program: %d\n", argc);//testing
    if (argc != 5)
        return (ft_printf("include 4 args\n"), 1);
    if (ini_check(argc, argv, envp) < 0)
        return (-1);
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == - 1)
    {
        perror ("Error opening file1");
        return (-1);
    }
    if (pipe(pipefd) == - 1)
    {
        perror("pipe failed");
        close_fd(fd_in);
        return (-1);
    }
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    data.pipefd = pipefd;
    data.fd_in = fd_in;
    parent(&data);
    fprintf(stderr, "\n\n\nPROGRAM FINISHED\n\n\n");//testing
    return (0);
}
