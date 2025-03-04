#include "pipex.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h> // For O_RDONLY

int main(int argc, char *argv[])
{
	if (argc < 5) // Corrected argument count check
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
        	return 1;
    	}
	(void)argv; //  Placed here, after argument check

    if (access(argv[1], R_OK) == -1) 
    {  // Check input file read access
        perror("access (input file)"); // Print error message
        return 1;
    }

    int infile_fd = open(argv[1], O_RDONLY);
    if (infile_fd == -1)
    {
        perror("open");
        return 1;
    }

    close(infile_fd); // Don't forget to close the file descriptor when done!
    return 0;
}
