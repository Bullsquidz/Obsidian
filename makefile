SRC := $(shell find src -type f -name '*.cpp')
HDR := $(shell find src -type d)

VNDR = vendor

INCS = $(addprefix -I, $(HDR)) \
		-I$(VNDR)/SDL3/include \
		-I$(VNDR)/SDL3_image/include 

LIBS = -L$(VNDR)/SDL3/lib			-lSDL3 \
		-L$(VNDR)/SDL3_image/lib 	-lSDL3_image

all:
	g++ $(SRC) -o a $(INCS) $(LIBS) -o a

clean:
	rm -f *.o
	rm -f src/**/*.o
	rm -f a
	make
