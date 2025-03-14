/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:10 by naankour          #+#    #+#             */
/*   Updated: 2025/03/12 13:31:10 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = head;
	while (current)
	{
		if (current->av)
		{
			i = 0;
			while (current->av[i])
			{
				free(current->av[i]);
				i++;
			}
		}
		free(current->av);
		if (current->path)
			free(current->path);
		next = current->next;
		free(current);
		current = next;
	}
}

char	*split_path(char **paths, char *cmd)
{
	int		j;
	char	*full_path;
	char	*cmd_path;

	j = 0;
	while (paths[j])
	{
		full_path = ft_strjoin(paths[j], "/");
		if (!full_path)
		{
			free(full_path);
			return (NULL);
		}
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_tab(paths);
			return (cmd_path);
		}
		free(cmd_path);
		j++;
	}
	free_tab(paths);
	return (ft_strdup(cmd));
}

char	*find_path(char	**envp, char *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths)
		return (NULL);
	return (split_path(paths, cmd));
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*lst = new;
}

t_cmd	*create_cmds(int ac, char **av, char **envp)
{
	int		i;
	t_cmd	*head;
	t_cmd	*new_cmd;

	new_cmd = NULL;
	head = NULL;
	i = 2;
	while (i < (ac - 1))
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (NULL);
		new_cmd->av = ft_split(av[i], ' ');
		if (new_cmd->av && new_cmd->av[0])
			new_cmd->path = find_path(envp, new_cmd->av[0]);
		else
			new_cmd->path = NULL;
		new_cmd->next = NULL;
		cmd_add_back(&head, new_cmd);
		i++;
	}
	return (head);
}

void	ft_error(char *str, t_cmd *head, int exit_code)
{
	perror(str);
	if (head)
		free_cmds(head);
	exit(exit_code);
}

void	open_infile(char **av, t_cmd *cmd, t_cmd *head)
{
	cmd->infile = open(av[1], O_RDONLY);
	if (cmd->infile < 0)
	{
		perror(av[1]);
		cmd->infile = open("/dev/null", O_RDONLY);
		if (cmd->infile < 0)
			ft_error("open /dev/null", head, 1);
	}
}

void	first_cmd(char **av, char **envp, t_cmd *cmd, int *next_pipe, t_cmd	*head)
{
	open_infile(av, cmd, head);
	if (pipe(next_pipe) < 0)
		ft_error("pipe", head, 1);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("fork", head, 1);
	else if (cmd->pid == 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		dup2(next_pipe[1], STDOUT_FILENO);
		close(cmd->infile);
		close(next_pipe[0]);
		close(next_pipe[1]);
		if (!cmd->path || !cmd->av || !cmd->av[0])
			ft_error("Invalid command", head, 127);
		execve(cmd->path, cmd->av, envp);
		ft_error("execve", head, 127);
	}
	close(cmd->infile);
	close(next_pipe[1]);
}

void	middle_cmd(char **envp, t_cmd *cmd, int *prev_pipe, int *next_pipe, t_cmd	*head)
{
	if (pipe(next_pipe) < 0)
		ft_error("pipe", head, 1);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("fork", head, 1);
	else if (cmd->pid == 0)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		dup2(next_pipe[1], STDOUT_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		close(next_pipe[1]);
		close(next_pipe[0]);
		printf("aaa\n");
		if (!cmd->path || !cmd->av || !cmd->av[0])
			ft_error("Invalid command", head, 127);
		execve(cmd->path, cmd->av, envp);
		ft_error("execve", head, 127);
	}
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(next_pipe[1]);
}

void	open_outfile(int ac, char **av, t_cmd *cmd, t_cmd *head, int *file_error)
{
	cmd->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile < 0)
	{
		perror(av[ac - 1]);
		cmd->outfile = open("/dev/null", O_WRONLY);
		if (cmd->outfile < 0)
			ft_error("open /dev/null", head, 1);
		*file_error = 1;
	}
}

void	last_cmd(int ac, char **av, char **envp, t_cmd *cmd, int *prev_pipe, t_cmd	*head, int *file_error)
{
	open_outfile(ac, av, cmd, head, file_error);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("fork", head, 1);
	else if (cmd->pid == 0)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		close(cmd->outfile);
		if (!cmd->path || !cmd->av || !cmd->av[0])
			ft_error("Invalid command", head, 127);
		execve(cmd->path, cmd->av, envp);
		ft_error("execve", head, 127);
	}
	close(cmd->outfile);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*head;
	t_cmd	*current;
	int		prev_pipe[2];
	int		next_pipe[2];
	int		status;
	int		exit_status;
	int		cmd_exit_code;
	int		file_error;

	file_error = 0;
	if (ac < 5)
	{
		perror("Error : Number of args is invalid\n");
		exit(1);
	}
	head = create_cmds(ac, av, envp);
	current = head;
	first_cmd(av, envp, current, next_pipe, head);
	current = current->next;
	prev_pipe[0] = next_pipe[0];
	prev_pipe[1] = next_pipe[1];
	while (current && current->next)
	{
		middle_cmd(envp, current, prev_pipe, next_pipe, head);
		close(prev_pipe[1]);
		prev_pipe[0] = next_pipe[0];
		prev_pipe[1] = next_pipe[1];
		current = current->next;
	}
	if (current && current->next == NULL)
	{
		last_cmd(ac, av, envp, current, prev_pipe, head, &file_error);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	cmd_exit_code = 0;
	exit_status = 0;
	current = head;
	while (current)
	{
		if (current->pid > 0)
		{
			waitpid(current->pid, &status, 0);
			if (WIFEXITED(status))
			{
				cmd_exit_code = WEXITSTATUS(status);
				exit_status = cmd_exit_code;
			}
		}
		current = current->next;
	}
	if (file_error)
		exit_status = 1;
	free_cmds(head);
	return (exit_status);
}

// void	print_cmds(t_cmd *cmd)
// {
// 	while(cmd != NULL)
// 	{
// 		ft_printf("\n%s\n", cmd->av[0]);
// 		ft_printf("%s\n", cmd->path);
// 		cmd = cmd->next;
// 	}
// }