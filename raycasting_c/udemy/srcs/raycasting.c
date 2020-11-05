/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:15:33 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/05 14:44:09 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./definitions.h"
#include "../minilibx-linux/mlx.h"

char		*window = NULL;
char		*renderer = NULL;

//全てを初期化
int		initialize_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
	return (TRUE);
}

void	render_map(t_game *game)
{
	draw_rectangles(game);
	draw_lines(game);

	// t_rect_info	rect;
	// int			i;
	// int			j;
	// i = 0;
	// rect.width = TILE_SIZE;
	// rect.height = TILE_SIZE;
	// while (i < ROWS)
	// {
	// 	j = 0;
	// 	while (j < COLS)
	// 	{
	// 		rect.x = j * TILE_SIZE;
	// 		rect.y = i * TILE_SIZE;
	// 		rect.color = g_map[i][j] != 0 ? 0xff : 0;
	// 		render_rectangle(game, &rect);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

t_rect_info	init_rect_info(int x, int y, int width, int height)
{
	t_rect_info	rect_info;

	rect_info.x = x;
	rect_info.y = y;
	rect_info.width = width;
	rect_info.height = height;
	return (rect_info);
}

void	render_player(t_game *game)
{
	t_rect_info	rect;
	
	rect = init_rect_info(g_player.x, g_player.y, 10, 10);
	render_player_rect(game, &rect, 0x00ff00);
}

t_line_info	init_line_info(double x1, double y1, double x2, double y2)
{
	t_line_info	line_info;

	line_info.x1 = x1;
	line_info.y1 = y1;
	line_info.x2 = x2;
	line_info.y2 = y2;
	return (line_info);
}

void	render_rays(t_game *game)
{
	t_line_info line;

	line = init_line_info(
		g_player.x,
		g_player.y,
		g_player.x + cos(g_player.rotation_angle) * 30,
		g_player.y + sin(g_player.rotation_angle) * 30);
	draw_ray(game, &line);

	t_rect_info rect;
	rect = init_rect_info(line.x2, line.y2, 3, 3);
	render_player_rect(game, &rect, 0x00ff000);
}

void	setup(void)
{
	g_player.x = WIDTH / 2;
	g_player.y = HEIGHT / 2;
	g_player.width = 5;
	g_player.height = 5;
	g_player.turn_direction = 0; //-1 if left, +1 if right
	g_player.walk_direction = 0; //-1 if back, +1 if front
	g_player.side_angle = 0;
	g_player.rotation_angle = PI / 2;
	g_player.walk_speed = 3;
	g_player.turn_speed = 10 * (PI / 180);
}

void	destroy_window()
{
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);
// 	SDL_Quit();
}

void	render(t_game *game)
{
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	update(void)
{
	double		move_step;
	double		new_player_x;
	double		new_player_y;

	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
	move_step = g_player.walk_direction * g_player.walk_speed;
	new_player_x = g_player.x + move_step * cos(g_player.rotation_angle + g_player.side_angle);
	new_player_y = g_player.y + move_step * sin(g_player.rotation_angle + g_player.side_angle);
	if (!has_wall_at(new_player_x, new_player_y))
	{
		g_player.x = new_player_x;
		g_player.y = new_player_y;
	}
}

int		main_loop(t_game *game)
{
	if (g_key_flag == TRUE)
	{
		//	描画する
		update();
		render(game);
	}
	g_key_flag = FALSE;
	return (0);
}

int		main(void)
{
	t_game	game;
	g_is_game_running = initialize_window(&game);

	setup(); //initializing put everything global var

	// destroy_window();
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &key_pressed, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 1<<1, &key_released, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	mlx_destroy_image(game.mlx, game.img.img);
	return (0);
}