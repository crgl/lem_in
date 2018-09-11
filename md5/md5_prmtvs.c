/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:55:15 by tdiaz             #+#    #+#             */
/*   Updated: 2018/08/09 16:55:19 by tdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ftssl.h"

uint32_t	prm_f(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) | ((~x) & (z)));
}

uint32_t	prm_g(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (z)) | ((y) & (~z)));
}

uint32_t	prm_h(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x) ^ (y) ^ (z));
}

uint32_t	prm_i(uint32_t x, uint32_t y, uint32_t z)
{
	return ((y) ^ ((x) | (~z)));
}

uint32_t	rl(uint32_t x, unsigned int n)
{
	return ((x) << (n) | ((x) >> (32 - n)));
}
