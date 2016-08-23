SRC_DIR = src
INCLUDE_DIR = include
INCLUDE_INTERFACE_DIR = interface/include
SRC_INTERFACE_DIR = interface/src

all: obj app

main: my_main app
	touch main
obj:
	g++ -Wall -Werror -c -std=c++14 -I $(INCLUDE_DIR)/ -I $(INCLUDE_INTERFACE_DIR)/ $(SRC_INTERFACE_DIR)*.cpp $(SRC_DIR)/*.cpp 
app:
	g++ -Wall -Werror -std=c++14 *.o -o project
clear: 
	rm *.o project
my_main:
	g++ -c -Wall -Werror -std=c++14 -I/$(INCLUDE_DIR) $(SRC_DIR)/main.cpp
help:
	echo "Create application\nobj to create *.o \napp to create application\nclear to clear created file\nmain to create main.o\ntest to start valgrind\nrun to run application\n "
test:
	valgrind ./project
run: 
	./project
