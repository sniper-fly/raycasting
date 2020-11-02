#include <stdio.h>
#include "./definitions.h"
#include "./minilibx-linux/mlx.h"

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

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	game->img.data[y * WIDTH + x] = color;
	// int		*dst;
	// dst = game->img.data + (y * game->img.size_l + x * game->img.bpp / (sizeof(int) * 8));
	// *dst = color;
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

void	render_player(t_game *game)
{
	t_rect_info rect;
	
	rect.x = g_player_x;
	rect.y = g_player_y;
	rect.width = 10;
	rect.height = 10;
	rect.color = 0x00ff00;
	render_rectangle(game, &rect);
}

void	setup(void)
{
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.width = 5;
	player.height = 5;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = PI / 2;
	player.walk_speed = 100;
	player.turn_speed = 45 * (PI / 180);
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
	// render_rays();
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int		main(void)
{
	t_game	game;
	g_is_game_running = initialize_window(&game);

	setup(); //initializing put everything global var

	// int i = 0;
	// for (; i < WIDTH / 2; i++) {
	// 	my_mlx_pixel_put(&game, i, 10, 0xff);
	// }
	// printf("former%d\n", i);
	// for (; i < WIDTH; i++) {
	// 	my_mlx_pixel_put(&game, i, 10, 0xff00);
	// }
	// printf("later%d", i);
	// mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);

	while (g_is_game_running)
	{
		// process_input();
		// update();
		render(&game);
	}

	// destroy_window();
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_loop(game.mlx);
	return (0);
}