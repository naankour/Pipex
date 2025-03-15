/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:14:46 by naankour          #+#    #+#             */
/*   Updated: 2025/03/15 14:14:46 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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
			free_tab(paths);
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
