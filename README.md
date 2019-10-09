# Platformer

## Overview

Platformed is a 2D game. The aim of the game is to complete all available levels
and obtain points in the shortest possible time. There are many obstacles to come
across during a journey: map objects affecting players mobility or life points,
enemies and treasures. User chooses one of possible magic classes to play. 
Each class has it's own ability to fight with enemies.

## Prerequisites

- [CMake](https://cmake.org) - 3.12 or higher
- [SFML](https://www.sfml-dev.org) - 2.4.2 or higher

In order to build a project a build system is required. Examples:
- [Make](https://www.gnu.org/software/make/)
- [MSVC](https://visualstudio.microsoft.com/pl/vs/features/cplusplus/) - delivered with [Visual Studio](https://visualstudio.microsoft.com)

## Installation

1. Clone the repository (using HTTPS as in example or SSH)
```bash
$ git clone https://github.com/kyma-incubator/bullseye-showcase.git
```

2. Navigate to directory where project was downloaded
```bash
$ cd {project-directory}
```

3. Edit `SFML_ROOT` variable in `CMakeLists.txt` file, provide directory where SFML was downloaded
```bash
(...)
set (SFML_ROOT "{provide-directory-here{")
(...)
```

4. Clean project to make sure there are no files generated
```bash
$ make clean
```

5. Build project with default CMake generator
```bash
$ make build
```

Alternative: you can build project using specific generator. In this case `generator` paramter has to be provided in `Makefile` file (see more details about generators [here](https://cmake.org/cmake/help/v3.1/manual/cmake-generators.7.html#id4)) 

6. Run application
```bash
make run
```

## Configuration

After installing an application there is no configuration required. Client can be ran anytime.

## Usage

Run application using Makefile tool
```bash
$ make run
```

Popup window should appear. In main manu click `Play` option using `Enter` button, choose class (navigate using arrow buttons) and start your journey!

Control buttons:
1. run (left, right arrow keys)
2. jump (up arrow key)
3. attack (space)
