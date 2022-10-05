# R-Type [![Build](https://github.com/TEAM-AAAAAAAAAAAAAAAA/RTYPE/actions/workflows/ci.yml/badge.svg)](https://github.com/TEAM-AAAAAAAAAAAAAAAA/RTYPE/actions/workflows/ci.yml)

This project aims to recreate the R-Type game and add a multiplayer mode to it. we had to implement a multi-threaded server and a graphical client in SFML.

## Before continuing...

This project is an EPITECH Project. If you are an EPITECH student, move out the way! Nothing to see here... The groups don't want to be involved to your -42.<br/>If you're not, no worries! You're welcome here!

### Prerequisites

To use this project, you'll need Cmake 3.17.0 Compiler, SFML-devel library and C11.

### Building program

```bash
    cmake -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
```

### Testing program

```bash
    rm -rf ./build
    cmake -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DTESTING=ON
    cmake --build ./build
    cd ./build
    ctest --ouput-on-failure
```

### Coding Style

R-Type is developed with C++. EPITECH doesn't impose any Coding Style to this but we tried to be as clean as possible.

## Authors

* **Guillaume Terrière** - [GuyomT](https://github.com/GuyomT)
* **Aurèle Nicolas** - [aurelenc](https://github.com/aurelenc)
* **Julien Hourcadette** - [Bootoyka](https://github.com/Bootoyka)
* **Constant Vigneron** - [Cavonstavant](https://github.com/Cavonstavant)
* **Emile Ettel** - [EmileEttel](https://github.com/EmileEttel)

