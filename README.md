# Stochastic rounding emulator

## Description

В данный момент эмулятор представляет собой header-only библиотеку с реализованными обертками над числовыми типами данных, позволяющими производить вычисления в 
fixed point (https://royalsocietypublishing.org/doi/pdf/10.1098/rsta.2019.0052) и floating point (http://eprints.maths.manchester.ac.uk/2758/1/fami20.pdf), используя стохастическое округление

## Features

На данный момент классы Fixed и FixedSR обладают следующими фичами:

- compile time проверка типов в конструкторах (можно создать Fixed либо из любого floating point типа, с указанием, сколько битов отдаем под хранение дробной части, либо из любого integer типа, которым шаблонизируем класс)

- compile time проверка возможности приведения класса к типу (компиляция упадет, если будем делать static_cast к не floating point типу)

- стохастическое округление для типов с фиксированной и плавающей точкой;

- Частичная функциональность Fixed и FixedSR  (см. TODO)

- Для проведения экспериментов написан интегратор Рунге-Кутты 4 порядка, который в том числе может поддерживать Fixed, FixedSR, FloatSR

- Реализован интегратор методом Эйлера

## TODO

- Проверка на переполнение в типах с фиксированной точкой
- tests & CI (последнее лучше наверное прикрутить при переходе в gitlab)
- больше экспериментов

## Build
`mkdir build` 

`cd build` 

`cmake .. & make`

Запуск эксперимента:
`./experiment{number: 1,2,3,4}`

Немного примеров использования класса fixed:
`./example`

Пример использования интегратора:
`./integrator_example`

## Tests
`./test_main`
