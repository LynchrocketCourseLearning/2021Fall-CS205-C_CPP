SRC_DIR = ./src
SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SOURCE))
TARGET = final
INCLUDE = -I./inc


CC = g++
CFLAGS = -c -Wall

$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ)
%.o:%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE)



.PHONY:clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)