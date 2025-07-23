/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:51:41 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/08 12:51:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	step;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dst)
		return (size + len_src);
	else
	{
		i = 0;
		step = (size - len_dst - 1);
		while (src[i] && step > 0)
		{
			dst[len_dst + i] = src[i];
			i++;
			step--;
		}
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}
