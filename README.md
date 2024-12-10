# Лабораторные работы по дискретному анализу

## Структура репозитория

```
.
├── course-project-FFT
│   ├── makefile
│   ├── minimp3
│   ├── README.md
│   └── solution.cpp
├── labx-*
│   ├── makefile
│   ├── README.md
│   └── solution.cpp
├── README.md
└── reports
    ├── labx
    │   ├── report.pdf
    │   ├── report.tex
    │   └── src
    │       ├── benchmark.tex
    │       ├── literature.tex
    │       ├── problem.tex
    │       ├── src.tex
    │       ├── thoughts.tex
    │       └── titlepage.tex
    └── styles
        └── log-style.sty
```

- labx-* - исходный код лабораторной работы + makefile для более удобной работы с задачей;

- course-project-FFT - файлы кода КП с субмодулем minimp3;

- reports - отчеты в формате TeX без дополнительных файлов (логов и подобных).

## 1 семестр

1. Поразрядная сортировка (объекты вида "ключ-значение": строка - uint64_t);

2. PATRICIA trie

3. Отладка и тестирование (диагностика) 

4. Алгоритм Ахо-Корасик

## 2 семестр

5. Поиск в известном тексте неизвестном заранее образцов (построение суффиксного дерева по алгоритму Укконена)

6. Длинная арифметика (-)

7. Динамическое программирование: палиндромы

8. Жадный алгоритм: откорм бычков

9. Графы: поиск компонент связности

10. Курсовой проект (быстрое преобразование Фурье/аудиопоиск)