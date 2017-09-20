/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 20:09:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/19 23:17:12 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

/*char	*nintencode64(const char *string)
{

    VAR(int, i, 0);
	VAR(int, len, ft_strlen(string));
	VAR(int, elen, (len + (len % 3 ? 3 - len % 3 : 0)) / 3 * 4 + 1);
	VAR(char*,encoded, ft_strnew(elen));
    VAR(char*,p,encoded);
	p = encoded;
    for (i = 0; i < len - 2; i += 3) {
    *p++ = g_base64[(string[i] >> 2) & 0x3F];
    *p++ = g_base64[((string[i] & 0x3) << 4) |
                    ((int) (string[i + 1] & 0xF0) >> 4)];
    *p++ = g_base64[((string[i + 1] & 0xF) << 2) |
                    ((int) (string[i + 2] & 0xC0) >> 6)];
    *p++ = g_base64[string[i + 2] & 0x3F];
    }
	ft_printf("i: %d, len %d, elen: %d\n", i, len, elen);
    if (i < len) {
    *p++ = g_base64[(string[i] >> 2) & 0x3F];
    if (i == (len - 1)) {
        *p++ = g_base64[((string[i] & 0x3) << 4)];
        *p++ = '=';
    }
    else {
        *p++ = g_base64[((string[i] & 0x3) << 4) |
                        ((int) (string[i + 1] & 0xF0) >> 4)];
        *p++ = g_base64[((string[i + 1] & 0xF) << 2)];
    }
    *p++ = '=';
    }

    *p++ = '\0';
    return encoded;
}*/


int		check_commands(char *command)
{
	VAR(int, i, -1);
	while (g_commands[++i])
	{
		if (!ft_strcmp(g_commands[i], command))
			return (i);
	}
	return (-1);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		if (check_commands(av[1]) < 0)
			ft_putendl("ERROR");
		else
			ft_putendl("BEWBS");
	}
	else
		ft_putendl(USAGE);
	return (0);
}
