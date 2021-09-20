CC=g++
OBJ = BedrockTerminal.cpp lodepng.cpp directory_handler.cpp file_manager.cpp entity.cpp
SRC = /data/data/com.termux/files/usr/bin

bed: $(OBJ)
	$(CC) -o $(SRC)/$@ $^ $(CFLAGS)