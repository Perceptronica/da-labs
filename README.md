## Лабораторные работы по дискретному анализу ##

|№ ЛР|Тема|Вариант|Решение|Отчет|
|:---:|:---:|:---:|:---:|:---:|
| <nobr> 1 </nobr> | <nobr> Сортировки за линейное время </nobr> | </nobr> 5-3: MD5-суммы - числа от 0 до 2^64 </nobr> | </nobr> [Решение](/lab1-radix-sort/main.cpp) </nobr> | </nobr> [Отчет](/reports/lab1/report.pdf) </nobr> |
| <nobr> 2 </nobr> | <nobr> Сбалансированные деревья </nobr> | </nobr> 3: PATRICIA </nobr> | </nobr> [Решение](/lab2-patricia/solution.cpp) </nobr> | </nobr> [Отчет](/reports/lab2/report.pdf) </nobr> |
| <nobr> 3 </nobr> | <nobr> Профилирование </nobr> | </nobr> - </nobr> | </nobr> - </nobr> | </nobr> [Отчет](/reports/lab3/report.pdf) </nobr> |
| <nobr> 4 </nobr> | <nobr> Строковые алгоритмы </nobr> | </nobr> 5-2: Ахо-Корасик на числах </nobr> | </nobr> - </nobr> | </nobr> - </nobr> |
| <nobr> 5 </nobr> | <nobr> Суффиксные деревья </nobr> | </nobr> 1: Поиск в известном тексте неизвестных заранее образцов </nobr> | </nobr> [Решение](/lab5-suffix-tree/solution.cpp) </nobr> | </nobr> - </nobr> |
| <nobr> 7 </nobr> | <nobr> Динамическое программирование </nobr> | </nobr> 6: Палиндромы </nobr> | </nobr> [Решение](/lab7-dp/solution.cpp) </nobr> | </nobr> [Отчет](/reports/lab7/report.pdf) </nobr> |
| <nobr> 8 </nobr> | <nobr> Жадные алгоритмы </nobr> | </nobr> 4: Откорм бычков </nobr> | </nobr> [Решение](/lab8-greedy/solution.cpp) </nobr> | </nobr> [Отчет](/reports/lab8/report.pdf) </nobr> |
| <nobr> 9 </nobr> | <nobr> Графы </nobr> | </nobr> 3: Поиск компонент связности </nobr> | </nobr> [Решение](/lab9-graphs/solution.cpp) </nobr> | </nobr> [Отчет](/reports/lab9/report.pdf) </nobr> |
| <nobr> КП </nobr> | <nobr> Курсовой проект </nobr> | </nobr> Быстрое преобразование Фурье </nobr> | </nobr> [Решение](/course-project-FFT/) </nobr> | </nobr> - </nobr> |

### Структура репозитория ###

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
