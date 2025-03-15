/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:08:22 by naankour          #+#    #+#             */
/*   Updated: 2025/03/04 08:08:22 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error(char *str, t_cmd *head, int exit_code)
{
	perror(str);
	if (head)
		free_cmds(head);
	exit(exit_code);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		i;

	cmd = head;
	while (cmd)
	{
		if (cmd->av)
		{
			i = 0;
			while (cmd->av[i])
			{
				free(cmd->av[i]);
				i++;
			}
			free(cmd->av);
		}
		if (cmd->path)
			free(cmd->path);
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
