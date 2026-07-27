/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:05:51 by epandele          #+#    #+#             */
/*   Updated: 2024/12/30 12:07:06 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*castd;
	unsigned char	*casts;

	if (!dst && !src)
		return (NULL);
	castd = (unsigned char *) dst;
	casts = (unsigned char *) src;
	while (n > 0)
	{
		*castd = *casts;
		castd++;
		casts++;
		n--;
	}
	return (dst);
}
