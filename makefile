CC = gcc
CFLAGS = -Wall -W            # <- permissivo, sem -ansi -pedantic
OBJDIR = build
OBJS = $(OBJDIR)/ProjetoEscola.o $(OBJDIR)/alunos.o $(OBJDIR)/professores.o $(OBJDIR)/disciplinas.o $(OBJDIR)/utilitarios.o $(OBJDIR)/relatorios.o
TARGET = ProjetoEscola

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.c ProjetoEscola.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
