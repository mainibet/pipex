/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_initial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:58:46 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:58:48 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_only_cmd(char *argv)
{
	char	*space;
	char	*cmd;
	size_t	len;

	space = ft_strchr(argv, ' ');
	if (space)
	{
		len = space - argv;
		cmd = malloc (sizeof (char) * len + 1);
		if (!cmd)
			return (malloc_error());
		ft_strlcpy (cmd, argv, len + 1);
	}
	else
	{
		cmd = ft_strdup(argv);
		if (!cmd)
			return (malloc_error());
	}
	return (cmd);
}

void	free_name_path(char *cmd_name, char *cmd_path)
{
	free (cmd_path);
	free (cmd_name);
}

int	check_cmd(int argc, char **argv, char **envp)
{
	int		i;
	char	*cmd_name;
	char	*cmd_path;

	i = 2;
	while (i < argc - 1)
	{
		cmd_name = get_only_cmd(argv[i]);
		cmd_path = find_path(cmd_name, envp);
		if (!cmd_path)
		{
			perror("Not path found");
			free(cmd_name);
			return (-1);
		}
		if ((access(cmd_path, X_OK) == -1))
		{
			perror("cmd2 is not executable");
			free_name_path(cmd_name, cmd_path);
			return (-1);
		}
		free_name_path(cmd_name, cmd_path);
		i++;
	}
	return (0);
}

int	ini_check(int argc, char **argv, char **envp)
{
	if (access(argv[1], F_OK) == -1)
	{
		perror("At least 1 file doesn't exist");
		return (-1);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror("No read permissions for file1");
		return (-1);
	}
	if (check_cmd(argc, argv, envp) != 0)
	{
		perror("Non executable command");
		return (-1);
	}
	return (0);
}
