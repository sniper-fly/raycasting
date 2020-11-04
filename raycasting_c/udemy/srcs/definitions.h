/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:14:37 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/04 10:23:16 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <math.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17 //Exit program key code

# define KEY_ESC			65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100

# define TILE_SIZE 32
# define ROWS 13
# define COLS 20
# define WIDTH (COLS * TILE_SIZE)
# define HEIGHT (ROWS * TILE_SIZE)
# define MINIMAP_SCALE_FACTOR 1

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

# define FOV_ANGLE (60 * (PI / 180))
# define NUM_RAYS (WIDTH * HEIGHT)

extern int		g_map[ROWS][COLS];
extern int		g_is_game_running;
extern int		g_key_flag;

struct			s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction; //-1 for left, +1 for right
	int		walk_direction; //-1 for back, +1 for front
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}			g_player;

typedef struct	s_img
{
	void	*img;
	int		*data; //imgの本体

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_game;

typedef struct
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_rect_info;

typedef struct
{
	double		x1;
	double		y1;
	double		x2;
	double		y2;
}				t_line_info;

void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			draw_line
				(t_game *game, double x1, double y1, double x2, double y2);
void			draw_ray
				(t_game *game, t_line_info *line);
void			draw_lines(t_game *game);
void			draw_rectangle(t_game *game, int x, int y, int color);
void			draw_rectangles(t_game *game);
void			render_player_rect(t_game *game, t_rect_info *rect, int color);
void			render_line(t_game *game, t_line_info *line, int color);
int				deal_key(int key_code, t_game *game);

#endif
