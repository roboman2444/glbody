CC = gcc
LDFLAGS = -lGL -lGLU -lGLEW `sdl-config --libs`  -lm
CFLAGS = -Wall -O3 `sdl-config --cflags`
CDFLAGS = -Wall -O0 -g -Q -v -da `sdl-config --cflags`
OBJECTS = filemanager.o glbody.o sdlmanager.o glmanager.o shadermanager.o framebuffermanager.o matrixlib.o gamecode.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

glbody: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
debug: $(OBJECTS)
	$(CC) $(CDFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
	@rm -f glbody
	@rm -f debug
