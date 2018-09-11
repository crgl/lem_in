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

# include "printf/ft_printf.h"
# include <stdint.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define READ_SIZE 1024

typedef unsigned char *t_ptr;

typedef	struct	s_md5set
{
	uint32_t		st[4];
	uint32_t		count[2];
	unsigned char	buff[64];
}				t_md5set;

typedef struct	s_sha2set
{
	uint32_t		st[8];
	uint32_t		count[2];
	unsigned char	buff[64];
}				t_sha2set;

typedef union	u_state
{
	uint8_t		byte[8];
	uint64_t	lane[25];
}				t_state;

typedef struct	s_sha3set
{
	int		index;
	int		rate;
	int		digestlen;
	t_state	state;
}				t_sha3set;

typedef struct	s_send
{
	void	(*prt)(int argc, char **argv);
	char	*s;
}				t_send;

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

void			md5_dispatch(int argc, char **argv);
void			sha_dispatch(int argc, char **argv);
void			sha3_dispatch(int argc, char **argv);
int				comp(const char *s1, const char *s2);

uint32_t		ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		sigma_0(uint32_t x);
uint32_t		sigma_1(uint32_t x);
uint32_t		sigma_o(uint32_t x);
uint32_t		sigma_i(uint32_t x);
uint32_t		rightshft(uint32_t x, int n);
uint32_t		rotright(uint32_t x, int n);
uint32_t		wordcalc(uint32_t x[16], int i);

void			init_sha256(t_sha2set *set);
void			update_sha256(t_sha2set *set, unsigned char *in,
				unsigned int len);
void			end_sha256(unsigned char digest[32], t_sha2set *set);
void			hash_sha256(uint32_t st[8], unsigned char block[64]);

void			init_sha3(t_sha3set *set);
void			update_sha3(t_sha3set *set, unsigned char *in,
				unsigned int len);
void			end_sha3(unsigned char digest[16], t_sha3set *set);

void			theta(uint64_t *state[25]);
void			rhopi(uint64_t *state[25]);
void			chi(uint64_t *state[25]);
void			iota(uint64_t *state[25], int r);

int				readflmd5(int fd, char *buff, t_md5set *set);
int				readflsha3(int fd, char *buff, t_sha3set *set);
int				readflsha256(int fd, char *buff, t_sha2set *set);

#endif
