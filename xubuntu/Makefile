all :	cub3D

cub3D :
	$(MAKE) -C ./libft
	gcc -I includes -I mlx_linux -I ./libft/includes -L ./libft -c ./srcs/*.c
	gcc -o cub3D -I includes -I mlx_linux *.o ./mlx_linux/libmlx.a ./libft/libft.a -Wall -Wextra -Werror -Ofastest -lm -lbsd -lX11 -lXext -lpthread

clean :
	rm -rf *.o

fclean :
	make clean
	rm -f snapshot_cub3d.bmp
	rm -f cub3D

re :
	make fclean
	make
