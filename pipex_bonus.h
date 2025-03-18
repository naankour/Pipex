/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:19:21 by naankour          #+#    #+#             */
/*   Updated: 2025/03/15 15:19:21 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "library/libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char			**av;
	char			*path;
	pid_t			pid;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	t_cmd	*head;
	int		prev_pipe[2];
	int		next_pipe[2];
	int		file_error;
	int		here_doc;
}					t_pipex;

//ERROR
void	ft_error(char *str, t_cmd *head, int exit_code);
//FREE
void	free_tab(char **tab);
void	free_cmds(t_cmd *head);
//FILES
void	open_infile(t_pipex *pipex, t_cmd *cmd);
void	open_outfile(t_pipex *pipex, t_cmd *cmd);
//COMMANDS
void	first_cmd(t_pipex *pipex, t_cmd *cmd);
void	middle_cmd(t_pipex *pipex, t_cmd *cmd);
void	last_cmd(t_pipex *pipex, t_cmd *cmd);
//PATH
char	*split_path(char **paths, char *cmd);
char	*find_path(char	**envp, char *cmd);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*create_cmds(int ac, char **av, char **envp, int start_index);
int		ft_wait(t_pipex *pipex);
void	execute_commands(t_pipex *pipex);

#endif