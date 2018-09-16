/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftssl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 21:26:37 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/13 21:26:43 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSSL_H
# define FTSSL_H

# include "../libft/libft.h"

typedef unsigned char *t_ptr;

typedef	struct	s_md5set
{
	uint32_t		st[4];
	uint32_t		count[2];
	unsigned char	buff[64];
}				t_md5set;

uint32_t		prm_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t		prm_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t		prm_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t		prm_i(uint32_t x, uint32_t y, uint32_t z);
uint32_t		rl(uint32_t x, unsigned int n);

void			uc_bits(uint32_t *output, unsigned char *input,
				unsigned int len);
void			c_bits(unsigned char *output, uint32_t *input,
				unsigned int len);
void			beuc_bits(uint32_t *output, unsigned char *input,
				unsigned int len);
void			bec_bits(unsigned char *output, uint32_t *input,
				unsigned int len);

void			init_md5(t_md5set *set);
void			update_md5(t_md5set *set, unsigned char *in, unsigned int len);
void			end_md5(unsigned char digest[16], t_md5set *set);
void			hash_md5(uint32_t st[4], unsigned char block[64]);
void			round12(uint32_t *st[4], uint32_t x[64]);
void			round34(uint32_t *st[4], uint32_t x[64]);

#endif
