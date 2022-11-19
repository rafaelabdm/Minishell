/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:48 by rabustam          #+#    #+#             */
/*   Updated: 2022/08/02 00:03:04 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_line(int fd, char *keep);
static char	*get_line(char *keep);
static char	*save_line(char *keep);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*keep;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = find_line(fd, keep);
	if (!keep)
		return (NULL);
	line = get_line(keep);
	keep = save_line(keep);
	return (line);
}

static char	*find_line(int fd, char *keep)
{
	char	*buf;
	int		bts;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bts = 1;
	while (bts && !ft_strchr_gnl(keep, '\n'))
	{
		bts = read(fd, buf, BUFFER_SIZE);
		if (bts == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bts] = '\0';
		keep = ft_strjoin_gnl(keep, buf);
	}
	free(buf);
	return (keep);
}

static char	*get_line(char *keep)
{
	char	*ret;
	int		nli;

	nli = 0;
	if (!keep[nli])
		return (NULL);
	while (keep[nli] && keep[nli] != '\n')
		nli++;
	ret = malloc(nli + 2);
	if (!ret)
		return (NULL);
	nli = 0;
	while (keep[nli] && keep[nli] != '\n')
	{
		ret[nli] = keep[nli];
		nli++;
	}
	if (keep[nli] == '\n')
	{
		ret[nli] = keep[nli];
		nli++;
	}
	ret[nli] = '\0';
	return (ret);
}

static char	*save_line(char *keep)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	ret = malloc(ft_strlen(keep) - i + 1);
	if (!ret)
		return (NULL);
	i++;
	j = 0;
	while (keep[i])
		ret[j++] = keep[i++];
	ret[j] = '\0';
	free(keep);
	return (ret);
}
