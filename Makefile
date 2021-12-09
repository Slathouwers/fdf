# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:41:21 by slathouw          #+#    #+#              #
#    Updated: 2021/12/09 08:29:38 by slathouw         ###   ########.fr        #
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
MLXFLAG = -lmlx -lXext -lX11 -lm
OBJDIR	= obj

#FDF files 
SOURCES	= fdf.c projections.c screen.c utils.c utils1.c color.c camera.c mesh.c \
			parser.c tests.c 
SRCDIR 	= srcs
SRCS 	= ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS	= ${addprefix $(OBJDIR)/, $(SOURCES:.c=.o)}

#LIN_ALG files 
LASOURCES	= matrix_ops.c matrix_transf.c matrix.c vector.c vector_ops.c vector_transf.c
LADIR 	= srcs/lin_alg
LASRCS 	= ${addprefix $(LADIR)/, $(LASOURCES)}
LAOBJS	= ${addprefix $(OBJDIR)/la_, $(LASOURCES:.c=.o)}

#FT_ARRAY files 
ARRSOURCES	= array.c int_array.c ft_realloc.c
ARRDIR 	= srcs/ft_array
ARRSRCS = ${addprefix $(ARRDIR)/, $(ARRSOURCES)}
ARROBJS	= ${addprefix $(OBJDIR)/arr_, $(ARRSOURCES:.c=.o)}

###############
# COMPILATION #
###############

all : 		${NAME}

#FDF linking compilation
$(NAME) :	$(OBJS) ${LAOBJS} ${ARROBJS}
	@make -sC $(LIBFT)
	@cp $(LIBFT)/libftprintf.a .
	@${CC} ${CFLAGS} -I${INCLUDES}  ${OBJS} ${LAOBJS} ${ARROBJS} -L/usr/lib $(MLXFLAG) libftprintf.a -o ${NAME}
	@echo "fdf binary created!"

#FDF object compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I${INCLUDES} -I/usr/include -c $< -o $@

#LA SOURCES object compilation
$(OBJDIR)/la_%.o: $(LADIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

#ARR SOURCES object compilation
$(OBJDIR)/arr_%.o: $(ARRDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

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
