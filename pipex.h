/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:55:53 by naankour          #+#    #+#             */
/*   Updated: 2025/03/04 07:55:53 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "library/libft/libft.h"
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char			**av;
	char			*path;
	pid_t			pid;
	struct	s_cmd	*next;
}					t_cmd;

void	free_tab(char **tab);
void	print_cmds(t_cmd *cmd);
char	*split_path(char **paths, char *cmd);
char	*find_path(char	**envp, char *cmd);

#endif