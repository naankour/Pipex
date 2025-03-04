/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:21 by naankour          #+#    #+#             */
/*   Updated: 2025/02/27 11:01:21 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*split_path(char **paths, char *cmd)
{
	int	j;
	char	*full_path;
	char	*cmd_path;

	j = 0;
	while (paths[j])
	{
		full_path = ft_strjoin( paths[j], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_tab(paths);
			return (cmd_path);
		}
		free (cmd_path);
		j++;
	}
	free_tab(paths);
	return (NULL);
}

char	*find_path(char	**envp, char *cmd)
{
	int	i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	if (!paths)
		ft_printf("Error : Environment hs no value\n");
		exit (1);
	return (split_path(paths, cmd));
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	outfile;
	int	p[2];
	int	pid1;
	int	pid2;
	char	**cmd1 = NULL;
	char	**cmd2 = NULL;
	char	*cmd1_path = NULL;
	char	*cmd2_path = NULL;

	if (ac != 5)
	{
		perror("Error : Number of args is invalid\n");
		exit(1);
	}
	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror("Error: infile");
		exit(1);
	}
	if (access(av[1], R_OK) != 0)
	{
		printf("Error: infile does not exist.\n");
		exit(1);
	}
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("Error : outfile");
		exit(1);
	}
	if (access(av[4], R_OK) != 0)
	{
		perror("Error: outfile does not exist.\n");
		exit(1);
	}
	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid1 == 0)
	{
		cmd1 = ft_split(av[2], ' ');
		if (!cmd1)
			exit(1);
		cmd1_path = find_path(envp, cmd1[0]);
		if (!cmd1_path)
		{
			perror("Command not found");
			exit(1);
		}
		dup2(infile, STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(infile);
		close(outfile);
		close(p[0]);
		close(p[1]);
		execve(cmd1_path, cmd1, envp);
		perror("execve cmd1");
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid2 == 0)
	{
		cmd2 = ft_split(av[3], ' ');
		if (!cmd2)
			exit(1);
		cmd2_path = find_path(envp, cmd2[0]);
		if (!cmd2_path)
		{
			perror("Command not found");
			exit(1);
		}
		dup2(p[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(infile);
		close(outfile);
		close(p[0]);
		close(p[1]);

		execve(cmd2_path, cmd2, envp);
		perror("execve tr");
		exit(1);
	}
	close(infile);
	close(outfile);
	close(p[0]);
	close(p[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit(1);
}
