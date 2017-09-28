/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 20:09:15 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/26 21:20:48 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

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
		VAR(int, cmd, check_commands(av[1]));
		if (cmd < 0)
			ft_putendl("ERROR");
		else if (cmd == 0)
			sd_base64(ac, av);
	}
	else
		ft_putendl(USAGE);
	return (0);
}
