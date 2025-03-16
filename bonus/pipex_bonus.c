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

#include "../pipex_bonus.h"

static void	init_pipex(int ac, char **av, char **envp, t_pipex *pipex)
{
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->head = create_cmds(ac, av, envp, 2);
	pipex->file_error = 0;
	pipex->prev_pipe[0] = -1;
	pipex->prev_pipe[1] = -1;
	pipex->next_pipe[0] = -1;
	pipex->next_pipe[1] = -1;
}

void	execute_commands(t_pipex *pipex)
{
	t_cmd	*cmd;

	cmd = pipex->head;
	first_cmd(pipex, cmd);
	cmd = cmd->next;
	pipex->prev_pipe[0] = pipex->next_pipe[0];
	pipex->prev_pipe[1] = pipex->next_pipe[1];
	while (cmd && cmd->next)
	{
		middle_cmd(pipex, cmd);
		close(pipex->prev_pipe[1]);
		pipex->prev_pipe[0] = pipex->next_pipe[0];
		pipex->prev_pipe[1] = pipex->next_pipe[1];
		cmd = cmd->next;
	}
	if (cmd && cmd->next == NULL)
	{
		last_cmd(pipex, cmd);
		close(pipex->prev_pipe[0]);
		close(pipex->prev_pipe[1]);
	}
}

static int	ft_wait(t_pipex *pipex)
{
	t_cmd	*cmd;
	int		status;
	int		exit_status;

	exit_status = 0;
	cmd = pipex->head;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
	if (pipex->file_error)
		exit_status = 1;
	return (exit_status);
}

void	init_pipex_here_doc(int ac, char **av, char **envp, t_pipex *pipex)
{
	char	*line;
	int		temp_fd;

	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->file_error = 0;
	pipex->prev_pipe[0] = -1;
	pipex->prev_pipe[1] = -1;
	pipex->next_pipe[0] = -1;
	pipex->next_pipe[1] = -1;
	pipex->here_doc = 1;
	temp_fd = open("temp_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd < 0)
		ft_error("Error: Failed to create temporary file\n", NULL, 1);
	while (1)
	{
		ft_printf("heredoc>");
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, av[2], ft_strlen(line) - 1) == 0)
		{
			free(line);
			break;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	pipex->head = create_cmds(ac, av, envp, 3);
	if (!pipex->head)
	{
		close(temp_fd);
		unlink("temp_here_doc");
		ft_error("Error: Failed to create commands\n", NULL, 1);
	}
	pipex->head->infile = open("temp_here_doc", O_RDONLY);
	if (pipex->head->infile < 0)
		ft_error("Error: Failed to read temporary file", pipex->head, 1);
	// execute_commands(pipex);
	// close(pipex->head->infile);
	// if (unlink("temp_here_doc") == -1)
	// 	perror("Error: Failed to delete temp file");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	if (ac < 5)
		ft_error("Error: Invalid number of arguments\n", NULL, 1);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			perror("Error : Number of args is invalid\n");
			exit(1);
		}
		init_pipex_here_doc(ac, av, envp, &pipex);
		execute_commands(&pipex);
		close(pipex.head->infile);
		if (unlink("temp_here_doc") == -1)
			perror("Error: Failed to delete temp file");
	}
	else
		init_pipex(ac, av, envp, &pipex);
	execute_commands(&pipex);
	exit_status = ft_wait(&pipex);
	free_cmds(pipex.head);
	return (exit_status);
}

