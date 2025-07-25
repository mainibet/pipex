#include "pipex.h"

int	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror ("error closing fd");
		return (1);
	}
	return (0);
}

void	free_memory(char **narg, int j)
{
	while (j > 0)
	{
		free (narg[j - 1]);
		j--;
	}
	free (narg);
}

int	fork_error(int fd_in, int *pipefd)
{
	close_fd(fd_in);
	close_fd(pipefd[0]);
	close_fd(pipefd[1]);
	return (-1);
}

char	*malloc_error(void)
{
	perror("Malloc error");
	return (NULL);
}
