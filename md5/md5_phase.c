/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_phase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 21:14:46 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/09 21:14:50 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

static unsigned char g_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void	init_md5(t_md5set *set)
{
	set->count[0] = 0;
	set->count[1] = 0;
	set->st[0] = 0x67452301;
	set->st[1] = 0xefcdab89;
	set->st[2] = 0x98badcfe;
	set->st[3] = 0x10325476;
}

void	update_md5(t_md5set *set, unsigned char *in, unsigned int len)
{
	unsigned int index;
	unsigned int sublen;
	unsigned int i;

	index = (unsigned int)((set->count[0] >> 3) & 0x3f);
	if ((set->count[0] += (uint32_t)len << 3) < ((uint32_t)len << 3))
		set->count[1]++;
	set->count[1] += ((uint32_t)len >> 29);
	sublen = 64 - index;
	if (len >= sublen)
	{
		ft_memcpy((t_ptr)&set->buff[index], (t_ptr)in, sublen);
		hash_md5(set->st, set->buff);
		i = sublen;
		while (i + 63 < len)
		{
			hash_md5(set->st, &in[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((t_ptr)&set->buff[index], (t_ptr)&in[i], len - i);
}

void	end_md5(unsigned char digest[16], t_md5set *set)
{
	unsigned char	bits[8];
	unsigned int	index;
	unsigned int	padlen;

	c_bits(bits, set->count, 8);
	index = (unsigned int)((set->count[0] >> 3) & 0x3f);
	padlen = (index < 56) ? (56 - index) : (120 - index);
	update_md5(set, g_padding, padlen);
	update_md5(set, bits, 8);
	c_bits(digest, set->st, 16);
	ft_memset((t_ptr)set, 0, sizeof(*set));
}

void	hash_md5(uint32_t st[4], unsigned char block[64])
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	x[16];

	uc_bits(x, block, 64);
	a = st[0];
	b = st[1];
	c = st[2];
	d = st[3];
	round12(&st, x);
	round34(&st, x);
	st[0] += a;
	st[1] += b;
	st[2] += c;
	st[3] += d;
	ft_memset((unsigned char *)x, 0, sizeof(x));
}
