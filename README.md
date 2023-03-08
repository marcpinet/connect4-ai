# Connect4 AI 

## 📝 Description

A simple Connect4 made with C++ and SFML for the window.
Currently, only the Minimax with Alpha Beta Pruning is implemented. 
Maybe, in the future, I'll implement other algorithms if I want to (such as MCTS?).

## 🎥 Demo Minimax with Alpha Beta Pruning

https://user-images.githubusercontent.com/52708150/219687697-d5a2e5b7-3d84-40cd-907d-4ee64157e32d.mp4

## 💡 How to use

### 🪟 Windows

1. Clone the repository 
```bash
git clone https://github.com/marcpinet/connect4-ai
```

2. Initialize the SFML submodule

```bash
git submodule update --init --recursive
```

3. Inside the cloned repo, run

```bash
mkdir output && cmake . && cmake --build output --target Connect4_AI
```

If you've a C/C++ IDE, you should already have `cmake` and `gcc`/`g++`. If not, then install CMake [here](https://cmake.org/download/) and gcc/g++ [here](https://www.devdungeon.com/content/install-gcc-compiler-windows-msys2-cc).

3. Fin and run the .exe

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

5. Build with `cmake`.

```bash
mkdir output && cmake . && cmake --build output --target Connect4_AI
```

## 📄 Note

It will probably be easier to run the project using an IDE such as [CLion](https://www.jetbrains.com/clion/).

No cache issue.