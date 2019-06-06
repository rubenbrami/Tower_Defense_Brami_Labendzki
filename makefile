CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm -lglut -lSDL_ttf

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# # Fichiers TD 01

# # Fichiers exercice 02
# OBJ_TD01_EX02= ex02/td01_ex02.o
# EXEC_TD01_EX02= td01_ex02.out

# # Fichiers exercice 03
# OBJ_TD01_EX03= ex03/td01_ex03.o
# EXEC_TD01_EX03= td01_ex03.out

# # Fichiers exercice 04
# OBJ_TD01_EX04= ex04/td01_ex04.o
# EXEC_TD01_EX04= td01_ex04.out

# # Fichiers exercice 05
# OBJ_TD01_EX05= ex05/td01_ex05.o
# EXEC_TD01_EX05= td01_ex05.out

# # Fichiers exercice 06
# OBJ_TD01_EX06= ex06/td01_ex06.o
# EXEC_TD01_EX06= td01_ex06.out

# Fichiers map
OBJ_TD01_MAP= td01_map.o
EXEC_TD01_MAP= td01_map.out

OBJ_MAP2= map2.o
EXEC_MAP2= map2.out

# Fichiers spritz
OBJ_MAIN= main.o
EXEC_MAIN= main.out

# Fichiers draw
OBJ_DRAW= draw.o
EXEC_DRAW= draw.out

# Regles compilation TD 01

all :

# ex02 : $(OBJDIR)$(OBJ_TD01_EX02)
# 	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX02) -o $(BINDIR)$(EXEC_TD01_EX02) $(LDFLAGS)

# ex03 : $(OBJDIR)$(OBJ_TD01_EX03)
# 	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX03) -o $(BINDIR)$(EXEC_TD01_EX03) $(LDFLAGS)
	
# ex04 : $(OBJDIR)$(OBJ_TD01_EX04)
# 	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX04) -o $(BINDIR)$(EXEC_TD01_EX04) $(LDFLAGS)
	
# ex05 : $(OBJDIR)$(OBJ_TD01_EX05)
# 	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX05) -o $(BINDIR)$(EXEC_TD01_EX05) $(LDFLAGS)

# ex06 : $(OBJDIR)$(OBJ_TD01_EX06)
# 	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX06) -o $(BINDIR)$(EXEC_TD01_EX06) $(LDFLAGS)

map : $(OBJDIR)$(OBJ_TD01_MAP)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_MAP) -o $(BINDIR)$(EXEC_TD01_MAP) $(LDFLAGS)

map2 : $(OBJDIR)$(OBJ_TD01_MAP2)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_MAP2) -o $(BINDIR)$(EXEC_TD01_MAP2) $(LDFLAGS)

main : $(OBJDIR)$(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_MAIN) -o $(BINDIR)$(EXEC_MAIN) $(LDFLAGS)

draw : $(OBJDIR)$(OBJ_DRAW)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_DRAW) -o $(BINDIR)$(EXEC_DRAW) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
