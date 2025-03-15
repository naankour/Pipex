/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:17:50 by naankour          #+#    #+#             */
/*   Updated: 2025/03/15 14:17:50 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	first_cmd(t_pipex *pipex, t_cmd *cmd)
{
	open_infile(pipex, cmd);
	if (pipe(pipex->next_pipe) < 0)
		ft_error("pipe", pipex->head, 1);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("fork", pipex->head, 1);
	else if (cmd->pid == 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		dup2(pipex->next_pipe[1], STDOUT_FILENO);
		close(cmd->infile);
		close(pipex->next_pipe[0]);
		close(pipex->next_pipe[1]);
		if (!cmd->path || !cmd->av || !cmd->av[0])
			ft_error("Invalid command", pipex->head, 127);
		execve(cmd->path, cmd->av, pipex->envp);
		ft_error("execve", pipex->head, 127);
	}
	close(cmd->infile);
	close(pipex->next_pipe[1]);
}

void	last_cmd(t_pipex *pipex, t_cmd *cmd)
{
	open_outfile(pipex, cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		ft_error("fork", pipex->head, 1);
	else if (cmd->pid == 0)
	{
		dup2(pipex->prev_pipe[0], STDIN_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
		close(pipex->prev_pipe[0]);
		close(pipex->prev_pipe[1]);
		close(cmd->outfile);
		if (!cmd->path || !cmd->av || !cmd->av[0])
			ft_error("Invalid command", pipex->head, 127);
		execve(cmd->path, cmd->av, pipex->envp);
		ft_error("execve", pipex->head, 127);
	}
	close(cmd->outfile);
	close(pipex->prev_pipe[0]);
	close(pipex->prev_pipe[1]);
}
