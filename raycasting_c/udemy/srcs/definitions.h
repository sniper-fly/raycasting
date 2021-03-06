/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:14:37 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/07 12:41:42 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <math.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"

# define TRUE 1
# define FALSE 0

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17 //Exit program key code

# define KEY_PRESS_MASK			1<<0
# define KEY_RELEASE_MASK		1<<1
# define STRUCTURE_NOTIFY_MASK	1<<17

# define KEY_ESC				65307
# define KEY_W					119
# define KEY_A					97
# define KEY_S					115
# define KEY_D					100
# define KEY_LEFT_ARROW			65361
# define KEY_RIGHT_ARROW		65363

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
# define NUM_RAYS WIDTH

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
	float	side_angle; //-1 for left, +1 for right
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}			g_player;

struct			s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}			g_rays[NUM_RAYS];

typedef struct	s_cast_ray_var
{
	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	int		wall_content;
	float	next_touch_x;
	float	next_touch_y;
	float	x_to_check;
	float	y_to_check;
}				t_cast_ray_var;

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
void			draw_ray
				(t_game *game, t_line_info *line);
void			draw_player_rect(t_game *game, t_rect_info *rect, int color);

void			draw_line
				(t_game *game, double x1, double y1, double x2, double y2);
void			draw_lines(t_game *game);
void			draw_rectangle(t_game *game, int x, int y, int color);
void			draw_rectangles(t_game *game);

t_rect_info		init_rect_info(int x, int y, int width, int height);
t_line_info		init_line_info(double x1, double y1, double x2, double y2);

void			render_map(t_game *game);
void			render_player(t_game *game);
void			render_rays(t_game *game);
void			render_map(t_game *game);
void			render(t_game *game);

int				key_pressed(int key_code, t_game *game);
int				key_released(int key_code, t_game *game);
int				close(t_game *game);

int				has_wall_at(float x, float y);

#endif
