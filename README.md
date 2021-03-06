# SCC0250-CG

Assignment for the SCC0250 Computer Graphics class on ICMC - University of São Paulo during the first semester of 2021

Made by:

* Abner Eduardo Silveira Santos - NUSP 10692012
* Amanda de Moura Peres - NUSP 10734522
* Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794

Some code comes from dmdmoura's [Adven](https://github.com/dmdemoura/Adven) GBA engine and from LuisEduardoR's [GLGame](https://github.com/LuisEduardoR/GLGame) repository

The models and textures come from the game DEEP by Fellowship of the Game, it can be played at [itch.io](https://fog-icmc.itch.io/deep)


---

## How to compile and run:

### Linux:

* Install packages (assuming an Ubuntu based distribution):

```
$ sudo apt install g++ make libglfw3-dev mesa-common-dev libglew-dev libsdl2-dev
```

* To compile:

```
$ make linux
```

* To Run:

```
$ make run
```

```
$ ./(program name)
```


### Windows (using MSYS2):

* Install [MSYS2](https://www.msys2.org/)

* In MSYS2's terminal install the packages:

  - MinGW-w64 tool-chain:

```
$ pacman -S mingw-w64-x86_64-toolchain
```

  - GLFW:

```
$ pacman -S mingw-w64-x86_64-glfw
```

  - GLEW:

```
$ pacman -S mingw-w64-x86_64-glew
```

  - GLM:

```
$ pacman -S mingw-w64-x86_64-glm
```

  - SDL2:

```
$ pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image
```

* Add **C:\msys64\mingw64\bin** to **PATH** (Considering that MSYS2 was installed in **C:\msys64**)

* To compile:

```
$ mingw32-make windows
```

* To run:

```
$ mingw32-make run
```


```
$ ./(program name)
```

---

## Structure of the project:

The project code is in the **src/** directory. The game also loads **.png**, **.obj** and **.glsl** files from the **assets/** directory, keep a copy of it with any executable version of the game!

A **Makefile** is provided with the commands to compile and run this game on Windows and Linux

A breakdown of the **src/** directory and it's sub-directories is found below:

```
└─── src
    ├─── Assets/        # Code used to load assets (mainly geometry and shaders)
    ├─── Components/    # Code for components used to compose objects in the game
    ├─── Events/        # Code used to implement Events and Listeners
    ├─── Exceptions/    # Code for certain types of Exceptions
    ├─── Input/         # Code that handles player input
    ├─── Interfaces/    # Code that tries to emulate the C# concept of Interface
    ├─── Math/          # Code for mathematical concepts like Vectors and Matrixes
    ├─── Physics/       # Code for collision physics
    ├─── Rendering/     # Code for the game's renderer that interacts with OpenGL and for geometry that can be rendered
    ├─── Scene/         # Code for scenes (levels) of the game, most game logic is handled by Scene/GameScene.cpp
    ├─── Time/          # Code for controlling time and ensuring movement is not FPS based
    ├─── Utils/         # Miscellaneous code that can be useful for very specific features
    ├─── WindowSystem   # Code for handling the game window through GLFW3
    └─── main.cpp       # Main function that initializes everything needed to run the game and executes the game loop
```

---

## Instructions

**W/A/S/D:**            Walk

**Mouse**               Look around

**O:**                  Toggle wire-frame

**U/P:**                Increase/Decrease ambient light intensity

**Left/right arrows:**  Increase/Decrease FoV

**ESC:**                Free cursor and reset camera