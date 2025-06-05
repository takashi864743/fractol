/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/05 15:28:34 by asaitakashi      ###   ########.fr       */
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
void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
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
** ft_atof:
**   Converts a string to double.
*/
double	ft_atof(char *str)
{
	double	result;
	double	sign;
	double	decimal;
	int		i;

	result = 0.0;
	sign = 1.0;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		decimal = 0.1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i] - '0') * decimal;
			decimal /= 10.0;
			i++;
		}
	}
	return (result * sign);
}

/*
** print_usage:
**   Prints usage information.
*/
void	print_usage(void)
{
	write(1, "Usage: ./fractol [mandelbrot|julia|burning_ship]\n", 50);
	write(1, "Controls:\n", 10);
	write(1, "  ESC: Exit\n", 11);
	write(1, "  Arrow keys: Move\n", 18);
	write(1, "  Mouse wheel: Zoom\n", 20);
	write(1, "  C: Shift colors\n", 17);
	write(1, "  R: Reset view\n", 15);
}
