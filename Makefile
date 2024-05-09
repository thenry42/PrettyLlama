#IMGUI SDL2 SDLRENDERER2 RULES

IMGUIFLAGS 	= -I imgui/ -I imgui/backends -g `sdl2-config --cflags`

LIBS		= -lGL -ldl `sdl2-config --libs`

#==============================================================================

SRCS		=	src/main.cpp \
				src/Meta.cpp \
				src/Model.cpp \
				src/utils.cpp \
				imgui/imgui.cpp \
			  	imgui/imgui_demo.cpp \
			  	imgui/imgui_draw.cpp \
			  	imgui/imgui_tables.cpp \
			  	imgui/imgui_widgets.cpp \
			  	imgui/backends/imgui_impl_sdl2.cpp \
			  	imgui/backends/imgui_impl_sdlrenderer2.cpp

NAME		=	vicuna

OBJDIR		=	obj

CXXFLAGS	=	-Wall -Wextra -Werror -g

CXX			=	c++

RM			=	rm -rf

OBJS		=	${patsubst %.cpp, ${SRCS:%.cpp=${OBJDIR}/%.o}, ${SRCS}}

INC		=	-I inc/

all:			${NAME}

${NAME}:		${OBJS}
				${CXX} ${INC} ${IMGUIFLAGS} ${CXXFLAGS} ${LIBS} $^ -o $@

${OBJDIR}/%.o:	%.cpp | ${OBJDIR}
				${CXX} ${INC} ${IMGUIFLAGS} ${CXXFLAGS} ${LIBS} -MMD -MP -c $< -o $@

${OBJDIR}:		
				mkdir -p ${OBJDIR}
				mkdir -p ${OBJDIR}/src/
				mkdir -p ${OBJDIR}/imgui/
				mkdir -p ${OBJDIR}/imgui/backends/

clean:		
				${RM} ${OBJDIR}
				${RM} imgui.ini

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all re clean fclean
