/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_findpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:12:45 by albetanc          #+#    #+#             */
/*   Updated: 2025/03/25 13:13:26 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char *find_path(char *argv, char **envp)

// {
//     char *file_path;
//     char **dir;
//     char *path;
//     char *each_path;
//     int i;

//     // path = get_path_env(envp);
//     // if (!path)
//     // {
//     //     perror("PATH env not found");
//     //     return (NULL);
//     // }

//     // dir = ft_split(path, ':');

//     // if (!dir)

//     //     return (NULL);
//     // i = 0;
//     // while (dir[i])
//     {
//     // each_path = ft_strjoin(dir[i], "/");
//     // if (!each_path)
//     // {
//     //     free (dir[i]);
//     //     return (NULL);
//     // }
//     // file_path = ft_strjoin(each_path, argv);
//     // free (each_path);
//     // if (!file_path)
//     // {
//     //     free(dir[i]);
//     //     return (NULL);
//     // }
//     // if (access (file_path, F_OK) == 0)
//     // {
//     //     while (dir[i])
//     //     {
//     //         free(dir[i]);
//     //         i++;
//     //     }
//     //     free (dir);
//     //     return (file_path);
//     // }
//     //     free (dir[i]);
//     //     free (file_path);
//     //     i++;
//     // }
//     free (dir);
//     return (NULL);
// }
//get the array of paths from PATH
static char	**get_path(char **envp)
{
	char	*path;
	char	**dir;

	path = get_path_env(envp);
	if (!path)
	{
		perror("PATH env not found");
		return (NULL);
	}
	dir = ft_split(path, ':');
	if (!dir)
	{
		free(path);
		return (NULL);
	}
	//free(path);//new
	return (dir);
}

//create and check path

//static char	*create_path(char *dir, char *argv)
static char	*create_path(char *dir, char *argv)
{
	char	*each_path;
	char	*file_path;

	each_path = ft_strjoin(dir, "/");
	if (!each_path)
	{
		free (dir);
		return (NULL);
	}
	file_path = ft_strjoin(each_path, argv);
	free (each_path);
	if (!file_path)
	{
		free(dir);
		return (NULL);
	}
	return (file_path);
}

//check he path with access and if found it
//it will be return 

static char	*check_path(char **dir, char *file_path, int i)
{
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
	return (NULL);
}

char	*find_path(char *argv, char **envp)
{
	char	*file_path;
	char	**dir;
	char	*final_path;
	int		i;

	dir = get_path(envp);
	if (!dir)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		file_path = create_path(dir[i], argv);
		if (!file_path)
		{
			while (dir[i])
			{
				free(dir[i]);
				i++;
			}
			free(dir);
			return (NULL);
		}
		final_path = check_path(dir, file_path, i);
		if (final_path)
			return (final_path);
		free(file_path);
		free (dir[i]);
		i++;
	}
	//free(dir[i]);
	free(dir);
	return (NULL);
}
