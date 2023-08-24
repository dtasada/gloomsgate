CC = gcc

CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

SRCDIR = src
SRCS = $(SRCDIR)/main.c

BUILDDIR = build

OBJS = $(SRCS:.c=.o)

TARGET = $(BUILDDIR)/game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(OBJS) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)