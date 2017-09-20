/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:59:36 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 01:09:42 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"

# define USAGE "usage: ft_ssl <command> [-e | -d] [-i <path>] [-o <path]"

# define KMDB(x) ft_printf("%s\n", x)

static const char g_base64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char *g_commands[5] = {"base64", "des", "des-ecb", "des-cbc", NULL};

typedef struct		s_base64
{
	char			*decoded;
	char			*encoded;
	t_bool			e;
	t_bool			d;
	t_bool			i;
	char			*input_path;
	t_bool			o;
	char			*output_path;
}					t_base64;

void				sd_base64(int ac, char **av);
#endif
