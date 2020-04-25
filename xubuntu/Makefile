all :	cub3d

cub3d :
	$(MAKE) -C ./libft
	gcc -I includes -I mlx_linux -I ./libft/includes -L ./libft -c ./srcs/*.c
	gcc -o cub3d -I includes -I mlx_linux *.o ./mlx_linux/libmlx.a ./libft/libft.a -Wall -Wextra -Werror -Ofastest -lm -lbsd -lX11 -lXext -lpthread

clean :
	rm -rf *.o

fclean :
	make clean
	rm -f snapshot.bmp
	rm -f cub3d

re :
	make fclean
	make
