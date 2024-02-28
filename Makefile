
## BUILD DETAILS

NAME 		=		cub3d

COMP 		= 		gcc -O3

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

DIR_GAME			=	game
DIR_PARSING			=	parsing
DIR_GENERIC_UTILS 	= 	generic_utils
DIR_REN_WIN			=	render_windows
DIR_COMPASS			=	compass
DIR_DRAWING_ALGOS	= 	drawing_algos
DIR_PLAYER			=	player
DIR_SPRITES			=	sprites
DIR_PIXEL_POINT		=	pixel_point
DIR_RAYCASTING		=	raycasting
DIR_XPM_PARSER		=	xpm_parser
DIR_HIT_DETECTION	=	hit_detection

## SOURCE FILES ##

INC_FILES		=		game.h				\
						sprites.h			\
						player.h			\
						vector.h			\
						parsing.h			\
						render_windows.h	\
						drawing_algos.h		\
						pixel_point.h		\
						compass.h			\
						user_inputs.h		\
						xpm_parser.h		\
						generic_utils.h		\
						hit_detection.h

SRC_MAIN			=	main.c				\
						game_settings.h		\
						settings.c

SRC_GAME			=	win_render_loop.c		\
						game_setup.c			\
						game_keys.c				\
						game_manager_keys.c		\
						game_manager_mouse.c	\
						free_game.c				\
						game_rotate.c			\
						game_render.c			\
						render_inside_compass.c		\
						map_player_collisions.c		\
						xpm_to_window.c				\
						super_debug_print.c			\
						game_render_hud.c			\
						enemy_movement.c			\
						bullet_rest.c
						

SRC_PLAYER			=	player_setup_and_actions.c	\
						player_aim.c				\
						player_move.c				\
						player_crouch_prone.c		\
						player_walk_height.c		\
						player_rotate.c				\
						player_jump.c				\
						player_timer.c

SRC_PARSING			=	parsing_main.c						\
						parsing_textures_get.c				\
						parsing_textures_analise.c			\
						parsing_file_to_list.c				\
						parsing_print_utils.c				\
						map_flood_count.c					\
						map_funcs.c							\
						map_dimensions.c		
						

SRC_XPM_PARSER		=	xpm_compiled_texture.c		\
						xpm_NSWE.c					\
						rubens_dementor.c			\
						xpm_mario.c					\
						xpm_items.c					\
						xpm_gun.c					\
						xpm_door.c					\
						xpm_free.c					\
						xpm_flying_bullet.c

SRC_GENERIC_UTILS 	= 	ft_split_count_replenish.c		\
						clamp.c							\
						fpow_2.c						\
						ft_fabs.c						\
						radian_truncate.c				\
						cubed_string_funcs.c

SRC_REN_WIN			=	win_init_window.c		\
						win_pixels.c			\
						win_callback_keys.c		\
						win_callback_mouse.c	\
						win_pause_blur.c	


SRC_COMPASS			=	compass_setup_render.c		\
						letter_north.c				\
						letter_south.c				\
						letter_east.c				\
						letter_west.c				\
						render_ring.c				\
						xlim_map_square.c				\
						xlim_inner_circle.c				\
						render_map_square.c				\
						compass_blur.c

SRC_DRAWING_ALGOS	=	drawing_lines.c				\
						liang_barsky_clipping.c		\
						liang_barsky_utils.c		\
						xiaolinwu_antialiasing.c	\
						xiaolinwu_utils.c		

SRC_PIXEL_POINT		=	gamma_correction.c				\
						pixels.c						\
						translate_rotate.c

SRC_RAYCASTING		=	vector.c					\
						raycasting.c				\
						wallcast.c					\
						floorcast.c					\
						spritecast.c				\
						doorcast.c					\
						shader.c

SRC_SPRITES			=	sprites.c					\
						sprite_quicksort.c			\
						sprites_hitmap.c			\
						shot_raycasting.c			\
						vertical_correction.c

SRC_HIT_DETECTION	=	lb_hit.c					\
						lb_hit_utils.c				\
						hit_list.c					

## AGGREGATING FILES ##

INCS		:=		$(addprefix $(INC_PATH)/, $(INC_FILES))


SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_MAIN))									\
					$(addprefix $(SRC_PATH)/$(DIR_PARSING)/, $(SRC_PARSING)) 				\
					$(addprefix $(SRC_PATH)/$(DIR_GENERIC_UTILS)/, $(SRC_GENERIC_UTILS))	\
					$(addprefix $(SRC_PATH)/$(DIR_REN_WIN)/, $(SRC_REN_WIN))				\
					$(addprefix $(SRC_PATH)/$(DIR_COMPASS)/, $(SRC_COMPASS))				\
					$(addprefix $(SRC_PATH)/$(DIR_DRAWING_ALGOS)/, $(SRC_DRAWING_ALGOS))	\
					$(addprefix $(SRC_PATH)/$(DIR_GAME)/, $(SRC_GAME))						\
					$(addprefix $(SRC_PATH)/$(DIR_PLAYER)/, $(SRC_PLAYER))					\
					$(addprefix $(SRC_PATH)/$(DIR_RAYCASTING)/, $(SRC_RAYCASTING))					\
					$(addprefix $(SRC_PATH)/$(DIR_XPM_PARSER)/, $(SRC_XPM_PARSER))					\
					$(addprefix $(SRC_PATH)/$(DIR_PIXEL_POINT)/, $(SRC_PIXEL_POINT))				\
					$(addprefix $(SRC_PATH)/$(DIR_SPRITES)/, $(SRC_SPRITES))						\
					$(addprefix $(SRC_PATH)/$(DIR_HIT_DETECTION)/, $(SRC_HIT_DETECTION))			
					

OBJS 		:=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

ALL_INCS	= 		-I$(INC_PATH) -I$(GLFW_INC) -I$(GLEW_INC) -I$(LIB_PATH)/$(LIB_INC_P)
LIBS		=		$(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(GLFW_LIB) $(GLEW_LIB)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) $(ALL_INCS) -o $(NAME) $(LIBS)
	@echo Program $(NAME) ready!!

$(OBJ_PATH)/settings.o : $(SRC_PATH)/settings.c $(SRC_PATH)/game_settings.h
	@if not exist $(OBJ_PATH) \
	( \
		powershell -File mkdir.ps1 \
	)
	$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@
	
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

git: fclean
	git add * && git commit -m "commiting" && git push

.PHONY: clean fclean message bonus