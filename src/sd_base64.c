/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 23:47:30 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 01:34:32 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	sd_base64_options(t_base64 *b64, int ac, char **av)
{
	VAR(int, i, 2);
	while (i < ac && av[i][0] == '-')
	{
		if (av[i][1] == 'e')
			b64->e = 1;
		else if (av[i][1] == 'd')
			b64->d = 1;
		else if (av[i][1] == 'i')
			b64->i = 1;
		else if (av[i][1] == 'o')
			b64->o = 1;
		++i;
	}
	b64->e = !(b64->e + b64->d) ? 1 : b64->e;
}

/*
 *	0x3 =	00000011
 *	0xF =	00001111
 *	0x3F =	00111111
 *	0xC0 =	11000000
 *	0xF0 =	11110000
 */


static char	*b64_encode_helper(t_base64 *b64, char *h, int len, int i)
{
	*h++ = g_base64[(b64->decoded[i] >> 2) & 0x3F];
	*h++ = g_base64[((b64->decoded[i] & 0x3) << 4) |
		((b64->decoded[i + 1] & 0xF0) >> 4)];
	if (i == len - 2)
	{
		*h++ = g_base64[((b64->decoded[i + 1] & 0xF) << 2) |
			((b64->decoded[i + 2] & 0xC0) >> 6)];
	}
	else
		*h++ = '=';
	*h++ = '=';
	return (h);
}

void	sd_base64_encode(t_base64 *b64)
{
	VAR(int, i, 0);
	VAR(int, len, ft_strlen(b64->decoded));
	b64->encoded = ft_strnew((len + (len % 3 ? 3 - len : 0)) / 3 * 4 + 1);
	VAR(char*, h, b64->encoded);
	while (i < len - 2)
	{
		*h++ = g_base64[(b64->decoded[i] >> 2) & 0x3F];
		*h++ = g_base64[((b64->decoded[i] & 0x3) << 4) |
			((b64->decoded[i + 1] & 0xF0) >> 4)];
		*h++ = g_base64[((b64->decoded[i + 1] & 0xF) << 2) |
			((b64->decoded[i + 2] & 0xC0) >> 6)];
		*h++ = g_base64[(b64->decoded[i + 2] & 0x3F)];
		i += 3;
	}
	if (i < len)
		h = b64_encode_helper(b64, h, len, i);
	*h++ = '\0';
}

void	sd_base64(int ac, char **av)
{
	VAR(t_base64*, b64, (t_base64 *)ft_memalloc(sizeof(t_base64)));
	sd_base64_options(b64, ac, av);
	if (b64->e)
	{
		get_next_line(0, &b64->decoded);
		sd_base64_encode(b64);
		ft_putendl(b64->encoded);
	}
}
