#簡略式makfefile for msys64 / GDI
 
TAR = main.exe

OBJS = \
	obj/main.o \

LIBS = \
	 -lgdi32

FLGS = \
	-g \
	-c \
	-m64 \
	-std=c++17 \
	-O1 \

#	-Werror \


#CC	= clang++
CC	= g++

$(TAR)	:	obj $(OBJS)
	$(CC) -o $(TAR) $(OBJS) $(LIBS)

obj/main.o:main.cpp
	$(CC)  $(FLGS) $< -o $@

obj/%.o:%.cpp %.h
	$(CC)  $(FLGS) $< -o $@

obj:
	mkdir obj

clean:
	rm -f *.exe
	rm -rf obj


