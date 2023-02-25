Курсовой проект был выполнен совместно с <a href="https://github.com/Yargachin-wye">Yargachin</a>

В рамках курсового проекта было необходимо реализовать обработку команд (CU, ALU) и трансляторы с языков Simple Basic и Simple Assembler.

Файл, содержащий программу на Simple Basic, преобразуется в файл с кодом Simple Assembler. Затем Simple Assembler-файл транслируется в бинарный формат. После чего бинарный файл может быть загружен в оперативную память Simple Computer.

Ниже представлен пример трансляций (Simple Basic -> Simple Assembler) и (Simple Assembler -> бинарный формат):

./sbt *.sb *.sa

./sat *.sa *.o
