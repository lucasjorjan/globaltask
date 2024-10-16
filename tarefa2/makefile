# Nome do executável
TARGET = formas

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra

# Arquivos-fonte
SRCS = main.c formaGeometrica.c triangulo.c retangulo.c

# Arquivos-objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão para compilar o projeto
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos-objeto e do executável
clean:
	del /Q *.o $(TARGET).exe

# Regra para executar o programa após compilado
run: $(TARGET)
	./$(TARGET)
