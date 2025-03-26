/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:58:59 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:59:01 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redir_input(int fd)
{
	int	fd_dup;

	fd_dup = dup2(fd, STDIN_FILENO);
	if (fd_dup == -1)
	{
		perror ("Dup2 in redir_input");
		close_fd (fd);
		return (1);
	}
	close_fd(fd);
	return (0);
}

int	redir_output(int fd)
{
	int	fd_dup;

	fd_dup = dup2(fd, STDOUT_FILENO);
	if (fd_dup == -1)
	{
		perror ("Dup2 in redir_output");
		close_fd(fd);
		return (1);
	}
	close_fd(fd);
	return (0);
}

int	setup_redir(int input_fd, int output_fd, t_fd_dup *dup)
{
	int	fd_in_dup;
	int	fd_out_dup;

	fd_in_dup = redir_input(input_fd);
	if (fd_in_dup < 0)
	{
		perror("Failed redir_input");
		return (-1);
	}
	fd_out_dup = redir_output(output_fd);
	if (fd_out_dup < 0)
	{
		close_fd(fd_in_dup);
		perror("Failed redirection OUTPUT");
		return (-1);
	}
	dup -> input_dup = fd_in_dup;
	dup -> output_dup = fd_out_dup;
	return (0);
}

void	child_process(t_pipe_data *data, t_initial_fd *fd, int child_num)
{
	t_fd_dup	dup;
	char		**nargv;

	if (setup_redir(fd -> input_fd, fd -> output_fd, &dup) != 0)
		exit(1);
	//nargv = exec_arg(data -> argc, data -> argv, child_num);
	nargv = exec_arg(data, child_num);//new
	if (!nargv)
	{
		perror ("nargv before execution");
		close_fd(dup.input_dup);
		close_fd(dup.output_dup);
		exit(1);
	}
	execution(nargv, data -> envp);
	perror ("Execution failed in child 1");
	free(nargv);
	close_fd(dup.input_dup);
	close_fd(dup.output_dup);
	exit(1);
}

