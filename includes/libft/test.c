/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 19:55:40 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/26 22:06:09 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	int fd = open("Makefile", O_RDONLY);
	char *new = ft_strnew(1);
	if (!get_all_bytes(fd, &new))
		ft_printf("%s", new);
	ft_strdel(&new);
	close(fd);
}
