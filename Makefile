# C compiler to be used
CC = g++ -std=c++17

# Source code of the program
#	- Source code directory
SRC_DIR = ./src
#	- Sub-directories (leave blank if there's a directory with only .hpp)
SRC_ASSETS			= $(SRC_DIR)/Assets/*.cpp
SRC_COMPONENTS		= $(SRC_DIR)/Components/*.cpp
SRC_EVENTS			= #$(SRC_DIR)/Events/*.cpp
SRC_EXCEPTIONS		= $(SRC_DIR)/Exceptions/*.cpp
SRC_INPUT			= $(SRC_DIR)/Input/*.cpp
SRC_INTERFACES		= #$(SRC_DIR)/Interfaces/*.cpp
SRC_MATH			= $(SRC_DIR)/Math/*.cpp
SRC_PHYSICS			= $(SRC_DIR)/Physics/*.cpp
SRC_RENDERING		= $(SRC_DIR)/Rendering/*.cpp
SRC_SCENE			= $(SRC_DIR)/Scene/*.cpp
SRC_TIME			= $(SRC_DIR)/Time/*.cpp
SRC_UTILS			= #$(SRC_DIR)/Utils/*.cpp
SRC_WINDOWSYSTEM	= $(SRC_DIR)/WindowSystem/*.cpp
#	- Complete source code
SRC = ./src/*.cpp $(SRC_ASSETS) $(SRC_COMPONENTS) $(SRC_EVENTS) $(SRC_EXCEPTIONS) $(SRC_INPUT) $(SRC_INTERFACES) $(SRC_MATH) $(SRC_PHYSICS) $(SRC_RENDERING) $(SRC_SCENE) $(SRC_TIME) $(SRC_UTILS) $(SRC_WINDOWSYSTEM)

# Name of the output program
OUTPUT = Trabalho-CG.exe

# Linker arguments
LINKER_LINUX = -lglfw -lGL -lGLEW -lm -lSDL2 -lSDL2_image
LINKER_WINDOWS = -lglfw3 -lglew32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32

# Compilation flags
RELEASE_FLAGS = -O3 -U _GNU_SOURCE
DEBUG_FLAGS = -g -U _GNU_SOURCE

# Compile program in Linux using release mode
linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(RELEASE_FLAGS) -o $(OUTPUT)

# Compile program in Windows using release mode
windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(RELEASE_FLAGS) -o $(OUTPUT)

# Compile program in Linux using debug mode
debug-linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(DEBUG_FLAGS) -o $(OUTPUT)

# Compile program in Windows using debug mode
debug-windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(DEBUG_FLAGS) -o $(OUTPUT)

# Run the program (remember to compile first)
run:
	./$(OUTPUT)
