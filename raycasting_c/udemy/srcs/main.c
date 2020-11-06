/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:15:33 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/06 12:12:19 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./definitions.h"

int		g_map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int		g_key_flag = TRUE;
int		g_is_game_running = FALSE;

//全てを初期化
int		initialize_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
	return (TRUE);
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

void	update(void)
{
	float		move_step;
	float		new_player_x;
	float		new_player_y;

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

	mlx_hook(game.win, X_EVENT_KEY_PRESS, KEY_PRESS_MASK, &key_pressed, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, KEY_RELEASE_MASK, &key_released, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, STRUCTURE_NOTIFY_MASK, &close, &game);
	//focus in イベント（最小化してもう一度画面を戻すとき）が発生したときに再度描画するhookを登録する必要がある. linux vmで要検証。mlx_put_image_to_windowを呼び出して再描画させればよさげ
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	mlx_destroy_image(game.mlx, game.img.img);
	mlx_destroy_window(game.mlx, game.img.img);
	return (0);
}
