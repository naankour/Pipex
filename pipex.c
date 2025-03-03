/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:21 by naankour          #+#    #+#             */
/*   Updated: 2025/02/27 11:01:21 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc(s1_len + s2_len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len && s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[s1_len + s2_len] = '\0';
	return (new);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big [i + j] == little[j] && little[j] && i + j <= len - 1)
		{
			j++;
		}
		if (little[j] == '\0' )
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
		{
			word++;
		}
		i++;
	}
	return (word);
}

static	size_t	ft_word_len(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char		**arr;
	size_t		i;
	size_t		length;
	size_t		index;

	arr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	index = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			length = ft_word_len(&s[i], c);
			arr[index] = ft_substr(s, i, length);
			index++;
			i = i + length;
		}
	}
	arr[index] = NULL;
	return (arr);
}

char	*find_path(char	**envp, char *cmd)
{
	int	i;
	int	j;
	char	**paths;
	char	*full_path;
	char	*cmd_path;

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

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	outfile;
	int	p[2];
	int	pid1;
	int	pid2;
	char	**cmd1 = NULL;
	char	**cmd2 = NULL;
	char	*cmd1_path = NULL;
	char	*cmd2_path = NULL;

	if (ac != 5)
	{
		perror("Error : Number of args is invalid\n");
		exit(1);
	}
	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror("Error: infile");
		exit(1);
	}
	if (access(av[1], R_OK) != 0)
	{
		printf("Error: infile does not exist.\n");
		exit(1);
	}
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("Error : outfile");
		exit(1);
	}
	if (access(av[4], R_OK) != 0)
	{
		perror("Error: outfile does not exist.\n");
		exit(1);
	}

	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(1);
	}

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid1 == 0)
	{
		cmd1 = ft_split(av[2], ' ');
		if (!cmd1)
			exit(1);
		cmd1_path = find_path(envp, cmd1[0]);
		if (!cmd1_path)
		{
			perror("Command not found");
			exit(1);
		}

		dup2(infile, STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(infile);
		close(outfile);
		close(p[0]);
		close(p[1]);

		execve(cmd1_path, cmd1, envp);
		perror("execve cmd1");
		exit(1);
	}

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid2 == 0)
	{
		cmd2 = ft_split(av[3], ' ');
		if (!cmd2)
			exit(1);
		cmd2_path = find_path(envp, cmd2[0]);
		if (!cmd2_path)
		{
			perror("Command not found");
			exit(1);
		}

		dup2(p[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(infile);
		close(outfile);
		close(p[0]);
		close(p[1]);

		execve(cmd2_path, cmd2, envp);
		perror("execve tr");
		exit(1);
	}

	close(infile);
	close(outfile);
	close(p[0]);
	close(p[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit(1);
}

// int main()
// {
// 	int fd = open("outfile.txt", O_WRONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		exit(1);
// 	}
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	execlp("ls", "ls", "-l", NULL);
// 	perror("execlp");
// 	return (1);
// }

//dup2 pour rediriger la sortie
//dans cet exemple j ecris dans un fichier au lieu d ecrire dans stdout
// int	main()
// {
// 	int	fd;

// 	fd = open("outfile.txt", O_WRONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		exit(1);
// 	}
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	printf("Ce message va dans outfile.text\n");
// 	printf("jecris ici\n");
// 	return (0);
// }

//FORK
// int	p[2];
// int	pid1;
// char inbuf[16];

// char	*str1 = "hello, world #1";
// char	*str2 = "hello, world #2";
// char	*str3 = "hello, world #3";

// int	main ()
// {
// if (pipe(p) < 0)
// {
// 	perror ("pipe");
// 	exit (1);
// }
// pid1 = fork();
// if (pid1 < 0)
// {
// 	perror("fork");
// 	exit (1);
// }
// else if ( pid1 == 0)
// {
// 	close(p[1]);
// 	while (read(p[0], inbuf, 16))
// 	{
// 		printf("Enfant a lu : %s\n", inbuf);
// 	}
// 	close(p[0]);
// 	exit (0);
// }
// else
// {
// 	close(p[0]);
// 	write(p[1], str1, 16);
// 	write(p[1], str2, 16);
// 	write(p[1], str3, 16);
// 	close(p[1]);
// 	waitpid1(pid1, NULL, 0);
// }
// }

//PIPE
// int	main()
// {
// 	char inbuf[16];
// 	int p[2];
// 	int	pid1;

// char	*str1 = "hello, world #1";
// char	*str2 = "hello, world #2";
// char	*str3 = "hello, world #3";

// 	if(pipe(p) < 0)
// 	{
// 			perror("pipe");
// 			exit(1);
// 	}
// 	pid1 = fork();
// 	if (pid1 < 0)
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	else if (pid1 == 0)
// 	{
// 		close(p[1]);
// 		while (read(p[0], inbuf, 16) > 0)
// 		{
// 			printf("Enfant a lu : %s\n", inbuf);
// 		}
// 		close(p[0]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(p[0]);

// 		write(p[1], str1, 16);
// 		write(p[1], str2, 16);
// 		write(p[1], str3, 16);
// 		close(p[1]);
// 		wait(NULL);
// 	}
// 	return(0);
// }


// char	*str1 = "hello, world #1";
// char	*str2 = "hello, world #2";
// char	*str3 = "hello, world #3";

// int	main()
// {
// 	char inbuf[16];
// 	int p[2];
// 	int i;

// 	if(pipe(p) < 0)
// 	{
// 			perror("pipe");
// 			exit(1);
// 	}
// 	write(p[1], str1, 16);
// 	write(p[1], str2, 16);
// 	write(p[1], str3, 16);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		read(p[0], inbuf, 16);
// 		printf("%s\n", inbuf);
// 		i++;
// 	}
// 	close(p[0]);
// 	close(p[1]);
// 	return(0);
// }