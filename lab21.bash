#!/bin/bash

# Проверяем введена ли директория 
if [ $# != 1 ]; then
    echo "Use: $0 <directory>"
    exit 1
fi;

# Проверяем существует ли такая директория
if [ ! -d "$1" ]; then
    echo "Ошибка: $1 не директория"
    exit 1
fi;

# Обход директорий и вывод поддиректорий
for file in `find $1 -type d`
do
    realpath $file;
done

