# SCC0250-CG

Assignment for the SCC0250 Computer Graphics class on ICMC - University of São Paulo during the first semester of 2021

Made by:

* Abner Eduardo Silveira Santos - NUSP 10692012
* Amanda de Moura Peres - NUSP 10734522
* Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794

Some code comes from dmdmoura's [Adven](https://github.com/dmdemoura/Adven) GBA engine and from LuisEduardoR's [GLGame](https://github.com/LuisEduardoR/GLGame) repository


## How to compile and run:

---

### Linux:

* Install packages:

    > g++ make libglfw3-dev mesa-common-dev libglew-dev

* To compile:

    > make linux

* To Run:

    > make run
    
    or

    > ./(program name)

---

### Windows (using MSYS2):

* Install [MSYS2](https://www.msys2.org/)

* In MSYS2's terminal install the packages:

  - MinGW-w64 tool-chain:

      > pacman -S mingw-w64-x86_64-toolchain

  - GLFW:

      > pacman -S mingw-w64-x86_64-glfw

  - GLEW:

      > pacman -S mingw-w64-x86_64-glew

  - GLM:

      > pacman -S mingw-w64-x86_64-glm

* Add **C:\msys64\mingw64\bin** to **PATH** (Considering that MSYS2 was installed in **C:\msys64**)

* To compile:

    > mingw32-make windows

* To run:

    > make run
    
    or

    > ./(program name)

---

Remember to keep the **assets** folder together with the executable