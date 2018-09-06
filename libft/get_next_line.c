/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 22:40:16 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/18 19:26:18 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_buf(t_fdlist **bufs, int fd)
{
	t_fdlist	*candidate;

	if (*bufs == NULL)
	{
		*bufs = (t_fdlist *)ft_memalloc(sizeof(t_fdlist));
		if (*bufs == NULL)
			return (NULL);
		(*bufs)->fd = fd;
		return (*bufs)->buf;
	}
	candidate = *bufs;
	while (candidate->next)
	{
		if (candidate->fd == fd)
			return (candidate->buf);
		candidate = candidate->next;
	}
	if (candidate->fd == fd)
		return (candidate->buf);
	candidate->next = (t_fdlist *)ft_memalloc(sizeof(t_fdlist));
	if (candidate->next == NULL)
		return (NULL);
	candidate->next->fd = fd;
	return (candidate->next->buf);
}

void	free_buf(t_fdlist **bufs, int fd)
{
	t_fdlist	*tmp1;
	t_fdlist	*tmp2;

	tmp1 = *bufs;
	if ((*bufs)->fd == fd)
	{
		(*bufs) = (*bufs)->next;
		free(tmp1);
		return ;
	}
	while (tmp1->next)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		if (tmp1->fd == fd)
		{
			tmp2->next = tmp1->next;
			free(tmp1);
			return ;
		}
	}
	free(tmp1);
	tmp2->next = NULL;
}

char	*init_buf(t_fdlist **abufs, int fd, int *check)
{
	char	*buf;

	buf = find_buf(abufs, fd);
	if (buf == NULL)
	{
		*check = -1;
		return (NULL);
	}
	if (buf[0] == '\0')
	{
		*check = read(fd, buf, BUFF_SIZE);
		if (*check == -1 || *check == 0)
		{
			free_buf(abufs, fd);
			return (NULL);
		}
		buf[*check] = '\0';
	}
	return (buf);
}

int		add_to_vec(char *buf, t_vec *current)
{
	int	i;
	int	check;

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
			break ;
		i++;
	}
	check = veccat(current, buf, i);
	if (check == -1)
		return (-1);
	if (buf[i] == '\n')
	{
		ft_memmove(buf, buf + i + 1, BUFF_SIZE - i);
		return (1);
	}
	else
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		return (0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_fdlist	*bufs;
	t_vec			*tmp;
	int				check;
	char			*buf;

	buf = init_buf(&bufs, fd, &check);
	if (buf == NULL)
		return (check);
	tmp = vecnew(NULL, BUFF_SIZE);
	if (tmp == NULL)
		return (-1);
	while (!(check = add_to_vec(buf, tmp)))
	{
		check = read(fd, buf, BUFF_SIZE);
		if (check == -1 || check == 0)
		{
			free_buf(&bufs, fd);
			break ;
		}
	}
	check = (check == 0 && tmp->len) ? 1 : check;
	if (check == 1)
		*line = vec2str(tmp);
	vecdel(&tmp);
	return (check);
}
