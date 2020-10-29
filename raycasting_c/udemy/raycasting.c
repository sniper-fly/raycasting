#include <stdio.h>
#include "./minilibx-linux/mlx.h"
#include <math.h>

//ヘッダー　定数ファイルを作って入れておくのが良い
#define TRUE 1
#define FALSE 0

# define TILE_SIZE 32
# define ROWS 13
# define COLS 20
# define WIDTH (COLS * TILE_SIZE)
# define HEIGHT (ROWS * TILE_SIZE)
# define MINIMAP_SCALE_FACTOR 1

# define PI 3.14159265
# define TWO_PI 6.28318530

#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS WIDTH * HEIGHT

const int g_map[ROWS][COLS] = {
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

struct Player
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction; //-1 for left, +1 for right
	int walk_direction; //-1 for back, +1 for front
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} player;

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
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}				t_rect_info;


int			is_game_running = FALSE;
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
	int		*dst;

	dst = game->img.data + (y * game->img.size_l + x * game->img.bpp / (sizeof(int) * 8));
	*dst = color;
}

void	render_rectangle(t_game *game, t_rect_info *rect)
{
	int	x_end;
	int y_end;
	int y_tmp;

	x_end = rect->x + rect->width;
	y_end = rect->y + rect->height;
	y_tmp = rect->y;
	while (rect->x < x_end)
	{
		rect->y = y_tmp;
		while (rect->y <= y_end)
		{
			my_mlx_pixel_put(game, rect->x, rect->y, rect->color);
			rect->y++;
		}
		rect->x++;
	}
}

void	render_map(t_game *game)
{
	t_rect_info	rect;
	int			i;
	int			j;

	i = 0;
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			rect.x = j * TILE_SIZE;
			rect.y = i * TILE_SIZE;
			rect.color = g_map[i][j] != 0 ? 0xff : 0;
			render_rectangle(game, &rect);
			j++;
		}
		i++;
	}

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
	// render_player();
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int		main(void)
{
	t_game	game;
	is_game_running = initialize_window(&game);

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

	while (is_game_running)
	{
		// process_input();
		// update();
		render(&game);
	}

	// destroy_window();
	mlx_loop(game.mlx);
	return (0);
}