EXE = systolic
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
CC = g++

# Flags d\u2019erreurs:
ERROR_FLAGS = -Wall -W -pedantic

# Flags pour le compilateur:
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0 gio-2.0 glib-2.0 )
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)

# Flags pour l\u2019editeur de lien:
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0 gio-2.0 glib-2.0)
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#callback.o: callback.c interface.o

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	@rm -rf $(EXE) ./src/$(OBJ)