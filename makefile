CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lSDL_image -lGLU -lGL -lm -lglut -lSDL_ttf

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/



# Fichiers main
OBJ_MAIN= main.o
EXEC_MAIN= main.out

# Fichiers draw
OBJ_DRAW= draw.o
EXEC_DRAW= draw.out

OBJ_VERIFY= verify.o
EXEC_VERIFY= verify.out

OBJ_VERIFY_MAP= verifyMap.o
EXEC_VERIFY_MAP= verifyMap.out

OBJ_CREATE_MAP= createMap.o
EXEC_CREATE_MAP= createMap.out



# Regles compilation

all :

map : $(OBJDIR)$(OBJ_TD01_MAP)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_MAP) -o $(BINDIR)$(EXEC_TD01_MAP) $(LDFLAGS)

map2 : $(OBJDIR)$(OBJ_TD01_MAP2)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_MAP2) -o $(BINDIR)$(EXEC_TD01_MAP2) $(LDFLAGS)

main : $(OBJDIR)$(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_MAIN) -o $(BINDIR)$(EXEC_MAIN) $(LDFLAGS)

draw : $(OBJDIR)$(OBJ_DRAW)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_DRAW) -o $(BINDIR)$(EXEC_DRAW) $(LDFLAGS)

verify : $(OBJDIR)$(OBJ_VERIFY)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_VERIFY) -o $(BINDIR)$(EXEC_VERIFY) $(LDFLAGS)

verifyMap : $(OBJDIR)$(OBJ_VERIFY_MAP)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_VERIFY_MAP) -o $(BINDIR)$(EXEC_VERIFY_MAP) $(LDFLAGS)
	
createMap : $(OBJDIR)$(OBJ_CREATE_MAP)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_CREATE_MAP) -o $(BINDIR)$(EXEC_CREATE_MAP) $(LDFLAGS)


clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
