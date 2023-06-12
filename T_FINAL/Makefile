# # <Copyright ChatGPT - 2023, June 6th>

# # Diretórios de origem
# SRC_DIR := src
# INC_DIR := classes

# LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm -lpng -g

# # Obter lista de arquivos .cc e .h
# SRCS := $(wildcard *.cc)
# INCS := $(wildcard $(INC_DIR)/*.h)

# # Obter lista de arquivos objeto
# OBJS := $(SRCS:.cc=.o)

# # Nome do executável
# TARGET := main

# # Flags do compilador
# CXXFLAGS := -Wall -Wextra -I$(INC_DIR) -g -ansi -pedantic -std=c++17

# # Regra para o alvo principal
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# # Regra genérica para compilar arquivos objeto
# %.o: %.cc $(INCS)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# .PHONY: clean
# clean:
# 	rm -f $(OBJS) $(TARGET)


# Cody Barnson
# Thur Mar 31, 2016
# Makefile for allegro game project

# declaration of variables
CC = g++
CCFLAGS = -Wall -g -std=c++14 

# file names
NONTEST = main.cc main.o

SOURCES = $(filter-out $(NONMAIN), $(wildcard *.cc))
OBJECTS = $(SOURCES:.cc=.o)

LIBDIR = -L/usr/lib/x86_64-linux-gnu

LNFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lm -lpng -g

# main target
all: main

main: $(OBJECTS)
	$(CC) $(LIBDIR) -o $@ $^ $(LNFLAGS)

# pull in dependency info for existing .o files
-include $(OBJECTS:.o=.d) $(OBJECTS:.o=.d)

# compile and generate dependency info
%.o: %.cc
	$(CC) -c $(CCFLAGS) $< -o $@
# $(CC) -M $(CCFLAGS) $*.cc > $*.d

# automatic variables
# $< contains the first dependency file name
# $@ contains the target file name

# phony targets --> avoid conflict with file of the same name, and
#                   improve performance
.PHONY: clean

# clean out the directory but keep executables with command "clean"
clean : 
	rm -f *~ *.o *.d *.gch main



