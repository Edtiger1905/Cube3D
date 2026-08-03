/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:05:51 by epandele          #+#    #+#             */
/*   Updated: 2026/08/03 14:19:13 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
