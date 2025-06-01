/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/01 17:09:06 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

/* X11 Event constants (defined directly to avoid header dependency) */
# define KEY_PRESS 2
# define BUTTON_PRESS 4
# define MOTION_NOTIFY 6
# define DESTROY_NOTIFY 17

/* X11 Event masks (defined directly to avoid header dependency) */
# define KEY_PRESS_MASK 1L
# define BUTTON_PRESS_MASK 4L
# define POINTER_MOTION_MASK 64L
# define STRUCTURE_NOTIFY_MASK 131072L

/* X11 Key codes (defined directly to avoid header dependency) */
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
# define ESC ESC_KEY
# define LEFT LEFT_KEY
# define RIGHT RIGHT_KEY
# define UP UP_KEY
# define DOWN DOWN_KEY
# define ZOOM_IN 4
# define ZOOM_OUT 5

/* Fixed point arithmetic */
# define FIXED_POINT_BITS 16
# define FIXED_POINT_FACTOR (1 << FIXED_POINT_BITS)
# define INT_TO_FIXED(x) ((x) << FIXED_POINT_BITS)
# define FIXED_TO_INT(x) ((x) >> FIXED_POINT_BITS)
# define FIXED_MULTIPLY(x, y) ((((long long)(x)) * (y)) >> FIXED_POINT_BITS)
# define FIXED_DIVIDE(x, y) ((((long long)(x)) << FIXED_POINT_BITS) / (y))

/*
** Complex number structure (using fixed point)
*/
typedef struct s_complex
{
	long	re;
	long	im;
} t_complex;

/*
** Fractal rendering context
*/
typedef struct s_fractal
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	long		zoom;
	long		offset_x;
	long		offset_y;
	int		max_iter;
	int		color_shift;
	int		fractal_type;
	t_complex	julia_c;
	int		mouse_x;
	int		mouse_y;
} t_fractal;

/* Main functions */
void	init_fractal(t_fractal *f, int type);
void	render_fractal(t_fractal *f);
int		main(int argc, char **argv);

/* Fractal calculations */
int		mandelbrot(t_complex c, int max_iter);
int		julia(t_complex z, t_complex c, int max_iter);
int		burning_ship(t_complex c, int max_iter);

/* Event handlers */
int		handle_key(int keycode, t_fractal *f);
int		handle_mouse(int button, int x, int y, t_fractal *f);
int		handle_mouse_move(int x, int y, t_fractal *f);
int		close_window(t_fractal *f);

/* Utils */
void	put_pixel(t_fractal *f, int x, int y, int color);
int		create_rgb(int r, int g, int b);
void	shift_colors(t_fractal *f);
int		ft_strcmp(const char *s1, const char *s2);
long	ft_atof_fixed(const char *str);
void	print_usage(void);

#endif
