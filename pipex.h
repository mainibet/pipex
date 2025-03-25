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
# include <fcntl.h> 
# include <unistd.h> 
# include <stdio.h> 
# include <sys/wait.h>


typedef struct s_pipe_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		*pipefd;
	int		fd_in;
}t_pipe_data;

typedef struct s_initial_fd 
{
	int	input_fd;
	int	output_fd;
}t_initial_fd;

typedef struct s_fd_dup
{
	int	input_dup;
	int	output_dup;
}t_fd_dup;


char	*get_path_env(char **envp);
char	*get_only_cmd(char *argv);
char	*find_path(char *argv, char **envp);
int		check_cmd(int argc, char **argv, char **envp);
int		ini_check(int argc, char **argv, char **envp);
int		redir_input(int fd);
int		redir_output(int fd);
int		setup_redir(int input_fd, int output_fd, t_fd_dup *dup);
void	child_process(t_pipe_data *data, t_initial_fd *fd, int child_num);
char	**new_arr_cmd(char *argv);
char	**dup_new_cmd(char **cmd);
char	**exec_arg(int argc, char **argv, int child_num);
void	execution(char	**nargv, char **const envp);
int		close_fd(int fd);
void	free_memory(char **narg, int j);
int		wait_child(pid_t pid, int *status);
int		fork_error(int fd_in, int *pipefd);
void	free_nargv(char **nargv);
char	*malloc_error(void);

#endif

