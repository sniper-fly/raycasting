#include <stdio.h>
#include "minilibx-linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	//You don't need to understand the 3 values below.
	//After declaration, it will be automatically initialized when passed to mlx_get_data_addr function.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
}				t_mlx;

int	main(void)
{
	t_mlx	*mlx;
	int		count_w;
	int		count_h;
	t_img	img;

	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

	//The reason why I cast to (int *): If I let this as void * type, whenever I refer to the array values, I need to multiply them by 4.
	//Check out keuhdall's github linked in my README for more information.

	count_h = -1;
	while (++count_h < IMG_HEIGHT)
	{
		count_w = -1;
		while (++count_w < IMG_WIDTH)
		{
			if (count_w % 2)
				img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF;
			else
				img.data[count_h * IMG_WIDTH + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}