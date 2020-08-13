![CubicSquareCreft](/showcase/Banner.png?raw=true "CubicSquareCreft")

<p align="center">
  <a href="https://github.com/FelipeCarlin/CubicSquareCreft/releases">Releases</a> |
  <a href="#screenshots">Screenshots</a> |
  <a href="#features">Features</a> |
  <a href="https://github.com/FelipeCarlin/CubicSquareCreft/wiki">Wiki</a> |
  <a href="https://github.com/FelipeCarlin/CubicSquareCreft/tree/master/CONTRIBUTING.md">Contributing</a>
<br/>
<br/>
<br/>
<a href="https://github.com/FelipeCarlin/CubicSquareCreft/releases"><img alt="platforms" src="https://img.shields.io/badge/platforms-Windows-blue?style=flat-square"/></a>
<a href="https://github.com/FelipeCarlin/CubicSquareCreft/releases"><img alt="release" src="https://img.shields.io/github/v/release/FelipeCarlin/CubicSquareCreft?style=flat-square"/></a>
<a href="https://github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft"><img alt="size" src="https://img.shields.io/github/repo-size/FelipeCarlin/CubicSquareCreft?style=flat-square"/></a>
<br/>

# 1. What is CubicSquareCreft

## 1.1. Description

CubicSquareCreft is a voxel game, focused on playability and being intuitive. The game is inspired in the popular game [Minecraft](https://www.minecraft.net).

CSC objectives are:

* Intuitiveness
* Fun-ness
* Cepibolla

## 1.2 How is structured

The game is in the [cubicsquarecreft](https://www.github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft) folder, inside is a folder with the [source](https://www.github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft/code), [data](https://www.github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft/data) that the game uses and [miscellaneous](https://www.github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft/misc) files.

<br/>

# 2. A story through time

## 2.1. Context

The origin of the project comes from boredom, the need of practice and a lot of coffee.

## 2.2 What I want to achieve

In reality the game aims:

* Not be complete garbage
* Be a good OpenGL practice
* Have documentation for developers and end-users
* Be a practice for dealing with a mid-term project

<br/>

<span name="features"></span>

# 3. Features

## 3.1. Implemented

Things that are no longer in the TODO list:

* None

## 3.2 TODO list

A list of stuff that should be worked on:

* (insert something later)

<br/>

# 4. Building

To build the game, you will need to have [Visual Studio 2019](https://visualstudio.microsoft.com/vs/features/cplusplus/) installed.
First download the source:

```bash
git clone --recursive https://github.com/FelipeCarlin/CubicSquareCreft
cd CubicSquareCreft
```

Now run `build.bat` inside the [scripts](https://github.com/FelipeCarlin/CubicSquareCreft/tree/master/scripts) folder. After that the executable should be in a folder called `build` in the root folder.
*Note: The files required for the game to work are in [cubicsquarecreft/data](https://github.com/FelipeCarlin/CubicSquareCreft/tree/master/cubicsquarecreft/data), so in order to work, the EXE file must me copied into this directory, this will be fixed in the future.

<br/>

# 5. Details

## 5.1 Software

* IDE: [GNU Emacs](https://www.gnu.org/software/emacs/)(I know, its old, but I'm trying IDEs)
* Compiler: [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) The Microsoft C/C++ Compiler

## 5.2. Dependencies

Right now, the game has 0 dependencies :)

## 5.3 Coding convention

* Interfaces starts by `I`
* Abstracts starts by `A`
* Class names: `UpperCamelCase`
* Public member variables: `lowerCamelCase`
* Private member variables: `m_lowerCamelCase`
* Public static variables: `UpperCamelCase`
* Private static variables: `_CAPS_LOCK_WITH_UNDERSCORES`
* Function/Method arguments: `lowerCamelCase`
* Function/Method names: `UpperCamelCase`
* Class member variables are located on file bottom
* Comment your functions, enums, classes, methods
  Some coding convention could have been forget while redacting this document, so always refer to the existing code base!

<br/>

<span name="screenshots"></span>

# 6. Screenshots

There is no screenshots, yet!

