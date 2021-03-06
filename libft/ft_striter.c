/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:18:18 by lschambe          #+#    #+#             */
/*   Updated: 2018/11/30 11:58:45 by lschambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int i;
	int k;

	if (s && f)
	{
		i = 0;
		k = 0;
		while (s[i] != '\0')
			i++;
		while (k < i)
		{
			f(s + k);
			k++;
		}
	}
}
