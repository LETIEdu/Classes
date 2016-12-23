#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

class Array
{
    // Секция public, доступна всем
public:
    // Конструктор по умолчанию
    Array();
    // Конструктор принимающий размер,
    // ключевое слово explicit объясняется
    // в main.cpp
    explicit Array(int s);
    // Конструктор копирования
    Array(const Array &copy);
    // Деструктор
    ~Array();
    // Функция возвращающая размер массива.
    // Слово const означает что функция не
    // модифицирует данные класса и может
    // быть вызвана с константным объектом
    // Указание кода функции в объявлении класса
    // также неявно добавляет ключевое слово
    // inline.
    int getSize() const {return size;}
    // Функция для обращения к элементу массива
    // с проверкой границ
    int &at(size_t i);
    // Оператор [] для обращения к элементу
    // без проверки границ
    int &operator [](size_t i) {return p[i];}
    // Оператор присваивания
    Array &operator=(const Array &a);

    // Оператор вывода в поток, объявлен
    // другом класса. Функции и классы друзья
    // имею доступ к приватным данным класса
    friend ostream &operator <<(ostream &stream,
                                const Array &a);
    // Секция private доступна только методам класса
    // и друзьям
private:
    int *p;
    size_t size;
};

#endif // ARRAY_H