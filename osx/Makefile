################################################################################
##############################                 #################################
##############################   PRINT VARS    #################################
##############################                 #################################
################################################################################

GREEN = \033[32m
CYAN = \033[0;36m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m

CLEAR = \033[0m

# Clear line
CLRLINE = \033[K

# Go back to line
BTOLINE = \033[A

################################################################################
##############################                 #################################
##############################   SRCS NAMES    #################################
##############################                 #################################
################################################################################

SRCNAMES += main.c

################################################################################
##############################                 #################################
##############################   SRCS PATHS    #################################
##############################                 #################################
################################################################################

SRCPATH += srcs

################################################################################
##############################                 #################################
##############################    MAIN VARS    #################################
##############################                 #################################
################################################################################

# Name
NAME = exec
SANNAME = sanexec
VALNAME = valexec

# Libraries
LIBFT += libft.a
LIBFTSAN += libftsan.a
LIBFTVAL += libftval.a

# Libraries path
LIBPATH += ./libft

# Compiler
CC = gcc

# Compiler flags
CFLAGS += -Wall -Wextra

CFLAGS += -lmlx -framework OpenGL -framework AppKit -Ofast+++

# sanitize flags
SANITIZE_FLAGS += -fsanitize=address,undefined -ggdb3 #-pedantic

# valgrind flags
VALGRIND_FLAGS += -ggdb3# -pedantic

################################################################################
##############################                 #################################
##############################      RULES      #################################
##############################                 #################################
################################################################################

#--------------------------------- STANDARD -----------------------------------#

$(NAME) :
	$(MAKE) -C ./libft
	$(MAKE) -C ./mlx_osx
	gcc -I includes -I mlx_osx -I ./libft/includes -c ./srcs/*c
	gcc -o cub3D -I includes -I mlx_osx *.o ./mlx_osx/libmlx.a \
	./libft/libft.a -framework OpenGL -framework AppKit -Ofast+++

clean :
	rm -f *.o
	cd $(LIBPATH) && make clean

fclean : clean
	rm -f $(NAME)
	cd $(LIBPATH) && make fclean

re :
	make fclean
	make all

bonus :
	make re

##--------------------------------- SANITIZE -----------------------------------#

san :
	@cd $(LIBPATH) && make san
	@gcc $(CFLAGS) $(SANITIZE_FLAGS) -I./includes/ -I./$(LIBPATH)/includes/ $(LIBPATH)/$(LIBFTSAN) $(SRCPATH)/*c -o $(SANNAME)

sanclean :
	@rm -f *.o

sanfclean : sanclean
	@rm -f $(SANNAME)

sanre :
	@make sanfclean
	@make san

##--------------------------------- VALGRIND -----------------------------------#

val :
	@cd $(LIBPATH) && make val
	@gcc $(CFLAGS) $(VALGRIND_FLAGS) -I./includes/ -I./$(LIBPATH)/includes/ $(LIBPATH)/$(LIBFTVAL) $(SRCPATH)/*c -o $(VALNAME)

valclean :
	@rm -f *.o

valfclean : valclean
	@rm -f $(VALNAME)

valre :
	@make valfclean
	@make val

###---------------------------------- CLEAN -------------------------------------#

.PHONY : all, clean, fclean, re, san, val

