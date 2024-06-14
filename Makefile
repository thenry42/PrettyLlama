#===================================================================#
# MAKEFILE RULES                                                    #
#===================================================================#

SRCS		=	src/main.cpp \
				src/Model.cpp \
				src/Ollama.cpp \
				src/History.cpp \

NAME		=	PrettyLlama

OBJDIR		=	obj

CXXFLAGS	=	-Wall -Wextra -Werror -g

CXX			=	c++

RM			=	rm -rf

OBJS		=	${patsubst %.cpp, ${SRCS:%.cpp=${OBJDIR}/%.o}, ${SRCS}}

INC		=	-I inc/

all:			${NAME}

${NAME}:		${OBJS}
				${CXX} ${INC} ${CXXFLAGS} -lreadline $^ -o $@

${OBJDIR}/%.o:	%.cpp | ${OBJDIR}
				${CXX} ${INC} ${CXXFLAGS} -MMD -MP -c $< -o $@

${OBJDIR}:		
				mkdir -p ${OBJDIR}
				mkdir -p ${OBJDIR}/src/

clean:		
				${RM} ${OBJDIR}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all re clean fclean
