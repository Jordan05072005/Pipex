/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:23:23 by jguaglio          #+#    #+#             */
/*   Updated: 2024/10/30 17:23:23 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(char *path_all, char *av, char **envp)
{
	char	**argm;
	char	*path;

	argm = ft_split(av, ' ');
	path = precis_path(path_all, argm[0]);
	if (!path)
	{
		free_split(argm);
		print_error_message("error : path no found\n", 0, 0);
	}
	if (execve(path, argm, envp) == -1)
	{
		print_error_message("error : no execution\n", errno, errno);
		free(path);
		free_split(argm);
	}
	free(path);
	free_split(argm);
}

// Read in pipefd 
void	parent(char **av, char **envp, int *pipefd)
{
	int		fd;
	char	*path;

	path = find_all_path(envp);
	if (!path)
		return ;
	fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
	{
		free(path);
		print_error_message("error : folder not open\n", errno, errno);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	dup2(fd, 1);
	execution(path, av[3], envp);
	close(fd);
}

//Write in pipefd
void	child(char **av, char **envp, int *pipefd)
{
	int		fd;
	char	*path;

	path = find_all_path(envp);
	if (!path)
		return ;
	fd = open(av[1], O_CREAT | O_RDONLY, 0777);
	if (fd == -1)
	{
		free(path);
		print_error_message("error : folder not open\n", errno, errno);
	}
	close(pipefd[0]);
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	execution(path, av[2], envp);
	close(fd);
}

//pipefd -> [0] : R , [1] : W
int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	proc;

	if (ac != 5)
		print_error_message("error : bad number of arguments\n", errno, 2);
	if (pipe(pipefd) == -1)
		print_error_message("errror : tunel not create\n", errno, errno);
	proc = fork();
	if (proc == -1)
		print_error_message("error : processus not create\n", errno, errno);
	if (proc == 0)
		child(av, envp, pipefd);
	else
		parent(av, envp, pipefd);
	exit(0);
}
