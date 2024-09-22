# Nom de l'exécutable
TARGET = Convertool.exe

# Répertoires
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
LIB_DIR = lib
RES_DIR = res

# Fichiers sources
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Fichiers objets
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Fichier de ressources
RC_FILE = $(RES_DIR)/icon.rc
RES_FILE = $(BIN_DIR)/icon.res

# Options du compilateur
DEBUG_FLAGS = -g
HIDE_CONSOLE = -mwindows
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Options du linker
LDFLAGS = -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Règle par défaut
all: LDFLAGS += $(HIDE_CONSOLE)
all: $(BIN_DIR)/$(TARGET)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(TARGET)

# Règle pour la construction de l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJ_FILES) $(RES_FILE)
	@echo "->   Linking..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Build successful!"

# Règle pour compiler les fichiers .c en .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@echo "->   Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour compiler le fichier .rc en .res
$(RES_FILE): $(RC_FILE)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@echo "->   Compiling resource file..."
	windres $< -O coff -o $@

# Nettoyage des fichiers objets, de l'exécutable et du fichier .res
clean:
	@echo "->   Cleaning up...
	@if exist $(BIN_DIR)\*.o del /Q $(BIN_DIR)\*.o
	@if exist $(BIN_DIR)\$(TARGET) del /Q $(BIN_DIR)\$(TARGET)
	
	
	@echo "->  Clean complete!

# @if exist $(RES_FILE) del /Q $(RES_FILE)
# Indiquer au make de ne pas considérer ces règles comme des fichiers
.PHONY: clean all
