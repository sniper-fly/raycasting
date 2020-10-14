## cub3Dでやったこと
minilibxのことは下記のサイトがとても参考になります。  
https://harm-smits.github.io/42docs/  

WSL2での開発なので、まずは下記のURLからminilibx linuxのダウンロード。  
https://github.com/42Paris/minilibx-linux  
git clone ~~ して

Requirements に色々書いてあるので、自分が持ってないパッケージは適当にダウンロード  
それでリポジトリのルートでmakeするとライブラリを作ってくれる。  

### getting started


```bash
gcc init_mlx.c ./minilibx-linux/libmlx.a
```
言われた通り上記のようにまずmlx_init()関数を書いたmainを実行するも
```
./minilibx-linux/libmlx.a(mlx_init.o): In function `mlx_int_deal_shm':
mlx_init.c:(.text+0x2c): undefined reference to `XShmQueryVersion'
mlx_init.c:(.text+0x11c): undefined reference to `XShmPixmapFormat'
./minilibx-linux/libmlx.a(mlx_init.o): In function `mlx_init':
mlx_init.c:(.text+0x14f): undefined reference to `XOpenDisplay'
mlx_init.c:(.text+0x1ca): undefined reference to `XInternAtom'
mlx_init.c:(.text+0x2ee): undefined reference to `XCreateColormap'
./minilibx-linux/libmlx.a(mlx_int_get_visual.o): In function `mlx_int_get_visual':
mlx_int_get_visual.c:(.text+0x61): undefined reference to `XGetVisualInfo'
collect2: error: ld returned 1 exit status
```
のようなエラーに遭遇。

https://askubuntu.com/questions/226918/undefined-reference-to-xshmqueryversion  
このページを参考に、
```bash
gcc init_mlx.c ./minilibx-linux/libmlx.a -lXext -lX11
```
と書き直すと無事コンパイルできました。

### どうやってWSLで画面描画するのか
まず、XmingかVcXsrvをダウンロードします。（筆者はVcXsrv）  

42docsサイトのチュートリアルは一旦置いといて、  
テスト的にxeyesというプログラムを起動して、画面描画を試しましょう。  
https://astherier.com/blog/2020/08/run-gui-apps-on-wsl2/#toc_id_4
このサイトを参考にすれば同じように動くはずです。  

しかし、
 'Error: Can't open display:  
 というエラーが表示されてしまいます。  
https://scrapbox.io/42tokyo-42cursus/Windows%E3%81%A7minilibx%E3%82%92%E5%88%A9%E7%94%A8%E3%81%99%E3%82%8B%E9%9A%9B%E3%81%AE%E6%B3%A8%E6%84%8F%E7%82%B9(X_window%E3%82%B5%E3%83%BC%E3%83%90%E3%83%BC%E3%81%AE%E8%A8%AD%E5%AE%9A)  
このscrapboxがとても参考になりました。

これでも動かなかったので、受信の規則、VcXsrv windows xserverで'操作'が'ブロック'になっている規則があったので、  
プロパティを開いて許可に変更したら通信ができ、無事xeyesを動かすことができました。
