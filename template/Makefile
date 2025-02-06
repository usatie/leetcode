NAME = a.out
SRC = main.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

all: $(NAME)

$(NAME): $(SRC) step1.hpp
	$(CXX) -o $(NAME) $(SRC) $(CXXFLAGS)

run: $(NAME)
	./$(NAME)
