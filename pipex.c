#include "pipex.h"

//needed as a parameter of execve
//strncmp is to compare the first 5 bytes
//the return will be +5 to get it withou :PATH="
//At the end it will return NULl if path is not found (hanlding error)
//Return NULL if is not found
char	*get_path_env(char **envp)
{
	int	i;

    if (!envp || !envp[0])
    {
        fprintf(stderr, "Error: no environment variables available.\n");//testing
        return (NULL);
    }
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
//get_path_testing
/*#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*path_env;

	path_env = get_path_env(envp);
	if (path_env)
		printf("PATH found: %s\n", path_env);
	else
		printf ("PATH not found\n");
	return (0);
}
*/

//To get the cmd name in the argv in cases like "echo hello world" or "cat -n" or "ls -l"
//This will make the function find_path work correctly before the execution and in the initial check
//If (space) means when space is not NULL
//I find len to get the length of the command name (without flags or parameters)
//When return(argv) it means there is no space so the return will be the same cmd name
//Other option I explored was to return(ft_strdup(argv)) but I think that would be ok 
//make strdup of argv makes easier manage the free only for that I decide it to do it
char *get_only_cmd(char *argv)
{
    char *space;
    char *cmd;
    size_t len;

    space = ft_strchr(argv, ' ');
    if (space)
    {
        len = space - argv;
        cmd = malloc (sizeof (char) * len + 1);
        if (!cmd)
        {
            perror ("Malloc failed to get only cmd");
            return (NULL);
        }
        ft_strlcpy (cmd, argv, len + 1);
        return (cmd);
    }
    else
        cmd = ft_strdup(argv);
    fprintf(stderr, "cmd_name in get_only_cmd is: %s\n", argv);//testing
        return (cmd);
}

//clean-up memory in strings inside an array 
void    free_memory (char **narg, int   j)
{
    while (j > 0)
    {
        free (narg[j - 1]);
        j--;
    }
    free (narg);
}

#include <stdio.h>//testing

//To find executables cmd1 or cmd2
//file_pat is to hold the return
//dir is the array with all the splited directories
char	*find_path(char *argv, char **envp)
{
	char	*file_path;
	char	**dir;
	char	*path;
	char	*each_path;
	int	i;

	path = get_path_env(envp);
	if (!path)
	{
		perror("PATH env not found");
		return (NULL);
	}
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		each_path = ft_strjoin(dir[i], "/");
		file_path = ft_strjoin(each_path, argv);
		free (each_path);
		if (access (file_path, F_OK) == 0)
		{
			fprintf(stderr, "Path found for cmd: %s\n", file_path);//TESTING
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
/*
//TESTING: find_path specific for executable files cmd1 cmd2
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	*command_path;

	if (argc == 2)
	{
		command_path = find_path(argv[1], envp);
		printf("specific path: %s\n", command_path);
	}
	else
		printf ("Command path not found\n");
	return (0);
}
*/
//reusable handling error when close fd
int close_fd(int fd)
{
    if (close(fd) == - 1)
    {
        perror ("error closing fd");
        return (1);
    }
    return (0);
}
#include <stdio.h>//just for testing
//to redirect input from file1 to cmd1 and from pipe[0] to cmd2
//fd is the one that will be duplicated (file1 or pipefd[0])
//fd_dup is the fd that cmd will use
int	redir_input(int fd)
{
	int	fd_dup;

	fd_dup = dup2(fd, STDIN_FILENO);
	if (fd_dup == - 1)
	{
		perror ("Dup2 failed stdin in redir_input");
        close_fd (fd);//NEW
		return (1);
	}
	fprintf(stderr, "Successfull redirection\n");//testing in stderr to see it in terminal
    close_fd(fd);
	return (0);
}

//to redirect output pipefd[1] nad file2
//fd is the one duplicated
//fd_dup is the one that cmd will use
#include <stdio.h> //testing
int redir_output(int fd)
{
    fprintf(stderr, "Now will begin redir_output to file2\n");//testing
    int fd_dup;
    
    fd_dup = dup2(fd, STDOUT_FILENO);//fd is the one parameter can be pipefd[1] or file2
    if (fd_dup == -1)
    {
        perror ("Dup2 failed with cmd2 to file2 in redir_output");
        close_fd(fd);//NEW
        return (1);
    }
    fprintf(stderr, "Successfull redirection\n");//testing
    close_fd(fd);
    return (0);
}
// //find the arg with the cmd and duplicate it to include it later in the new array as argv[[0]]
// char *get_narg(char *argv)
// {
//     char    *cmd_arg;

//     cmd_arg = ft_strdup(argv);
//     if (!cmd_arg)
//     {
//         perror ("strdup failed in get_arg");
//         return (NULL);//because it failed
//     }
//     else
//         return (cmd_arg);//check where to free after use
// }
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
        perror("malloc failed in ft_split");
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
        perror ("malloc failed in exec_arg");
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
char    **exec_arg(int argc, char **argv, int child_num)
{
    fprintf(stderr, "\n\n\nWe are going to find the correct args befor execution\n\n\n");//testing
    char    **cmd;
    char    **new_arg;
    size_t  count;//new

    if (ft_strchr(argv[2], ' ') && child_num == 1)
    {
        cmd = new_arr_cmd(argv[2]);
        if (!cmd)
        {
            perror("error getting new_arr_cmd in exec_arg");
            return (NULL);
        }
        count = 0;//new
        while (cmd[count])//new
            count++;//new
        new_arg = dup_new_cmd(cmd);
        if (!new_arg)
        {
            perror ("malloc failed in exec_arg");
            free_memory(cmd, count);//new
            free (cmd);
            return (NULL);
        }
    }
    else if (ft_strchr(argv[argc - 2], ' ') && child_num == 2)
    {
        cmd = new_arr_cmd(argv[argc - 2]);
        if (!cmd)
        {
            perror("error getting new_arr_cmd in exec_arg");
            return (NULL);
        }
        count = 0;//new
        while (cmd[count])//new
            count++;//new
        new_arg = dup_new_cmd(cmd);
        if (!new_arg)
        {
            perror ("malloc failed in exec_arg");
            free_memory(cmd, count);
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
        new_arg[1] = NULL;
        if (child_num == 1)
           new_arg[0] = argv[2];
        else if (child_num == 2)
          new_arg[0] = argv[argc - 2];
        new_arg[1] = NULL;
    }
    return (new_arg);
}

#include <stdio.h> //just for testing
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
    count = 0;
    while (nargv[count])
            count++;
    execve(cmd_path, nargv, envp);
    perror ("execve failed");
	free (cmd_name);
    free (cmd_path);
    free_memory(nargv, count);
    free (nargv);
    exit (EXIT_FAILURE);
}

#include <stdio.h> //just for testing
//i begins in 2 which is the position of cmd1
//will be check until argv[argc -2] which will be the last cmd before file2
//argv[argc -1] is file2
//free cmd_path at the end of each loop
int check_cmd(int argc, char **argv, char **envp)
{
    int i;
    char    *cmd_name;
    char    *cmd_path;

    i = 2;
    while (i < argc - 1)
    {
        cmd_name = get_only_cmd(argv[i]);
		cmd_path = find_path(cmd_name,envp);
        if (!cmd_path)
        {
            perror("Not path found");
            free(cmd_name);
            return (-1);
        }
        if ((access(cmd_path, X_OK) == - 1))//new
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
    fprintf(stderr, "cmds passed initial check\n");//testing
	return (0);
}

//initial check
//check existence of file1 and file2
//check if file 1 has read permissions
//check if file 2 has write permissions
//check if cmds are executables
//file2 not need ti exit when calling tge program 
//if doesn't exist needs to be created
//O_TRUNC truncates the file, over wrtes the one
//gives it the permissions 0644: rw-r--r--
int	ini_check(int argc, char **argv, char **envp)
{
	//if ((access(argv[1], F_OK) == -1) || (access(argv[argc - 1], F_OK) == -1))//to check if the file2 exist
	if (access(argv[1], F_OK) == - 1)
	{
		perror("At least 1 file doesn't exist");
		return (-1);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror("No read permissions for file1");
		return (-1);
	}
 fprintf(stderr, "File1 passed initial check\n");//testing
 if (check_cmd(argc, argv, envp) != 0)
 {
     perror("Non executable command");
     return (-1);
		}
	return (0);
}
//process for cmd1 (FORK1)
//Function void because it succees or exit to go back to the parent, doesn't return
//*nargv is the new array of arguments needed for execution
//fd_dup is the dup of file1 after the redirection
//pipefd_dup is the dup of pipefd after the redirection 
//pipefd[0] not needed in this process but inherited
//redirect file1 as input of cmd1
//refirect cmd1 to piepfd[1] stdout
//If any redirection fail the fd dups will be close 
//(the original fd are close in the redir functions)
//After all redirections will be done before the execution
//The execution will be done with the duplicated fd
//Need to be found the right arg for execution (nargv) to get in position 0 the cmd file
//If the execution succees pipefd[1] can't manually be closed in the child1 and nargv 
//can't be free, needs to be close in the parent and the child close it automatically
//if fails needs to exit(1) to stop the process and go back to the parent
void child1(int argc, int  *pipefd, char **argv, char **envp, int fd[2])
{
    fprintf(stderr, "\nCHILD1 WILL BEGIN\n\n\n");//testing
    char **nargv;
    int fd_dup;
    int pipefd_dup;
    int child_num;
    
    close_fd(pipefd[0]);
    //close_fd(fd[1]);//NEW
	if ((fd_dup = redir_input(fd[0])) < 0)
    {
        perror("Failed redirection input in child1");
        exit(1);
    }
    fprintf(stderr, "redirection INPUT child1  good\n");//testing
    if ((pipefd_dup = redir_output(pipefd[1])) < 0)
    {
        close_fd (fd_dup);
        perror("Failed redirection OUTPUT in child1");
        exit(1);
    }
    fprintf(stderr, "Redirection output child1  good\n");//testing
    child_num = 1;
    nargv = exec_arg(argc,argv, child_num);
    if (!nargv)
    {
        perror ("Failed to create neww array with arg before execution");
        close_fd(pipefd_dup);
        close_fd(fd_dup);
        exit(1);
    }
    fprintf(stderr, "This is the NEW ARRAY in child1 of arg: %s\n\n\n", *nargv);//testing
    fprintf(stderr, "We are in child1 about to call execution\n");//testing
    execution(nargv, envp);
    perror ("Execution failed in child 1");
    free(nargv);
    close_fd(fd_dup);
    close_fd(pipefd_dup);
    close_fd(fd[1]);//NEW
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    exit (1);
}

//process for cmd2(FORK2)
//pipefd[1] not needed in this process
//If any reirection fails will be close the dup fd opened before
//File2 and pipfd are close in redir functions if that fails
//After all the reirection will be done the execution
//First redir input from pipe to cmd2
//then redirection output from cmd2 to file2
void child2 (int argc, int  *pipefd, char **argv, char **envp, int fd[2])
{
    fprintf(stderr, "\nCHILD2 WILL BEGIN\n\n\n");//testing
    char **nargv;
    int fd_dup;
    int pipefd_dup;
    int child_num;

    close(pipefd[1]);
    close(fd[0]);//NEW
				fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);//new
		  if (fd[1] == - 1)//new
		  {
		    perror ("open output file");//new
				  exit (- 1);//new
				}
    if ((pipefd_dup = redir_input(pipefd[0])) < 0)
    {
        perror("Failed redirection input in child2");
        exit(1);
    }
    fprintf(stderr, "redirection INPUT child2  good\n");//testing
    if ((fd_dup = redir_output(fd[1])) < 0)
    {
        close_fd(pipefd_dup);
        perror ("Failed redirection OUTPUT in child2");
        exit(1);
    }
    fprintf(stderr, "Redirection OUTPUT cmd2 file2 good\n");//testing
    child_num = 2;
    nargv = exec_arg(argc, argv, child_num);
    if (!nargv)
    {
        perror ("Failed to remove first argv called from main");
        close_fd(pipefd_dup);
        close_fd(fd_dup);
        exit (1);
    }
    fprintf(stderr, "This is the NEW ARRAY in child2 of arg: %s\n\n\n", *nargv);//testing
    fprintf(stderr, "We are in child2 about to call execution\n");//testing
    execution(nargv, envp);
    perror ("Execution failed in child2");
    free (nargv);
    close_fd(pipefd_dup);
    close_fd(fd_dup);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    exit(1);
}

//First initial check
//file 1 is argv[1]
//file2 is argv[argc - 1]
//Then open file1 to be used in child1 when redirection input of cmd1
//Then open file2 to be use in child2 in redir cmd2 output
//fd[0] is file1
//fd[1] is file2
int open_fd(int argc, char **argv, char **envp, int fd[2])//check if norminette is happy with this
{
    if (ini_check(argc, argv, envp) < 0)
        return (-1);
    fd[0] = open(argv[1], O_RDONLY);
    if (fd[0] == - 1)
	{
	    perror ("Error opening file1");
		return (-1);
	}
    fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
    {
        perror ("Error opening file2");
        close_fd(fd[0]);
        return (-1);//check if this is valid
    }
    fprintf(stderr, "Successfully opened\n");//testing
    close_fd(fd[1]);
				return (0);
}
//parent function to do the fork() for the child processess
int wait_child(pid_t  pid, int *status)
{
    fprintf(stderr, "parent is about to wait");//testing
    if (waitpid(pid, status, 0) == - 1)
    {
        perror ("Error waiting for child");
        return (-1);
    }
    if (WIFEXITED(*status) && WEXITSTATUS(*status) != 0)
    {
        perror ("Child failed");
        return (-1);
    }
    fprintf(stderr, "Child process %d completed\n", pid);//testing
    return (0);
}

//pid1 is child1 (cmd1)
//pid2 is child2 (cmd2)
//pid == 0 means we are in child process
//pid > 0 means we are in the parent process
//fork() returns -1 if something fails
int parent(int argc, int *pipefd, char **argv, char **envp, int fd[2])
{
    pid_t   pid1;
    pid_t   pid2;
    int status1;
    int status2;

    pid1 = fork();
    if (pid1 == - 1)
    {
        perror ("Fork failed for child1");
        close_fd(fd[0]);//NEW
        fprintf(stderr, "Closed correctly fd[0] which is file1\n");//testing
        close_fd(fd[1]);//NEW
        fprintf(stderr, "Closed correctly fd[1] which is file2\n");//testing
        close_fd(pipefd[0]);//NEW
        fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
        close_fd(pipefd[1]);//NEW
        fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
        return (-1);
    }
    else if (pid1 == 0)
        child1(argc, pipefd, argv, envp, fd);
    pid2 = fork();
    if (pid2 == -1)
    {
        perror ("Fork failed for child2");
        close_fd(fd[0]);//NEW
        fprintf(stderr, "Closed correctly fd[0] which is file1\n");//testing
        close_fd(fd[1]);//NEW
        fprintf(stderr, "Closed correctly fd[1] which is file2\n");//testing
        close_fd(pipefd[0]);//NEW
        fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
        close_fd(pipefd[1]);//NEW
        fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
        wait_child(pid1, &status1);
        return (-1);
    }
    else if (pid2 == 0)
        child2(argc, pipefd, argv, envp, fd);
    fprintf(stderr, "We will close in the parent all the fd opened and after forks\n");//testing
    close_fd(fd[0]);
    fprintf(stderr, "Closed correctly fd[0] which is file1\n");//testing
    close_fd(fd[1]);
    fprintf(stderr, "Closed correctly fd[1] which is file2\n");//testing
    close_fd(pipefd[0]);
    fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
    close_fd(pipefd[1]);
    fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
    if (wait_child(pid1, &status1) == - 1)
    {
        perror ("error waiting child1");
        return (-1);
    }
    fprintf(stderr, "Child1 finished now we are in the parent about to begin child2\n");//testing
    if (wait_child(pid2, &status2) == - 1)
    {
        perror ("Error waiting child2");
        return (-1);
    }
    fprintf(stderr, "We are again in the parent after success of child2\n");//testing
    return (0);
}

//mandatory part has to work exactly with 4arg
//pipefd[2] Pipe for inter-process communication
//correct order of redirections (this will happen in childs):
//file1 - cmd1, cmd1- pipefd[0], pipefd[1] to cmd2 and cmd2 to file2
//open_fd will do the initial check of all arg and open file1 and file2
//fd[0] is file1
//fd[1] is file2
//at the end closed std fd
int	main(int argc, char **argv, char **envp)
{
    int pipefd[2];//check if norminette is happy with this
    int fd[2];
    
    ft_printf("argc including the program: %d\n", argc);//testing
    if (argc != 5)
        return (ft_printf("include 4 args\n"), 1);
    if (open_fd(argc, argv, envp, fd) == -1)
        return (1);
    if (pipe(pipefd) == - 1)
    {
        perror("pipe failed");
        close_fd(fd[0]);
        close_fd(fd[1]);
        exit (EXIT_FAILURE);
    }
    parent(argc, pipefd, argv, envp, fd);
    fprintf(stderr, "\n\n\nPROGRAM FINISHED\n\n\n");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    return (0);
}