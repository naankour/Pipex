/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:30:30 by naankour          #+#    #+#             */
/*   Updated: 2025/03/04 08:30:30 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	free_list(t_cmd *head)
// {
// 	t_cmd	*temp;

// 	while (head != NULL)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp);
// 	}
// }

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
	return (cmd);
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
		return (NULL);
	return (split_path(paths, cmd));
}

t_cmd	*create_cmds(int ac, char **av, char **envp)
{
	int	i;
	t_cmd	*new_cmd;
	t_cmd	*head;
	t_cmd	*current;

	new_cmd = NULL;
	head = NULL;
	current = NULL;
	i = 2;
	while(i < (ac - 1))
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (NULL);
		new_cmd->av = ft_split(av[i], ' ');
		new_cmd->path = find_path(envp, new_cmd->av[0]);
		new_cmd->next = NULL;
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		i++;
	}
	return(head);
}

void	print_cmds(t_cmd *cmd)
{
	while(cmd != NULL)
	{
		ft_printf("\n%s\n", cmd->av[0]);
		ft_printf("%s\n", cmd->path);
		cmd = cmd->next;
	}
}

void	first_cmd(char **av, char **envp, t_cmd *cmd, int *next_pipe)
{
	int	infile;

	if ( access(av[1], R_OK) != 0)
	{
		perror(av[1]);
		exit(1);
		// exit(0);
	}
	infile = open(av[1], O_RDONLY);
	if ( infile < 0)
	{
		perror(av[1]);
		exit(1);
	}
	if (pipe(next_pipe) < 0)
	{
		perror("pipe");
		exit(1);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (cmd->pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(next_pipe[1], STDOUT_FILENO);
		close(infile);
		close(next_pipe[0]);
		close(next_pipe[1]);
		if (execve(cmd->path, cmd->av, envp) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	close(infile);
	close(next_pipe[1]);
}

void	middle_cmd(char **av, char **envp, t_cmd *cmd, int *prev_pipe, int *next_pipe)
{
	if (pipe(next_pipe) < 0)
	{
		perror("pipe");
		exit(1);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (cmd->pid == 0)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		dup2(next_pipe[1], STDOUT_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		close(next_pipe[1]);
		close(next_pipe[0]);
		if (execve(cmd->path, cmd->av, envp) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(next_pipe[1]);
}
void	last_cmd(int ac, char **av, char **envp, t_cmd *cmd, int *prev_pipe)
{
	int	outfile;
	int	status;

	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ( outfile < 0)
	{
		perror(av[ac - 1]);
		exit(1);
	}
	cmd->pid = fork();
	if ( access(av[ac - 1], W_OK) != 0)
	{
		perror(av[ac - 1]);
		exit(1);
	}
	if (cmd->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (cmd->pid == 0)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		close(outfile);
		if (execve(cmd->path, cmd->av, envp) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	close(outfile);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
}


int	main(int ac, char **av, char **envp)
{
	t_cmd	*head;
	t_cmd	*current;
	int	prev_pipe[2];
	int	next_pipe[2];
	int status;
	int	exit_status = 0;

	head = create_cmds(ac, av, envp);
	current = head;
	if (ac < 5)
	{
		perror("Error : Number of args is invalid\n");
		exit(1);
	}
	first_cmd(av, envp, current, next_pipe);
	current = current->next;
	prev_pipe[0] = next_pipe[0];
	prev_pipe[1] = next_pipe[1];

	while(current && current->next)
	{
		middle_cmd(av, envp, current, prev_pipe, next_pipe);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		current = current->next;
	}
	if(current->next == NULL)
		last_cmd(ac, av, envp, current, prev_pipe);
	current = head;
	while (current)
	{
		if (current->pid > 0)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status))
			{
				if (current->next == NULL)
					exit_status = WEXITSTATUS(status);
			}
		}
		current = current->next;
	}
	// while (current)
	// {
	// 	waitpid(current->pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 	{
	// 		if (current->next == NULL)
	// 		{
	// 			return WEXITSTATUS(status);
	// 		}
	// 	}
	// 	current = current->next;
	// }
	print_cmds(head);
}

// int	determine_stqus(int	status)
// {
// 	if ((status & 0x7F) == 0)
// 		return ((status >> 8) & 0x7F);
// 	else
// 		return (status & 0x7F);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_cmd	*head;
// 	t_cmd	*current;
// 	int		is_first = 1;
// 	int		infile;
// 	int		prev_pipe[2];
// 	int		new_pipe[2];
// 	int		outfile;
// 	int		pid;

// 	prev_pipe[0] = -1;
// 	prev_pipe[1] = -1;

// 	head = create_cmds(ac, av, envp);
// 	current = head;
// 	while (current != NULL)
// 	{
// 		if (current->next)
// 			pipe(new_pipe);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (is_first)
// 			{
// 				printf("erroor1\n");
// 				infile = open(av[1], O_RDONLY);
// 				dup2(infile, STDIN_FILENO);
// 				dup2(new_pipe[1], STDOUT_FILENO);
// 				close(infile);
// 				close(new_pipe[0]);
// 			}
// 			if (current->next)
// 			{
// 				printf("erroor2\n");
// 				dup2(prev_pipe[0], STDIN_FILENO);
// 				dup2(new_pipe[1], STDOUT_FILENO);
// 				close(prev_pipe[1]);
// 				close(prev_pipe[0]);
// 				close(new_pipe[0]);
// 				close(new_pipe[1]);
// 			}
// 			if ( current->next == NULL)
// 			{
// 				printf("erroor3\n");
// 				outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				dup2(prev_pipe[0], STDIN_FILENO);
// 				dup2(outfile, STDOUT_FILENO);
// 				close(prev_pipe[0]);
// 				close(prev_pipe[1]);
// 				close(outfile);
// 			}
// 			execve(current->path, current->av, envp);
// 			perror("execve");
// 			exit(1);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			if (is_first)
// 				is_first = 0;
// 			close(new_pipe[0]);
// 			close(new_pipe[1]);
// 			close(infile);
// 			close(outfile);
// 		}
// 		if (current->next)
// 		{
// 			prev_pipe[0] = new_pipe[0];
// 			prev_pipe[1] = new_pipe[1];
// 		}
// 		current = current->next;
// 	}
// 	print_cmds(head);
// }
