#include "array.h"
#include <cassert>
#include <memory.h>

/*
 * После : идёт список инициализации в виде
 * имяПеременной(значение),
 * имяМассива{значение, значение}
 */
Array::Array() :
    p(nullptr),
    size(0)
{
}

Array::Array(int s)
{
    cout << "constructor " << s << endl;
    p = new int[s];
    size = s;
}

Array::Array(const Array &copy) :
    p(nullptr),
    size(0)
{
    cout << "Copy constructor" << endl;
    operator =(copy);
}

Array::~Array()
{
    cout << "destructor" << endl;
    if(p != nullptr)
    {
        delete[] p;
    }
}

int &Array::at(size_t i)
{
    // Проверка индекса с помощью макроса
    // assert. В случае false в скобках
    // программа завершается с сообщением
    // указывающем файл, номер строки и
    // содержимое assert
    // Похожим образом в OpenCV проверяется,
    // например, равенство количества каналов
    // двух изображений
    assert(i < size);

    return p[i];
}

Array &Array::operator=(const Array &a)
{
    cout << "Assigment operator" << endl;
    /*
     * Проверка на присваивание себя
     * самому себе
     * this - указатель на объект с
     * которым была вызвана функция
     * Пример:
     * Object obj;
     * obj.func();
     * this в вызове obj.func() будет
     * указателем на obj
     */
    if(this == &a) return *this;
    if(p != nullptr)
    {
        delete[] p;
    }
    p = new int[a.size];
    size = a.size;
    // Копирование данных из одного
    // массива в другой
    memcpy(p, a.p, size * sizeof(int));

    return *this;
}

// Оператор вывода в поток, не является членом класса
// Array, но является его другом, поэтому может
// обращаться к закрытым членам класса
ostream &operator <<(ostream &stream, const Array &a)
{
    // Просто выводим по очереди все элементы массива
    // в строчку
    for(size_t i = 0; i < a.size - 1; ++i)
    {
        stream << a.p[i] << " ";
    }
    stream << a.p[a.size - 1];

    return stream;
}
