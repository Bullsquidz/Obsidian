SRC := $(shell find src -type f -name '*.cpp')
HDR := $(shell find src -type d)

INCS = $(addprefix -I, $(HDR)) \
		-Ilibs/SDL3/include \
		-Ilibs/SDL3_image/include 

LIBS = -Llibs/SDL3/lib			-lSDL3 \
		-Llibs/SDL3_image/lib 	-lSDL3_image \
	    -Wl,-rpath,'$$ORIGIN/libs/SDL3/lib' \
    	-Wl,-rpath,'$$ORIGIN/libs/SDL3_image/lib'


WLIBS = -Llibs/SDL3/win_lib -lmingw32 -lSDL3 -lSDL3_image \
            -Llibs/SDL3_image/win_lib -mwindows

linux:
	g++ $(SRC) -o a $(INCS) $(LIBS)

windows:
	x86_64-w64-mingw32-g++ $(SRC) -o o.exe $(INCS) $(WLIBS)

clean:
	rm -f *.o
	rm -f src/**/*.o
	rm -f a
