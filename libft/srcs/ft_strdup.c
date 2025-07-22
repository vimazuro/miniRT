/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:51 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/08 12:31:55 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;

	len = (ft_strlen(s) + 1);
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, len);
	return (ptr);
}
