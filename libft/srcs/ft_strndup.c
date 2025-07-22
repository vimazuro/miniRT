/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:34:24 by vimazuro          #+#    #+#             */
/*   Updated: 2025/05/21 14:12:44 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*copy;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str[i] && i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
