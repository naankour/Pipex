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


// void	fork_exec(t_cmd *temp, char **envp)
// {
// 	while (temp)
// 	{
// 		if(fork() == 0)
// 		{
// 			execve(temp->path, temp->av, envp);
// 			perror("execve");
// 			exit(1);
// 		}
// 		waitpid();
// 		temp = temp->next;
// 	}
// 	dup2

// }
void	print_cmds(t_cmd *cmd)
{
	while(cmd != NULL)
	{
		ft_printf("%s\n", cmd->av[0]);
		ft_printf("%s\n", cmd->path);
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*head;
	t_cmd	*current;
	int		is_first = 1;
	int		infile;
	int		prev_pipe[2];
	int		outfile;

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	head = create_cmds(ac, av, envp);
	current = head;
	while (current != NULL)
	{
		if (is_first)
		{
			infile = open("infile.txt", O_RDONLY);
			dup2(prev_pipe[0], STDIN_FILENO);
			close(infile);
			is_first = 0;
		}
		if (current->next == NULL)
		{
			outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
	}
	print_cmds(head);
}
