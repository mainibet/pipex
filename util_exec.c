/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:59:22 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/24 17:59:24 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**new_arr_cmd(char *argv)
{
	char	**cmd;
	size_t	len;

	len = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		perror("malloc in ft_split");
		return (NULL);
	}
	return (cmd);
}

char	**dup_new_cmd(char **cmd)
{
	size_t	len;
	size_t	i;
	char	**new_arg;

	len = 0;
	i = 0;
	while (cmd[len])
		len++;
	if (!(new_arg = malloc(sizeof(char *) * (len + 1))))
	{
		perror ("malloc in exec_arg");
		return (NULL);
	}
	while (i < len)
	{
		if (!(new_arg[i] = ft_strdup(cmd[i])))
		{
			perror ("ft_strdup failed in the preocess of new_arg");
			free_memory(new_arg, i);
			return (NULL);
		}
		i++;
	}
	new_arg[len] = NULL;
	return (new_arg);
}

char	**exec_arg(int argc, char **argv, int child_num)
{
	char	**cmd;
	char	**new_arg;
	char	*cmd_arg;

	if (child_num == 1)
		cmd_arg = argv[2];
	else if (child_num == 2)
		cmd_arg = argv[argc - 2];
	else
		return (NULL);    
	if (ft_strchr(cmd_arg, ' '))
	{
		cmd = new_arr_cmd(cmd_arg);
		if (!cmd)
		{
			perror("new_arr_cmd in exec_arg");
			return (NULL);
		}
		new_arg = dup_new_cmd(cmd);
		if (!new_arg)
		{
			perror ("malloc in exec_arg");
			free_memory(cmd, 0);
			free (cmd);
			return (NULL);
		}
	}
	else
	{
		new_arg = malloc (sizeof(char *) * (2));
		if (!new_arg)
		{
			perror ("malloc failed in exec_arg");
			return (NULL);
		}
		new_arg[0] = cmd_arg;
		new_arg[1] = NULL;
	}
	return (new_arg);
}

static void	free_nargv(char **nargv)
{
	size_t	count;

	count = 0;
	while (nargv[count])
		count++;
	free_memory(nargv, count);
	free(nargv);
}

void	execution(char	**nargv, char **const envp)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = get_only_cmd(nargv[0]);
	cmd_path = find_path (cmd_name, envp);
	if (!cmd_path)
	{
		perror ("command_path not found");
		free(cmd_name);
		free_nargv(nargv);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, nargv, envp);
	perror ("execve failed");
	free (cmd_name);
	free (cmd_path);
	free_nargv(nargv);
	exit (EXIT_FAILURE);
}


