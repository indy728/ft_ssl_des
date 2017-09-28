/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 14:13:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/26 14:26:06 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinew(char *str1, char *str2, int del)
{
	char	*new;

	new = ft_strnew(ft_strlen(str1) + ft_strlen(str2));
	new = ft_strcpy(new, str1);
	new = ft_strcat(new, str2);
	if (del > 1)
		ft_strdel(&str2);
	if (del & 1)
		ft_strdel(&str1);
	return (new);
}
