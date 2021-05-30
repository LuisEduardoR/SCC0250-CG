CC = g++ -std=c++17

SRC = ./src/*.cpp
OUTPUT = Trabalho-CG.exe

LINKER_LINUX = -lglfw -lGL -lGLEW -lm
LINKER_WINDOWS = -lglfw3 -lglew32 -lopengl32

RELEASE_FLAGS = -O3
DEBUG_FLAGS = -g

linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(RELEASE_FLAGS) -o $(OUTPUT)

windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(RELEASE_FLAGS) -o $(OUTPUT)

debug-linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(DEBUG_FLAGS) -o $(OUTPUT)

debug-windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(DEBUG_FLAGS) -o $(OUTPUT)
	
run:
	./$(OUTPUT)