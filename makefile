

main: main.o charset.o input.o sdl.o pause.o pong.o start.o gameover.o
	clang objs/main.o objs/charset.o objs/input.o objs/sdl.o objs/pause.o objs/pong.o objs/start.o objs/gameover.o -lSDL2 -lSDL2_ttf -o bin/main.game -no-pie

main.o:
	clang -c src/main.c -o objs/main.o -I/usr/include/SDL2 -Isrc/

charset.o:
	clang -c src/charset/charset.c -o objs/charset.o -I/usr/include/SDL2 -Isrc/

input.o:
	clang -c src/input/input.c -o objs/input.o -I/usr/include/SDL2 -Isrc/

sdl.o:
	clang -c src/utils/sdl.c -o objs/sdl.o -I/usr/include/SDL2 -Isrc/


pause.o:
	clang -c src/views/pause/pause.c -o objs/pause.o -I/usr/include/SDL2 -Isrc/

pong.o:
	clang -c src/views/pong/pong.c -o objs/pong.o -I/usr/include/SDL2 -Isrc/

start.o:
	clang -c src/views/start/start.c -o objs/start.o -I/usr/include/SDL2 -Isrc/

gameover.o:
	clang -c src/views/gameover/gameover.c -o objs/gameover.o -I/usr/include/SDL2 -Isrc/