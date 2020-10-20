
## 構造体の例
```c
typedef struct {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;
```

```c
void	*mlx_init()
void *mlx = mlx_init();
```
絶対最初に呼ばないといけないやつ。

```c
void	*mlx_new_window(void* 初期化したmlx, int 画面幅, int 画面高さ, char* window名)
void *mlx_win = mlx_new_window(mlx, 1920, 1080, "test window");
```
のように呼び出して使い、最初の真っ黒ウィンドウを作ってくれる。  

```c
void	*mlx_new_image(void* 初期化したmlx,int 画面幅, int 画面高さ)
void *img = mlx_new_image(mlx, 1920, 1080);
```
新しく描画するための画面を作ってくれる奴。多分

```c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
```
座標x, yにcolor色をいれてくれる。ドット入れを楽にするための自作関数。

```c
int     mlx_put_image_to_window(void* 初期化したmlx, void* 画像を入れるmlx_win, void *新しく作ったimg, int x, int y)
mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
```
実際に作ったimgをmlx_winに入れていく関数。

```c
int		mlx_loop(void *mlx);
```
イベントを受け取るために必要。イベントを待つための無限ループ。

## 大体こんな感じで使う
```c
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//↑ここまで大体は決めうちで使うっぽい。
	my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	//↑画像描画 画面のx = 10, y = 10座標に赤を1pxだけ塗る

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
```
これで(10, 10)に赤いドットが1pxだけ塗られる。
