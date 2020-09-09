#Before modifying this file, ensure the editor is tab intended

#Listing down all the rules, to ensure their execution 
#irrespective of existing file in the Makefile location
.PHONY: deploy test clean default lint

EXE?= runme

#if nothing sepcified use this default variable
LIB_DIR?=lib
SRC_DIR?=./src
TEST_DIR?=./test
OBJ_DIR?=./obj
CPP_FLAGS?=-std=c++17 -Wall
C_FLAGS?=-Wall

INCLUDES=-I./\
		-I./include\
		-I$(SRC_DIR)/include\
		-I$(TEST_DIR)/include

CPP_SRCS=$(TEST_DIR)/test_main.cpp
C_SRCS=$(SRC_DIR)/clockp.c


CPP_OBJS=$(CPP_SRCS:.cpp=.o)

C_OBJS=$(C_SRCS:.c=.o)

#The standard structure of Makefile is as below
#TARGET: PREQUISITES
#	RECIPE
#The first rule is default rule. If nothing is specified only this rule is executed
default: $(C_SRCS)
	@echo "1 Building the main application in standalone mode"
	gcc $(C_FLAGS) $(INCLUDES) $(C_SRCS) -DINCLUDE_MAIN -o $(EXE)

test: 
	@echo "1 Generating objects for all c files"
	gcc $(C_FLAGS) $(INCLUDES) -c $(C_SRCS) -o $(C_OBJS)
	@echo "2 Generating objects for all cpp files"
	g++ $(CPP_FLAGS) $(INCLUDES) -c $(CPP_SRCS) -o $(CPP_OBJS)
	g++ -o $(EXE) $(C_OBJS) $(CPP_OBJS)

clean:
	@echo "Removing the object files"
	rm $(C_OBJS) $(CPP_OBJS) $(EXE)

lint:
	@echo "Linting the codebase"
	#TODO:
	#oclint $(LINT_SRC) $(CPP_FLAGS) $(INCLUDES)


# TODO: Update the hard coded file names with autofill

#% gcc -c clockp.c -I.
#% g++ -c test_main.cpp  -std=c++17 -I.
#% g++ -o runme test.o clockp.o
#% gcc -Wall -I./ -I./include -I./src/include ./src/clockp.c -o opt

