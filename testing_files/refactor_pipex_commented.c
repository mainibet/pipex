#include "pipex.h"

//needed as a parameter of execve
//strncmp is to compare the first 5 bytes
//the return will be +5 to get it withou :PATH="
//At the end it will return NULl if path is not found (hanlding error)
//Return NULL if is not found
char	*get_path_env(char **envp)
{
	int	i;

    if (!envp)
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
    if (!dir)
    {//tmp
        return (NULL);
    }//tmp
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
		perror ("Dup2 in redir_input");
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
//fd is the one parameter can be pipefd[1] or file2
#include <stdio.h> //testing
int redir_output(int fd)
{
    fprintf(stderr, "Now will begin redir_output to file2\n");//testing
    int fd_dup;
    
    fd_dup = dup2(fd, STDOUT_FILENO);
    if (fd_dup == -1)
    {
        perror ("Dup2 in redir_output");
        close_fd(fd);
        return (1);
    }
    fprintf(stderr, "Successfull redirection\n");//testing
    close_fd(fd);
    return (0);
}
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
        if ((access(cmd_path, X_OK) == - 1))
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
//will be used for child1 and child2
//to call redirections and handle errors in it if needed
int setup_redir(int input_fd, int output_fd, t_fd_dup *dup)//new
{
    int fd_in_dup;
    int fd_out_dup;

    if ((fd_in_dup = redir_input(input_fd)) < 0)
    {
        perror("Failed redir_input");
        return (-1);
    }
    fprintf(stderr, "redirection INPUT good\n");//test
    if((fd_out_dup = redir_output(output_fd)) < 0)
    {
        close_fd(fd_in_dup);
        perror("Failed redirection OUTPUT");
        return (-1);
    }
    fprintf(stderr, "Redirection output good\n");
    dup -> input_dup = fd_in_dup;
    dup -> output_dup = fd_out_dup;
    return 0;
}

//execution process for child1 and child2
void    child_process(t_pipe_data *data, t_initial_fd *fd, int child_num)
{
    char **nargv;
    t_fd_dup    dup;

    if (setup_redir(fd -> input_fd, fd -> output_fd, &dup) != 0)
    exit(1);
    nargv = exec_arg(data -> argc, data -> argv, child_num);
    if (!nargv)
    {
        perror ("nargv before execution");
        close_fd(dup.input_dup);//new
        close_fd(dup.output_dup);//new
        exit(1);
    }
    fprintf(stderr, "This is the NEW ARRAY in child1 of arg: %s\n\n\n", *nargv);//testing
    fprintf(stderr, "We are in child1 about to call execution\n");//testing
    execution(nargv, data -> envp);
    perror ("Execution failed in child 1");
    free(nargv);
    close_fd(dup.input_dup);//new
    close_fd(dup.output_dup);//new
    exit(1);
}

//process for cmd1 (FORK1)
//Function void because it succees or 
//exit to go back to the parent
//pipe_data includes pipefd
void    child1(t_pipe_data *data)
{
    int child_num;
    t_initial_fd    fd;

    child_num = 1;
    fprintf(stderr, "\nCHILD1 WILL BEGIN\n\n\n");//testing
    close_fd(data -> pipefd[0]);
    fd = (t_initial_fd){data->fd_in, data->pipefd[1]};//check norm
    child_process(data, &fd, child_num);
}

//COMMENTS OF THE PREVIOUS VERSION OF CHILD1
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

//struct fd initialized with arg important for child2
//child process called with that struct
//process for cmd2(FORK2)
//pipefd[1] not needed in this process
void    child2(t_pipe_data *data)
{
    int child_num;
    t_initial_fd    fd;
    int fd_out;

    child_num = 2;
    fprintf(stderr, "\nCHILD2 WILL BEGIN\n\n\n");//testing
    close(data -> pipefd[1]);
    close(data -> fd_in);
    fd_out = open(data -> argv[data -> argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == - 1)
	{
	    perror ("open output file");
		exit (- 1);
	}
    fd = (t_initial_fd){data -> pipefd[0], fd_out};
    child_process(data, &fd, child_num);
}
//COMMENTS OF THE PREVIOUS VERSION OF CHILD2

//If any reirection fails will be close the dup fd opened before
//File2 and pipfd are close in redir functions if that fails
//After all the reirection will be done the execution
//First redir input from pipe to cmd2
//then redirection output from cmd2 to file2
//void child2 (int argc, char **argv, char **envp, int  *pipefd, int fd_in)

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

//function to close fd when a fork fails
int fork_error(int fd_in, int *pipefd)
{
    close_fd(fd_in);
    fprintf(stderr, "Closed correctly fd[0] which is file1\n");//testing
    close_fd(pipefd[0]);
    fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
    close_fd(pipefd[1]);
    fprintf(stderr, "Closed correctly pipefd[1]\n");//testing
    return (-1);
}

//pid1 is child1 (cmd1)
//pid2 is child2 (cmd2)
//pid == 0 means we are in child process
//pid > 0 means we are in the parent process
//fork() returns -1 if something fails
int parent(struct s_pipe_data *data)
{
    pid_t   pid1;
    pid_t   pid2;
    int status1;
    int status2;

    pid1 = fork();
    if (pid1 == - 1)
    {
        perror ("Fork failed for child1");
        return (fork_error(data->fd_in, data->pipefd));
    }
    else if (pid1 == 0)
        child1(data);
    pid2 = fork();
    if (pid2 == -1)
    {
        perror ("Fork failed for child2");
        if (wait_child(pid1, &status1) == -1)
            perror("Error waiting child1");
        return (fork_error(data->fd_in, data->pipefd));
    }
    else if (pid2 == 0)
        child2(data);
    fprintf(stderr, "We will close in the parent all the fd opened and after forks\n");//testing
    close_fd(data -> fd_in);
    fprintf(stderr, "Closed correctly fd_in which is file1\n");//testing
    close_fd(data -> pipefd[0]);
    fprintf(stderr, "Closed correctly pipefd[0]\n");//testing
    close_fd(data -> pipefd[1]);
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
//at the end closed std fd
int	main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    int fd_in;
    t_pipe_data data;//check norm
				
    ft_printf("argc including the program: %d\n", argc);//testing
    if (argc != 5)
        return (ft_printf("include 4 args\n"), 1);
    if (ini_check(argc, argv, envp) < 0)
        return (-1);
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == - 1)
    {
        perror ("Error opening file1");
        return (-1);
    }
    if (pipe(pipefd) == - 1)
    {
        perror("pipe failed");
        close_fd(fd_in);
        return (-1);
    }
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    data.pipefd = pipefd;
    data.fd_in = fd_in;
    parent(&data);
    fprintf(stderr, "\n\n\nPROGRAM FINISHED\n\n\n");//testing
    return (0);
}
