/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:46:09 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/14 14:29:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	**ft_remove_empty_tokens(char **tokens)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		trimmed = ft_strtrim(tokens[i], " \n\r\t");
		free(tokens[i]);
		if (trimmed && *trimmed)
			tokens[j++] = trimmed;
		else
			free(trimmed);
		i++;
	}
	tokens[j] = NULL;
	return (tokens);
}
