
## BUILD DETAILS

NAME 		=		fdf
BONUS 		=		fdf_bonus

CC 			= 		gcc
## -Wall Wextra Werror
FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
GLFW_LIB 	= 		-Lglfw/lib-mingw-w64 -lglfw3dll -lgdi32 -lopengl32
GLEW_LIB	=		-Lglew/lib/Release/Win32 -lglew32 -lm
RM 			=		rm
MAKE		=		mingw32-make

## FOLDER PATH ##
INC_PATH	=		incs
SRC_PATH	=		srcs
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs

GLFW_INC 	= 		glfw/include
GLEW_INC	=		glew/include

## SOURCE LIBRARIES
LIBFT		=		libft.a

## SOURCE FILES ##
SRC_FILES	=		fdf_main.c    						\
					fdf_windows.c						\
					fdf_map_parsing.c					\
					fdf_setup.c							\
					fdf_pixel_utils.c					\
					fdf_add_to_libft.c					\
					fdf_xiaolinwu.c						\
					fdf_xiaolinwu_utils.c				\
					fdf_lb_clipping.c					\
					fdf_lb_utils.c						\
					fdf_key_moves.c						\
					fdf_key_moves_cont.c				\
					fdf_print_utils.c					\
					fdf_render.c						\
					fdf_error_msg.c


SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJS		:=		$(SRCS:%.c=%.o)

INCS		= 		-I$(INC_PATH) -I$(GLFW_INC) -I$(GLEW_INC) -I$(LIB_PATH)/$(LIB_INC_P)
LIBS		=		$(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(GLFW_LIB) $(GLEW_LIB)

all: $(NAME)

$(NAME): message $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(INCS) -o $(NAME) $(LIBS)
	@echo Program $(NAME) ready!!

%.o: %.c
	@$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(LIBFT):
##	@echo Preparing Libft....
##	@$(MAKE) -C $(LIB_PATH)


message:
	@echo Building program....

clean:

fclean: clean

re: fclean all

.PHONY: clean fclean re message bonus

##COLOUR

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
