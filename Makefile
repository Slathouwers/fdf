# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:41:21 by slathouw          #+#    #+#              #
#    Updated: 2021/11/12 14:01:19 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# VARIABLES #
#############

NAME 	= fdf
INCLUDES= includes
CC		= gcc
CFLAGS	= 
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
	@${CC} ${CFLAGS} -I${INCLUDES}  ${OBJS} -L/usr/lib $(MLXFLAG) -o ${NAME}
	@echo "fdf binary created!"

#FDF object compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I${INCLUDES} -I/usr/include -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@echo "objects removed..."

fclean: clean
	@rm -f $(NAME)
	@echo "binaries removed..."


re :		fclean all

.PHONY: all clean fclean re bonus
