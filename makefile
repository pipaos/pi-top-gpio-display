LIBS = `pkg-config --libs gtk+-3.0`

CFLAGS = `pkg-config --cflags gtk+-3.0`

APP:=pitop-gpio

all: $(APP)

$(APP): main.c application.c application.h main.h
	gcc -o $(APP) main.c application.c application.h $(LIBS) $(CFLAGS) -lwiringPi
