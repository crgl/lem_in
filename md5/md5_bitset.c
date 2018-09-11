/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_bitset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 21:04:21 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/09 21:04:24 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

void	c_bits(unsigned char *output, uint32_t *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	uc_bits(uint32_t *output, unsigned char *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = (uint32_t)input[j]
			| (((uint32_t)input[j + 1]) << 8)
			| (((uint32_t)input[j + 2]) << 16)
			| (((uint32_t)input[j + 3]) << 24);
		i++;
		j += 4;
	}
}

void	beuc_bits(uint32_t *output, unsigned char *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = (uint32_t)input[j] << 24
			| (((uint32_t)input[j + 1]) << 16)
			| (((uint32_t)input[j + 2]) << 8)
			| ((uint32_t)input[j + 3]);
		i++;
		j += 4;
	}
}

void	bec_bits(unsigned char *output, uint32_t *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)((input[i] >> 24) & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 3] = (unsigned char)(input[i] & 0xff);
		i++;
		j += 4;
	}
}
