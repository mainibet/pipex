/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:07:04 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/26 16:07:06 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_child(pid_t pid, int *status)
{
	if (waitpid(pid, status, 0) == -1)
	{
		perror ("Error waiting for child");
		return (-1);
	}
	return (0);
}

int	fork_handle(pid_t *pid, t_pipe_data *data, int child_num)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror ("Fork failed");
		return (fork_error(data->fd_in, data->pipefd));
	}
	if (*pid == 0)
	{
		if (child_num == 1)
			child1(data);
		else if (child_num == 2)
			child2(data);
		return (1);
	}
	return (0);
}

int	check_fork(int result, pid_t pid1, int *status)
{
	if (result != 0)
	{
		if (result == 1)
			return (0);
		else
		{
			if (pid1 != 0)
				wait_child(pid1, status);
			return (result);
		}
	}
	return (0);
}
