/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:30:18 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/08 12:30:23 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strings(char const *s, char c)
{
	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			num++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (num);
}

static char	**free_memory(char **ptr, size_t j)
{
	while (j > 0)
		free(ptr[--j]);
	free(ptr);
	return (NULL);
}

static char	*fill_substring(char const *s, size_t start, size_t end)
{
	char	*ptr;
	size_t	len;

	len = end - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}

static char	**fill_all(char const *s, char c, char **ptr)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			ptr[j] = fill_substring(s, start, i);
			if (!ptr[j])
				return (free_memory(ptr, j));
			j++;
		}
		else
			i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = fill_all(s, c, ptr);
	return (ptr);
}
