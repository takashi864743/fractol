/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/01 16:50:30 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** ft_strcmp:
**   Compares two strings.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*
** put_pixel:
**   Draws a pixel at (x, y) with the given color.
*/
void	put_pixel(t_fractal *f, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** create_rgb:
**   Creates an RGB color from r, g, b values.
*/
int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
** shift_colors:
**   Shifts the color palette for psychedelic effects.
*/
void	shift_colors(t_fractal *f)
{
	f->color_shift = (f->color_shift + 10) % 256;
}

static long	parse_decimal(const char *str, int *i)
{
	long	decimal;
	long	factor;

	decimal = 0;
	factor = FIXED_POINT_FACTOR / 10;
	while (str[*i] >= '0' && str[*i] <= '9' && factor > 0)
	{
		decimal += (str[*i] - '0') * factor;
		factor /= 10;
		(*i)++;
	}
	return (decimal);
}

long	ft_atof_fixed(const char *str)
{
	long	result;
	long	sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result = INT_TO_FIXED(result);
	if (str[i] == '.')
	{
		i++;
		result += parse_decimal(str, &i);
	}
	return (result * sign);
}
