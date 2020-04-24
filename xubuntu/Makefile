all :
	$(MAKE) -C ./libft
	gcc -I includes -I mlx_linux -I ./libft/includes -L ./libft -c ./srcs/*.c
	gcc -o exec -I includes -I mlx_linux *.o ./mlx_linux/libmlx.a ./libft/libft.a -Wall -Wextra -Werror -Ofastest -lm -lbsd -lX11 -lXext -lpthread

clean :
	rm -rf *.o

fclean :
	make clean
	rm -f snapshot.bmp
	rm -f exec

re :
	make fclean
	make
