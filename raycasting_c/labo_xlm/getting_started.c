#include "minilibx-linux/mlx.h"
#include <stdio.h>

#define X_EVENT_KEY_PRESS		2
#define KEY_ESC			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

int g_player_x = 10;
int g_player_y = 10;

typedef	struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int			main_loop(void *mlx, void *mlx_win)
{
	t_data img;

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	my_mlx_pixel_put(&img, g_player_x, g_player_y, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, g_player_x, g_player_y);
	return (0);
}

int		deal_key(int key_code)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		g_player_y--;
	else if (key_code == KEY_S)
		g_player_y++;
	else if (key_code == KEY_A)
		g_player_x--;
	else if (key_code == KEY_D)
		g_player_x++;
	return (0);
}

int				main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// for (int i = 10; i < 500; i++) {
	// 	// for (int j = 10; j < 300; j++) {
	// 		my_mlx_pixel_put(&img, i, i, 0x00FF0000);
	// 	// }
	// }
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, X_EVENT_KEY_PRESS, 1, &deal_key, mlx);
	mlx_loop_hook(mlx, &main_loop, mlx);
	mlx_loop(mlx);

	return (0);
}
