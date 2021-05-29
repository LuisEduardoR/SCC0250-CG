SRC = ./src/*.cpp
OUTPUT = EP3-Piramide.exe

LINKER_LINUX = -lglfw -lGL -lGLEW -lm
LINKER_WINDOWS = -lglfw3 -lglew32 -lopengl32

RELEASE_FLAGS = -O3
DEBUG_FLAGS = -g

linux:
	g++ $(SRC) $(LINKER_LINUX) $(RELEASE_FLAGS) -o $(OUTPUT)

windows:
	g++ $(SRC) $(LINKER_WINDOWS) $(RELEASE_FLAGS) -o $(OUTPUT)

debug-linux:
	g++ $(SRC) $(LINKER_LINUX) $(DEBUG_FLAGS) -o $(OUTPUT)

debug-windows:
	g++ $(SRC) $(LINKER_WINDOWS) $(DEBUG_FLAGS) -o $(OUTPUT)
	
run:
	./$(OUTPUT)