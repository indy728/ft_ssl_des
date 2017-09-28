/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 21:51:21 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/26 22:24:20 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_all_bytes(int const fd, char **new)
{
	char	buff[BUFF_SIZE + 1];
	int		b;

	if (fd < 0 || fd > MAX_FD)
		return (-1);
	if (!*new)
		*new = ft_strnew(1);
	while ((b = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[b] = '\0';
		*new = ft_strjoinew(*new, buff, 1);
	}
	return (b == 0 ? 1 : 0);
}
