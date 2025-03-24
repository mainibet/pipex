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
		{
			perror ("Malloc in get only cmd");
			return (NULL);
		}
		ft_strlcpy (cmd, argv, len + 1);
	}
	else
	{
		cmd = ft_strdup(argv);
		if (!cmd)
		{
			perror ("Malloc in get only cmd");
			return (NULL);
		}
	}
	return (cmd);
}

char	*find_path(char *argv, char **envp)
{
	char	*file_path;
	char	**dir;
	char	*path;
	char	*each_path;
	int		i;

	path = get_path_env(envp);
	if (!path)
	{
		perror("PATH env not found");
		return (NULL);
	}
	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);

	i = 0;
	while (dir[i])
	{
		each_path = ft_strjoin(dir[i], "/");
		if (!each_path)
		{
			free (dir[i]);
			return (NULL);
		}
		file_path = ft_strjoin(each_path, argv);
		free (each_path);
		if (!file_path)
		{
			free(dir[i]);
			return (NULL);
		}
		if (access (file_path, F_OK) == 0)
		{
			while (dir[i])
			{
				free(dir[i]);
				i++;
			}
			free (dir);
			return (file_path);
		}
		free (dir[i]);
		free (file_path);
		i++;
	}
	free (dir);
	return (NULL);
}

int check_cmd(int argc, char **argv, char **envp)
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
			free(cmd_name);
			free(cmd_path);
			return (-1);
		}
		free (cmd_path);
		free (cmd_name);
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




