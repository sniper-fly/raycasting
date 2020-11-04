/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:15:33 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/04 10:32:37 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

	line = init_line_info(g_player.x, g_player.y, 32, 32);
	draw_ray(game, &line);
}

void	setup(void)
{
	g_player.x = WIDTH / 2;
	g_player.y = HEIGHT / 2;
	g_player.width = 5;
	g_player.height = 5;
	g_player.turn_direction = 0;
	g_player.walk_direction = 0;
	g_player.rotation_angle = PI / 2;
	g_player.walk_speed = 100;
	g_player.turn_speed = 45 * (PI / 180);
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

int		main_loop(t_game *game)
{
	if (g_key_flag == TRUE)
	{
		//	描画する
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
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}