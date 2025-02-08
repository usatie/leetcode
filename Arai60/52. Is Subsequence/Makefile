NAME = a.out
SRC = main.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

all: $(NAME)

$(NAME): $(SRC) step1.hpp step2.hpp step3.hpp
	$(CXX) -o $(NAME) $(SRC) $(CXXFLAGS)

run: $(NAME)
	./$(NAME)
