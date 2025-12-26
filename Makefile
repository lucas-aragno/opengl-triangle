CC      := clang
CFLAGS  := -Wall -Wextra -std=c11 \
           -Iinclude \
           -I/opt/homebrew/include

LDFLAGS := -L/opt/homebrew/lib \
           -lglfw \
           -framework OpenGL

SRC     := main.c shaders.c glad.c mesh.c
OBJ     := $(SRC:.c=.o)
TARGET  := app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
