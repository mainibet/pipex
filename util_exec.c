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
#include <stdio.h> //just for testing

//to create the new array for execution 
//in case the cmd arg has multiple words
//this means flags or parameteres
char **new_arr_cmd(char *argv)
{
    char **cmd;
    size_t  len;
    
    len = 0;
    cmd = ft_split(argv, ' ');
    if (!cmd)
    {
        perror("malloc in ft_split");
        return (NULL);
    }
    return (cmd);
}
//duplicate cmd_arr to new_arr
//cmd can't be free here because will be sed in exec_arg
//free memory for the str created before the array failed
char **dup_new_cmd (char **cmd)
{
    size_t  len;
    size_t  i;
    char    **new_arg;

    len = 0;
    i = 0;
    while (cmd[len])
        len++;
    new_arg = malloc(sizeof(char *) * (len + 1));
    if (!new_arg)
    {
        perror ("malloc in exec_arg");
        return (NULL);
    }
    while ( i < len)
    {
        new_arg[i] = ft_strdup(cmd[i]);
        if (!new_arg[i])
        {
            perror ("ft_strdup failed in the preocess of new_arg");
            free_memory(new_arg, i);
            return (NULL);
        }
        i++;
    }
    new_arg[len] = NULL;
    return (new_arg);//follow from here
}
//function to get the right args for execution
//I'm not using strdup because I understan args won't change CHECK THIS
//The option with strdup for each child would be smt like:  
//instead of new_arg[0] = argv[2]; do: new_arg[0] = strdup(argv[2]);
//instead of new_arg[0] = argv[argc - 2]; do: new_arg[0] = strdup(argv[argc - 2]);
//execve() consider the firs argv the file that needs to be process by the cmd
//about it man says:  By convention, the first of these  strings (i.e.,
//argv[0])  should  contain the filename associated with the file being executed.
//malloc is for (2) to include only arg with cmd name and NULL to close correctly the arr
//index i begins in 2 position of cmd1
//loop until argc -1 to exclude file2
//new_arg[j] doesn't occupy memory, so doesn't need to be included in malloc
//cmd_arg is the argument that needs to be process for each child
char    **exec_arg(int argc, char **argv, int child_num)
{
    fprintf(stderr, "\n\n\nWe are going to find the correct args befor execution\n\n\n");//testing
    char    **cmd;
    char    **new_arg;
    char    *cmd_arg;

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

//Is a void function because if success go back to the parent and if it fails just will exit
//it will need cmd name in the argv and then find the path with that
//the execute the cmd
//i = 2 where is the position of cmd1
//i will loop until argc -1 where is the final cmd, excluding file2
//final free after successfulexecve call
void	execution(char	**nargv, char **const envp)
{
    fprintf(stderr, "\n\n\nEXECUTION WILL BEGIN\n");//testing
    char    *cmd_name;
    char    *cmd_path;
    size_t  count;

    cmd_name = get_only_cmd(nargv[0]);
    fprintf(stderr, "cmd_name is: %s\n", cmd_name);//testing
    cmd_path = find_path (cmd_name, envp);
    if (!cmd_path)
    {
        perror ("command_path not found");
        free(cmd_name);
        count = 0;
        while (nargv[count])
                count++;
        free_memory(nargv, count);
        free (nargv);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "cmd_path found for execution: %s\n", cmd_path);//testing
    fprintf(stderr, "Execution of cmd[%s] will begin\n", cmd_name);//testing
    fprintf(stderr, "Will be used this as nargv: %s and %s\n", nargv[0], nargv[1]);//testing
    execve(cmd_path, nargv, envp);
    perror ("execve failed");
	free (cmd_name);
    free (cmd_path);
    count = 0;
    while (nargv[count])
            count++;
    free_memory(nargv, count);
    free (nargv);
    exit (EXIT_FAILURE);
}


