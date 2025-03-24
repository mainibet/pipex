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
typedef struct
{
    int argc;
    char **argv;
    char **envp;
    int *pipefd;
    int fd_in;
}s_pipe_data

//function ptototype

#endif

