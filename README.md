МГТУ им. Н.Э. Баумана Кафедра ИУ5

# Лабораторные работы по курсу "Программирование в среде WINDOWS"

> Терентьев В.О. Группа ИУ5-43Б

## Лаба 1

Составьте программу, в которой в главное окно бледно-розового цвета выводятся три концентрических эллипса с размерами 350х250, 250х150 и 150х50 пикселов. Внешний эллипс нарисуйте толстым (6-8 пиксела) черным пером, средний – синим, а внутренний – желтым. Эллипсы должны быть прозрачными. Нажатие левой клавиши – изменение толщины пера у эллипса, над которым находится курсор

## Лаба 2

Сформировать два приложения, которые открывают по одному окну. В окне 1 по щелчку левой клавиши мыши: при помощи FindWindow() найти дескриптор окна 2. Выдать сообщение об этом. Если операция неудачная, то выдать сообщение об этом. При помощи функции SendMessage() и поля WPARAM передать свой дескриптор второму окну. Выдать сообщение об этом. В окне 2: при получении сообщения WM_USER+1 (левая клавиша) нарисовать прямоуголиник (при повторном получении сообщения WM_USER+1 цвет, размер, координаты изменяются). При получении сообщения WM_USER+2 (правая клавиша) закрыть приложение 1

## Лаба 3

Составьте программу "Калькулятор 2"

## Лаба 4

Первый поток выводит в верхнюю половину окрашенного окна большой круг, кисть для заливки которого выбирается случайным образом из трех созданных заранее кистей разных цветов. Для того чтобы наглядно фиксировать моменты смены кисти, в центр круга выводится номер такта этого потока

Второй поток выводит в нижнюю половину окна цветными символами текущее время (часы, минуты и секунды), получаемое с помощью функции GetLocalTime()

## Отчет по лабам

Отчет: [pdf](/%D0%9E%D1%82%D1%87%D0%B5%D1%82%20%D0%A2%D0%B5%D1%80%D0%B5%D0%BD%D1%82%D1%8C%D0%B5%D0%B2%20%D0%98%D0%A35-43.pdf)
