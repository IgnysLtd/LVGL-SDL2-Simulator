# LVGL With SDL2 Simulator

Requirements:

- [cmake version 3.10](https://cmake.org/download/)
  - download the latest version msi file extension and rn the installer it will add cmake to your system path
- [MinGW](https://winlibs.com/)
  - Download the latest or version you want, used here was 14.2.0
  - Unzip and manually add to system path
- [Make version 4.4.1](https://ftp.gnu.org/gnu/make/)
  - You are looking for `make-4.4.1.tar.gz  2023-02-26 15:06    2.2M`
  - to unzip you need to use `tar`
    - `tar -xvxf make-4.4.tar.gz -C "C:PATH\To\Folder"`
    - Manually add this to system path
- Git

## Getting Started

- `git clone --recurse-submodules https://github.com/IgnysLtd/LVGL-SDL2-Simulator.git`

## SDL2 Dependency

For simplicity we have included all the SDL2 libraries but if you want to know what we did here are the steps:

- Download link [SLD2 version 2.30.7](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.7)
- Select option `SDL2-devel-2.30.7-mingw.zip`
- unzip the package
- in directory i686_64-w64-mingw32 copy and past the `include` and `lib` folder to base directory of this project

## LVGL Configuration

What we did for you:

- Made a copy of `lvgl/lv_conf_template.h` with the name `lv_conf.h` in the base directory of this project
- Edited line 862 to include the path for the `SDL.h`
  - `#define LV_SDL_INCLUDE_PATH     <include/SDL2/SDL.h>`
- Included Fonts of certain sizes
  - `#define LV_FONT_MONTSERRAT_14 1` Line 404 of `lv_conf.h`
  - `#define LV_FONT_MONTSERRAT_24 1` Line 409 of `lv_conf.h`

## Build the Project

Commands from the base directory of the project

- `mkdir build`
- `mkdir bin`
- `cd build`
- `cmake .. -G "MinGW Makefiles"`
- `make -j8`
- `../bin/main.exe`
