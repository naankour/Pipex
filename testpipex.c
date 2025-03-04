/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:01:12 by naankour          #+#    #+#             */
/*   Updated: 2025/03/04 08:01:12 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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