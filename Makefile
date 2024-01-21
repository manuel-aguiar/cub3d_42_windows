
## BUILD DETAILS

NAME 		=		cub3d

COMP 		= 		gcc -g

FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
GLFW_LIB 	= 		-Lglfw/lib-mingw-w64 -lglfw3dll -lgdi32 -lopengl32
GLEW_LIB	=		-Lglew/lib/Release/Win32 -lglew32 -lm
RM 			=		del
MAKE		=		mingw32-make

GLFW_INC 	= 		glfw/include
GLEW_INC	=		glew/include

## FOLDER PATH ##
INC_PATH	=		incs
SRC_PATH	=		srcs
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs


## SOURCE LIBRARIES
LIBFT		=		libft.a

## SOURCE FOLDERS

DIR_PARSING		=		parsing
DIR_GENERIC_UTILS 	= 	generic_utils
DIR_REN_WIN			=	render_windows
DIR_REN_LIN			=	render_linux
DIR_COMPASS			=	compass
DIR_DRAWING_ALGOS	= 	drawing_algos

## SOURCE FILES ##

INC_FILES	=		cub3d.h				\
					render_windows.h	\
					xiaolin_wu.h		\
					liang_barsky.h		\
					compass.h

SRC_MAIN			=	main.c

SRC_PARSING			=	parsing.c

SRC_GENERIC_UTILS 	= 	ft_split_count_replenish.c

SRC_REN_WIN			=	win_init_window.c		\
						win_keys.c				\
						win_pixels.c			\
						win_render_loop.c		\
						win_fps_counter.c


SRC_COMPASS			=	compass_setup.c				\
						translate_rotate.c			\
						letter_north.c				\
						letter_south.c				\
						letter_south_circle.c		\
						letter_east.c				\
						letter_west.c				\
						win_circle.c				\
						win_square.c				\
						inner_circle.c

SRC_DRAWING_ALGOS	=	circle_line_clipping.c		\
						liang_barsky_clipping.c		\
						liang_barsky_utils.c		\
						xiaolinwu_antialiasing.c	\
						xiaolinwu_utils.c		


## AGGREGATING FILES ##

INCS		:=		$(addprefix $(INC_PATH)/, $(INC_FILES))

SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_MAIN))									\
					$(addprefix $(SRC_PATH)/$(DIR_PARSING)/, $(SRC_PARSING)) 				\
					$(addprefix $(SRC_PATH)/$(DIR_GENERIC_UTILS)/, $(SRC_GENERIC_UTILS))	\
					$(addprefix $(SRC_PATH)/$(DIR_REN_WIN)/, $(SRC_REN_WIN))				\
					$(addprefix $(SRC_PATH)/$(DIR_COMPASS)/, $(SRC_COMPASS))				\
					$(addprefix $(SRC_PATH)/$(DIR_DRAWING_ALGOS)/, $(SRC_DRAWING_ALGOS))

OBJS 		:=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

ALL_INCS	= 		-I$(INC_PATH) -I$(GLFW_INC) -I$(GLEW_INC) -I$(LIB_PATH)/$(LIB_INC_P)
LIBS		=		$(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(GLFW_LIB) $(GLEW_LIB)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) $(ALL_INCS) -o $(NAME) $(LIBS)
	@echo Program $(NAME) ready!!


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@if not exist $(OBJ_PATH) \
	( \
		powershell -File mkdir.ps1 \
	)
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

clean:
	@if exist $(OBJ_PATH) \
	( \
		rmdir /s /q $(OBJ_PATH) \
	)
	@if exist $(LIB_PATH)/$(LIBFT) \
	( \
		$(MAKE) clean -C $(LIB_PATH) \
	)

fclean: clean
	@if exist $(NAME) \
	( \
		del $(NAME) \
	)
	@if exist $(LIB_PATH)/$(LIBFT) \
	( \
		$(MAKE) fclean -C $(LIB_PATH) \
	)

$(LIBFT):
	@$(MAKE) -C $(LIB_PATH)

run: $(NAME)
	@./$(NAME)

re: fclean all

.PHONY: clean fclean re message bonus
