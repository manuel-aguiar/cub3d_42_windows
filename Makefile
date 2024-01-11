
## BUILD DETAILS

NAME 		=		cub3d

COMP 		= 		gcc -g -O3

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

## SOURCE FILES ##

INC_FILES	=		cub3d.h

SRC_MAIN	=		main.c

#SRC_FILES	=		

INCS		:=		$(addprefix $(INC_PATH)/, $(INC_FILES))

SRCS 		:=		$(addprefix $(SRC_PATH)/, $(SRC_MAIN))
##$(addprefix $(SRC_PATH)/, $(SRC_FILES))
							
OBJS 		:=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

ALL_INCS	= 		-I$(INC_PATH) -I$(GLFW_INC) -I$(GLEW_INC) -I$(LIB_PATH)/$(LIB_INC_P)
LIBS		=		$(ADD_LIB) $(LIB_PATH)/$(LIBFT) $(GLFW_LIB) $(GLEW_LIB)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(COMP) $(FLAGS) $(OBJS) $(ALL_INCS) -o $(NAME) $(LIBS)
	@echo Program $(NAME) ready!!


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@if not exist $(OBJ_PATH) \
	( \
		powershell -File mkdir.ps1 ; \
	)
	@$(COMP) $(FLAGS) $(ALL_INCS) -c $< -o $@

clean:
	@if exist $(OBJ_PATH) \
	( \
		rmdir /s /q $(OBJ_PATH) ; \
	)
	@if exist $(LIB_PATH)/$(LIBFT) \
	( \
		@$(MAKE) clean -C $(LIB_PATH) ; \
	)

fclean: clean
	@if exist $(NAME) \
	( \
		del $(NAME); \
	)
	@if exist $(LIB_PATH)/$(LIBFT) \
	( \
		@$(MAKE) fclean -C $(LIB_PATH) ; \
	)

$(LIBFT):
	@$(MAKE) -C $(LIB_PATH)

run: $(NAME)
	@./$(NAME)

re: fclean all

.PHONY: clean fclean re message bonus
