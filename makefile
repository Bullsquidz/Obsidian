SRC := $(shell find src -type f -name '*.cpp')
HDR := $(shell find src -type d)

INCS = $(addprefix -I, $(HDR)) \
		-Ilibs/SDL3/include \
		-Ilibs/SDL3_image/include 

LIBS = -Llibs/SDL3/lib			-lSDL3 \
		-Llibs/SDL3_image/lib 	-lSDL3_image \
	    -Wl,-rpath,'$$ORIGIN/libs/SDL3/lib' \
    	-Wl,-rpath,'$$ORIGIN/libs/SDL3_image/lib'

all:
	g++ $(SRC) -o a $(INCS) $(LIBS) -o a

clean:
	rm -f *.o
	rm -f src/**/*.o
	rm -f a
