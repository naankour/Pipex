/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:51:50 by naankour          #+#    #+#             */
/*   Updated: 2025/03/12 16:09:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
// int main()
// {
//     const char s[] = "Coucou tout le monde";
//     char c = ' ';
//     char **result = ft_split(s, c);

//     if (result)
// 		{
//         size_t i = 0;
//         while (result[i] != NULL) {
//             printf("Mot %zu: %s\n", i + 1, result[i]);
//             i++;
//         }

//         for (size_t i = 0; result[i] != NULL; i++) {
//             free(result[i]);
//         }
//         free(result);
//     	}
// 	else
// 	{
// 		printf("Erreur d'allocation mémoire.\n");
// 	}
// }
