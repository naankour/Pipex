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
		if (!line)
		{
			free(line);
			break;
		}
		if (ft_strncmp(line, av[2], ft_strlen(line) - 1) == 0)
		{
			// printf("limiteur trouvé : %s\n", av[2]);
			free(line);
			break;
		}
		// printf("Écriture de la ligne dans fd temp\n");
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	// printf("Fichier temporaire fermé avec succès\n");

	printf("Création des commandes\n");
	pipex->head = create_cmds(ac, av, envp, 3);
	if (!pipex->head)
	{
		printf("Erreur : Impossible de créer les commandes\n");
		ft_error("Error: Failed to create commands\n", NULL, 1);
	}

	pipex->head->infile = open("temp_here_doc", O_RDONLY);
	if (pipex->head->infile < 0)
		perror("Error: Failed to read temporary file");
	// else
	// 	printf("Fichier temporaire ouvert en lecture avec succès\n");

	open_outfile(pipex, pipex->head);
	execute_commands(pipex);

	close(pipex->head->infile);

	if (unlink("temp_here_doc") == -1)
		perror("Error: Failed to delete temp file");

	// if (pipex->head->outfile >= 0)
	// 	close(pipex->head->outfile);
}