# Connect4 AI 

## 📝 Description

A simple Connect4 made with C++ and SFML for the window.
Currently, only the Minimax with Alpha Beta Pruning is implemented. 
Maybe, in the future, I'll implement other algorithms if I want to (such as MCTS?).

## 🎥 Demo Minimax with Alpha Beta Pruning

https://user-images.githubusercontent.com/52708150/219687697-d5a2e5b7-3d84-40cd-907d-4ee64157e32d.mp4

## 💡 How to use

### 🪟 Windows

If you've a C/C++ IDE, you should already have `cmake` and `gcc`/`g++`. If not, then install CMake [here](https://cmake.org/download/) and gcc/g++ [here](https://www.devdungeon.com/content/install-gcc-compiler-windows-msys2-cc).

1. Clone the repository 
```bash
git clone https://github.com/marcpinet/connect4-ai
```

2. Initialize the SFML submodule

```bash
git submodule update --init --recursive
```

3. Build with CMake

```bash
cmake -S . -B output -DCMAKE_BUILD_TYPE=Release -G"MinGW Makefiles"
```

4. Build the project using make inside the newly created output folder

```bash
cd output && make
```

5. Run the `.exe`

### 🐧 Linux / WSL

1. Run the holy command

```bash
sudo apt-get update
```

2. Install the following packages

```bash
sudo apt install libsfml-dev gdb cmake build-essential libvorbis-dev libopenal-dev freetype2-demos libudev-dev libx11-dev libxrandr-dev
```

3. Clone the repository

```bash
git clone https://github.com/marcpinet/connect4-ai
```

4. Initialize the SFML submodule

```bash
git submodule update --init --recursive
```

5. Build with CMake

```bash
cmake -S . -B output -DCMAKE_BUILD_TYPE=Release
```

6. Build the project using make inside the newly created output folder

```bash
cd output && cp -r ../assets assets && make
```

7. Run the file!

```bash
chmod u+x Connect4_AI && ./Connect4_AI
```

## 📄 Note

On Windows, it will probably be easier to run the project using an IDE such as [CLion](https://www.jetbrains.com/clion/).

No cache issue.