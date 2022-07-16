# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abittel <abittel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 10:24:03 by abittel           #+#    #+#              #
#    Updated: 2022/07/16 17:18:56 by abittel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_TEST    =  test.cpp
SRCS_TIME    =  test_time.cpp
OSRCS_TEST   =  ${SRCS_TEST:.cpp=.o}
OSRCS_TIME   =  ${SRCS_TIME:.cpp=.o}
NAME_TEST_FT =  test_ft
NAME_TEST_STD = test_std
NAME_TIME =     test_time

all : ${NAME}

%.o: %.cpp 
        c++ -Wall -Werror -Wextra -std=c++98 -c $< -o ${<:.cpp=.o}
${NAME} :       ${OSRCS_TEST} ${OSRCS_TIME}
        c++ -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=ft ${OSRCS_TEST} -o ${NAME_TEST_FT} 
        c++ -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=std ${OSRCS_TEST} -o ${NAME_TEST_STD} 
        c++ -Wall -Werror -Wextra -std=c++98 ${OSRCS_TIME} -o ${NAME_TIME} 
clean :
	rm -f ${OSRCS_TEST} ${OSRCS_TIME}
fclean : clean
	rm -f ${NAME}
re : fclean all

.PHONY: all clean fclean re
