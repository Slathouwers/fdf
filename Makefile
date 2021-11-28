# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:41:21 by slathouw          #+#    #+#              #
#    Updated: 2021/11/28 06:11:28 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# VARIABLES #
#############

NAME 	= fdf
INCLUDES= includes
LIBFT 	= libs/libftprintf
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
MLXFLAG = -lmlx -lXext -lX11
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
	@${CC} ${CFLAGS} -I${INCLUDES}  ${OBJS} -L/usr/lib $(MLXFLAG) libftprintf.a -o ${NAME}
	@echo "fdf binary created!"

#FDF object compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I${INCLUDES} -I/usr/include -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@make clean -sC $(LIBFT)
	@echo "objects removed..."

fclean: clean
	@rm -f $(NAME) libftprintf.a
	@make fclean -sC $(LIBFT)
	@echo "binaries removed..."


re :		fclean all

.PHONY: all clean fclean re bonus
