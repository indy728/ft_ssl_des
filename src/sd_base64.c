/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 23:47:30 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/20 20:26:53 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static void		b64_xput(char **xput, t_bool *n, char **av, int *i)
{
	++*i;
	if (av[*i] && av[*i][0] != '-')
	{
		*xput = ft_strdup(av[*i]);
		*n = 1;
	}
	else
		--*i;
}

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
			b64_xput(&b64->input_path, &b64->i, av, &i);
		else if (av[i][1] == 'o')
			b64_xput(&b64->output_path, &b64->o, av, &i);
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
	*h = '\0';
}

/*
 *	0x30 = 	00110000
 *	0x3C =	00111100
 *
 *
 */

static int	get_len(char *str)
{
	VAR(int, i, 0);
	while (str[i] && str[i] != '=')
		++i;
	return (i);
}

static int	get_new_len(char *str, int len)
{
	VAR(int, i, 0);
	while (str[len + i])
		++i;
	i = (i % 3 ? 3 - i : 0);
	return (len / 4 * 3 + 1 + i);
}

static char	*b64_decode_helper(t_base64 *b64, char *h, int len, int i)
{
	VAR(char*, tmp, (char *)g_base64);
	*h++ = ((int)ft_strlchr(tmp, b64->encoded[i]) << 2) |
		(((int)ft_strlchr(tmp, b64->encoded[i + 1]) & 0x30) >> 4);
	if (i == len - 3)
	{
		*h++ = (((int)ft_strlchr(tmp, b64->encoded[i + 1]) & 0xF) << 4) |
				(((int)ft_strlchr(tmp, b64->encoded[i + 2]) & 0x3C) >> 2);
	}
	return (h);
}

/*
 *	Have to make sure everything is printable here VV
 */

void	sd_base64_decode(t_base64 *b64)
{
	VAR(int, i, 0);
	VAR(int, len, get_len(b64->encoded));
	VAR(char*, tmp, (char *)g_base64);
	b64->decoded = ft_strnew(get_new_len(b64->encoded, len));
	VAR(char*, h, b64->decoded);
	while (i < len - 3)
	{
		*h++ = ((int)ft_strlchr(tmp, b64->encoded[i]) << 2) |
			(((int)ft_strlchr(tmp, b64->encoded[i + 1]) & 0x30) >> 4);
		*h++ = (((int)ft_strlchr(tmp, b64->encoded[i + 1]) & 0xF) << 4) |
				(((int)ft_strlchr(tmp, b64->encoded[i + 2]) & 0x3C) >> 2);
		*h++ = (((int)ft_strlchr(tmp, b64->encoded[i + 2]) & 0x3) << 6) |
				((int)ft_strlchr(tmp, b64->encoded[i + 3]));
		i += 4;
	}
	if (i < len)
		h = b64_decode_helper(b64, h, len, i);
	*h = '\0';
}

void	xcode_from_file(char **string, char *path)
{
	VAR(int, fd, 0);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_printf("FUCK YOU\n");///////////////////
		exit (0) ;//////////////////
	}
	VAR(char*, line, NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (*string)
		   *string = ft_strjoin(ft_strjoin(*string, "\n"), line);////hella memory fuckos
		else
		   *string = ft_strdup(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
}

static int	get_output_fd(char *path)
{
	VAR(int, fd, 1);
	if ((fd = open(path, O_CREAT | O_APPEND)))
	{
		ft_printf("FUCK YOU\n");///////////////////
		exit (0) ;//////////////////
	}
	return (fd);
}

void	sd_base64_output(t_base64 *b64)
{
	VAR(int, fd, 1);
	if (b64->o)
		fd = get_output_fd(b64->output_path);
	ft_putendl_fd(b64->e ? b64->encoded : b64->decoded, fd);
	if (fd > 2)
		close (fd);
}

void	sd_base64(int ac, char **av)
{
	VAR(t_base64*, b64, (t_base64 *)ft_memalloc(sizeof(t_base64)));
	sd_base64_options(b64, ac, av);
	if (b64->e)
	{
		if (!b64->i)
			get_next_line(0, &b64->decoded);
		else
			xcode_from_file(&b64->decoded, b64->input_path);
		sd_base64_encode(b64);
		sd_base64_output(b64);
	}
	else
	{
		if (!b64->i)
			get_next_line(0, &b64->encoded);
		else
			xcode_from_file(&b64->encoded, b64->input_path);
		sd_base64_decode(b64);
		sd_base64_output(b64);
	}
}
