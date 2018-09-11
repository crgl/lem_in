/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:45:58 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/10 16:46:08 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

int		ind(char *s, int x)
{
	t_md5set		set;
	unsigned char	digest[16];
	unsigned int	len;

	len = ft_strlen(s);
	init_md5(&set);
	update_md5(&set, (t_ptr)s, len);
	end_md5(digest, &set);
	return((digest[0] * 256 + digest[15]) % x);
}
