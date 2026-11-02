# Запуск программы

Из корня репозитория. Требуется компилятор C++ с поддержкой C++17.

Windows:


### Windows (Git Bash)

Компиляция программы:

```bash
g++ -std=c++17 -Wall -Wextra src/DynamicArray.cpp src/main.cpp -o main.exe
```

Запуск программы:

```bash
./main.exe
```


Linux/macOS:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp -o main
./main
```
