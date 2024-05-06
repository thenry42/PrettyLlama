SRCS		=	src/main.cpp \
				src/Meta.cpp \
				src/Model.cpp \
				src/imgui_impl_glfw.cpp \
				src/imgui_impl_opengl3.cpp \
				src/imgui.cpp \
				src/imgui_draw.cpp \
				src/imgui_widgets.cpp \
				src/imgui_demo.cpp \
				src/imgui_tables.cpp \

NAME		=	vicuna

OBJDIR		=	obj

CXXFLAGS	=	-Wall -Wextra -Werror -g

LIBS		=	-lglfw -lGL -lglfw3 -lGLFW -lgdi32 -lopencv -lopengl32

CXX			=	c++

RM			=	rm -rf

OBJS		=	${patsubst %.cpp, ${SRCS:%.cpp=${OBJDIR}/%.o}, ${SRCS}}

INC		=	-I inc/

all:			${NAME}

${NAME}:		${OBJS}
				${CXX} ${INC} ${CXXFLAGS} $^ -o $@

${OBJDIR}/%.o:	%.cpp | ${OBJDIR}
				${CXX} ${INC} ${CXXFLAGS} ${LIBS} -MMD -MP -c $< -o $@

${OBJDIR}:		
				mkdir -p ${OBJDIR}
				mkdir -p ${OBJDIR}/src/

clean:		
				${RM} ${OBJDIR}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all re clean fclean
