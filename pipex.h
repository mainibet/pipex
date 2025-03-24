/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:58:49 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/18 12:37:59 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h> //to open()
# include <unistd.h> //to accese to close() to read() to write() pipe() dup() execve() dup2() fork()
# include <stdio.h> //to perror (validar si esta o erno)
# include <sys/wait.h>//to waitpid() and wait() fork() includes macros WIFEXITED and WEXITSTATUS

//struct definition
typedef struct s_pipe_data
{
    int argc;
    char **argv;
    char **envp;
    int *pipefd;
    int fd_in;
}t_pipe_data;
//struct for file1 and file2
typedef struct s_initial_fd 
{
    int input_fd;
    int output_fd;
}t_initial_fd;
//structu for fd duplicated
typedef struct s_fd_dup
{
    int input_dup;
    int output_dup;
}t_fd_dup;
//function ptototype

#endif

