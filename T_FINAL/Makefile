# <Copyright ChatGPT - 2023, June 6th>

# Diretórios de origem
SRC_DIR := src
INC_DIR := classes

LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm -lpng -g

# Obter lista de arquivos .cc e .h
SRCS := $(wildcard *.cc)
INCS := $(wildcard $(INC_DIR)/*.h)

# Obter lista de arquivos objeto
OBJS := $(SRCS:.cc=.o)

# Nome do executável
TARGET := main

# Flags do compilador
CXXFLAGS := -Wall -Wextra -I$(INC_DIR) -g -ansi -pedantic -std=c++17

# Regra para o alvo principal
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Regra genérica para compilar arquivos objeto
%.o: %.cc $(INCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)