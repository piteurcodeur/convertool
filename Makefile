# Nom de l'exécutable
TARGET = prog.exe

# Répertoires
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
LIB_DIR = lib

# Fichiers sources
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Fichiers objets
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Options du compilateur
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Options du linker
LDFLAGS = -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Règle par défaut pour la construction de l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	@echo "Linking..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Build successful!"

# Règle pour compiler les fichiers .c en .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	@echo "Cleaning up..."
	del /Q $(BIN_DIR)\*.o $(BIN_DIR)\$(TARGET)
	@echo "Clean complete!"

# Indiquer au make de ne pas considérer ces règles comme des fichiers
.PHONY: clean
