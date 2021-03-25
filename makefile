CXX = g++
CXX_FLAGS = -std=c++17
CXX_FLAGS += -Wuninitialized -Wall -Wextra -Werror -pedantic -Wfatal-errors # source code quality.
CXX_FLAGS += -O3 -ffast-math # non-debug version.
#CXX_FLAGS += -O0 -g # debug version.
CXX_FLAGS += -I./ # include paths.

SRCS = example.cc \
    point_quadtree/point.cc \
    point_quadtree/box.cc \
    point_quadtree/domain.cc \
    point_quadtree/grid_position.cc \
    point_quadtree/morton_keys.cc \
    point_quadtree/node.cc \
    point_quadtree/point_inserter.cc \
    point_quadtree/point_quadtree.cc

%.o: %.cc; $(CXX) $(CXX_FLAGS) -o $@ -c $<

OBJS = $(SRCS:.cc=.o)

all: $(OBJS); $(CXX) $^ $(LINK_FLAGS) -o example.out

clean: ; rm -rf example.out $(OBJS) *.dSYM
