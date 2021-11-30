# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:41:21 by slathouw          #+#    #+#              #
#    Updated: 2021/11/30 13:16:18 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# VARIABLES #
#############

NAME 	= fdf
INCLUDES= includes
LIBFT 	= libs/libftprintf
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
MLXFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit
OBJDIR	= obj

#PUSH_SWAP files 
SOURCES	= fdf.c
SRCDIR 	= srcs
SRCS 	= ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS	= ${addprefix $(OBJDIR)/, $(SOURCES:.c=.o)}

###############
# COMPILATION #
###############

all : 		${NAME}

#FDF linking compilation
$(NAME) :	$(OBJS)
	@make -sC $(LIBFT)
	@cp $(LIBFT)/libftprintf.a .
	@make -sC mlx
	@cp mlx/libmlx.dylib .
	@${CC} ${CFLAGS} -I${INCLUDES}  ${OBJS} $(MLXFLAG) libftprintf.a -o ${NAME}
	@echo "fdf binary created!"

#FDF object compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I${INCLUDES} -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@make clean -sC $(LIBFT)
	@make clean -sC mlx
	@echo "objects removed..."

fclean: clean
	@rm -f $(NAME) libftprintf.a libmlx.dylib
	@make fclean -sC $(LIBFT)
	@make fclean -sC mlx
	@echo "binaries removed..."


re :		fclean all

.PHONY: all clean fclean re bonus
