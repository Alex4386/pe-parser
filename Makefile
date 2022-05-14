CC=g++
BUILD_DIR=./build

all:
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	$(CC) -static -static-libgcc -static-libstdc++ -o $(BUILD_DIR)/pe-parser src/*.cpp src/analyze/*.cpp src/parser/*.cpp src/common/*.cpp

clean:
	$(RM) $(BUILD_DIR)/pe-parser
