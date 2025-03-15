/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:09:27 by naankour          #+#    #+#             */
/*   Updated: 2025/03/15 14:09:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_infile(t_pipex *pipex, t_cmd *cmd)
{
	cmd->infile = open(pipex->av[1], O_RDONLY);
	if (cmd->infile < 0)
	{
		perror(pipex->av[1]);
		cmd->infile = open("/dev/null", O_RDONLY);
		if (cmd->infile < 0)
			ft_error("open /dev/null", pipex->head, 1);
	}
}

void	open_outfile(t_pipex *pipex, t_cmd *cmd)
{
	cmd->outfile = open(pipex->av[pipex->ac - 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile < 0)
	{
		perror(pipex->av[pipex->ac - 1]);
		cmd->outfile = open("/dev/null", O_WRONLY);
		if (cmd->outfile < 0)
			ft_error("open /dev/null", pipex->head, 1);
		pipex->file_error = 1;
	}
}
