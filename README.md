# Connect4 AI 

## 📝 Description

A simple Connect4 made with C++ and SFML for the window.
Currently, only the Minimax with Alpha Beta Pruning is implemented. 
Maybe, in the future, I'll implement other algorithms if I want to (such as MCTS?).

## 🎥 Demo Minimax with Alpha Beta Pruning

https://user-images.githubusercontent.com/52708150/218887447-573d2c01-5913-42e8-8558-aea4cd7308cf.mp4

## 💡 How to use

### 🪟 Windows (hard one)

1. Install SFML 2.5.1 [here](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip) and the corresponding MinGW build [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download)

2. Extract and put these 2 folders in something like `C:` for example (the disk root)

3. Build with `cmake`.

### 🐧 Linux / WSL

1. Install the following packages

```bash
sudo apt install libsfml-dev gdb cmake build-essential
```

2. Build with `cmake`.

## 📄 Note

It will probably be easier to run the project using an IDE such as [CLion](https://www.jetbrains.com/clion/).

No cache issue.