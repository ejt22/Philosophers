# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 11:55:16 by ejoo-tho          #+#    #+#              #
#    Updated: 2022/10/12 10:11:20 by ejoo-tho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White

# -------------------------------------VARS--------------------------------------

NAME	= philo

CC		= @gcc

CFLAGS	= -Wall -Wextra -Werror -pthread

RM		= @rm -f

# ---------------------------------SOURCE FILES----------------------------------

SRCS	= philo.c \
			utils.c \
			routine.c \
			error.c \

OBJS	= ${SRCS:.c=.o}

INCS	= -I ./includes

# ------------------------------------RULES--------------------------------------

%.o:		%.c
			${CC} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}
				@echo $(Green)√$(Color_Off)$(Cyan)Philo has been compiled!$(Color_Off);

all:		$(NAME)

clean:
			${RM} ${OBJS}
			@echo $(Green)√$(Color_Off)$(Purple)Clean succeeded, all the '.o' have been removed!$(Color_Off);

fclean:		clean
			${RM} ${NAME}
			@echo $(Green)√$(Color_Off)$(Blue)Fclean succeeded, everything has been removed!$(Color_Off);

re:			fclean all

# -----------------------------------PHONY---------------------------------------

.PHONY:		all clean fclean re
