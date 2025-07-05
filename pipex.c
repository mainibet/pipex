#include "pipex.h"

void	child1(t_pipe_data *data)
{
	t_initial_fd	fd;
	int				child_num;

	child_num = 1;
	close_fd(data -> pipefd[0]);
	fd = (t_initial_fd){data->fd_in, data->pipefd[1]};
	child_process(data, &fd, child_num);
}

void	child2(t_pipe_data *data)
{
	t_initial_fd	fd;
	int				child_num;
	int				fd_out;

	child_num = 2;
	close(data -> pipefd[1]);
	close(data -> fd_in);
	fd_out = open(data -> argv[data -> argc - 1], O_WRONLY 
			| O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror ("open output file");
		exit (-1);
	}
	fd = (t_initial_fd){data -> pipefd[0], fd_out};
	child_process(data, &fd, child_num);
}

static int	parent(struct s_pipe_data *data)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		result;

	result = fork_handle(&pid1, data, 1);
	if (check_fork(result, 0, &status))
		return (result);
	result = fork_handle(&pid2, data, 2);
	if (check_fork(result, pid1, &status))
		return (result);
	close_fd(data -> fd_in);
	close_fd(data -> pipefd[0]);
	close_fd(data -> pipefd[1]);
	if (wait_child(pid1, &status) == -1 || wait_child(pid2, &status) == -1)
	{
		perror ("error waiting child");
		return (-1);
	}
	return (0);
}

static int	setup_pipe(int pipefd[2], int fd_in)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		close_fd(fd_in);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	data;
	int			pipefd[2];
	int			fd_in;

	if (argc != 5)
		return (ft_printf("include 4 args\n"), 1);
	if (ini_check(argc, argv, envp) < 0)
		return (-1);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror ("Error opening input file");
		return (-1);
	}
	if (setup_pipe(pipefd, fd_in) == -1)
		return (-1);
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.pipefd = pipefd;
	data.fd_in = fd_in;
	parent(&data);
	return (0);
}
