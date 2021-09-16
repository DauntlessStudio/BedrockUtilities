CC=g++
DEPS = json.hpp getopt.h JsonSources.h DirectoryHandler.h lodepng.h
OBJ = BedrockTerminal.o lodepng.o
SRC = /data/data/com.termux/files/usr/bin

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bed: $(OBJ)
	$(CC) -o $(SRC)/$@ $^ $(CFLAGS)
	
.PHONY: clean


clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~