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

void	create_cmds(int ac, char **av, char **envp)
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
			return ;
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
int	main(int ac, char **av, char **envp)
{

}
