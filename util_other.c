/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:59:35 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:59:37 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //just for testing

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
//clean-up memory in strings inside an array 
void    free_memory (char **narg, int   j)
{
    while (j > 0)
    {
        free (narg[j - 1]);
        j--;
    }
    free (narg);
}

//parent function to do the fork() for the child processess
int wait_child(pid_t  pid, int *status)
{
    fprintf(stderr, "parent is about to wait");//testing
    if (waitpid(pid, status, 0) == - 1)
    {
        perror ("Error waiting for child");
        return (-1);
    }
    if (WIFEXITED(*status) && WEXITSTATUS(*status) != 0)
    {
        perror ("Child failed");
        return (-1);
    }
    fprintf(stderr, "Child process %d completed\n", pid);//testing
    return (0);
}

//function to close fd when a fork fails
int fork_error(int fd_in, int *pipefd)
{
    close_fd(fd_in);
    fprintf(stderr, "Closed correctly fd[0] which is file1\n");//testing
    close_fd(pipefd[0]);
    fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
    close_fd(pipefd[1]);
    fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
    return (-1);
}
