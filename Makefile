TARGET = work

SOURCES = work2.c

OBJECTS = $(SOURCES:%.c=%.c.o)
INCLUDE = -I.
CFLAGS = -g -O2 -Wall $(INCLUDE) -static
LDFLAGS = -static
CC = arm-none-linux-gnueabi-gcc
LD = arm-none-linux-gnueabi-gcc

$(TARGET): $(OBJECTS)
	@echo [Compiling Target File] $@ 
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@ 

%.c.o: %.c		
	@echo [Compiling Object File] $<...
	@$(CC) -c $(CFLAGS) $< -o $@

clean: .PHONY
	@echo [CLEAN DONE] 
	@rm -f $(OBJECTS) $(TARGET)

.PHONY:
