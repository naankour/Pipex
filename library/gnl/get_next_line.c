/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:46:54 by naankour          #+#    #+#             */
/*   Updated: 2025/02/11 16:46:39 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buffer, char *temp)
{
	int	r;

	while (!(ft_strchr_2(buffer, '\n')))
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r <= 0)
		{
			if (r == 0)
				break ;
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		temp[r] = '\0';
		buffer = ft_strjoin_2(buffer, temp);
		if (!buffer)
		{
			free (temp);
			return (NULL);
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(temp);
		free(buffer);
		return (NULL);
	}
	buffer = ft_read(fd, buffer, temp);
	free (temp);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_strdup_2(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}

// int	main (void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("testgnl.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("tu sais meme pas ouvrir un fichier la honte");
// 		return (0);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
