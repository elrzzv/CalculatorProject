# Calculator

Учебный проект - калькулятор с поддержкой .dll плагинов.

## Возможности

- **Арифметические операторы**: `+`, `-`, `*`, `/`, `^` (степень)
- **Встроенные функции**: `sin`, `cos`, `ln`, `abs`, `sqrt`, `exp`
- **Константы**: `PI`, `E`
- **Скобки**: полная поддержка вложенных выражений
- **Унарный минус**: корректная обработка отрицательных чисел
- **Plugin System**: загрузка функций и операторов из .dll файлов

## Архитектура

```
├── src/
│   ├── main.cpp              - точка входа
│   ├── calculator/           - ядро калькулятора
│   │   ├── calculator.cpp/h  - основной класс
│   │   └── plugin_loader.cpp/h - загрузчик плагинов
│   └── utils/
│       └── expression_parser.cpp/h - парсер выражений (алгоритм Shunting-yard)
├── plugins/                  - .dll плагины
│   ├── funcsin.cpp, funccos.cpp, ...
│   └── funcdeg.cpp          - оператор "^"
└── tests/                    - Google Tests
```

Парсер использует алгоритм **Shunting-yard** для преобразования инфиксной записи в обратную польскую нотацию (RPN) с последующим вычислением.

## Сборка

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Debug
```

После сборки:
- Исполняемый файл: `build/output/calc.exe`
- Плагины (.dll): `build/output/*.dll`

## Запуск

```bash
./build/output/calc.exe
```

Пример сессии:
```
======== Calculator ========
Available operations: +, -, /, *, ^
Available functions: sin, cos, ln, abs, sqrt, exp, deg
Available constants: PI, E
Enter an expression or 'exit' to exit
============================
> 2 + 3 * 4
> 14
> sin(PI/2)
> 1
> 2 ^ 3 ^ 2
> 512
> exit
```

## Тесты

```bash
cd build
ctest --output-on-failure
```

## Добавление плагинов

### Функция (unary):

```cpp
extern "C" {
    __declspec(dllexport) double execute(double x) {
        return std::sin(x);
    }
    
    __declspec(dllexport) const char* get_function_name() {
        return "sin";
    }
}
```

### Оператор (binary):

```cpp
extern "C" {
    __declspec(dllexport) double execute_operator(double a, double b) {
        return std::pow(a, b);
    }
    
    __declspec(dllexport) const char* get_operator_name() {
        return "^";
    }
    
    __declspec(dllexport) int get_priority() {
        return 3;
    }
    
    __declspec(dllexport) bool is_right_associative() {
        return true;
    }
}
```

Добавьте новый `.cpp` файл в директорию `plugins/` - CMake автоматически включит его в сборку.
