/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:07:12 by naankour          #+#    #+#             */
/*   Updated: 2024/11/13 12:50:03 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		len_trim;
	char	*trimstr;
	int		k;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_inset(s1[i], set))
		i++;
	while (j > i && ft_inset(s1[j], set))
		j--;
	len_trim = (j - i) + 1;
	trimstr = malloc(len_trim + 1);
	if (!trimstr)
		return (NULL);
	k = 0;
	while (k < len_trim)
	{
		trimstr[k] = s1[i + k];
		k++;
	}
	trimstr[len_trim] = '\0';
	return (trimstr);
}

// int main() {
//     const char *s1 = "\t \n   Hello World!   \n \t ";
//     const char *set = " \t\n\r\v\f";

//     char *trimmed_str = ft_strtrim(s1, set);

//     if (trimmed_str == NULL) {
//         printf("Erreur d'allocation mémoire\n");
//         return 1;
//     }

//     printf("Chaîne trimée : '%s'\n", trimmed_str);

//     free(trimmed_str);

//     return 0;
// }
