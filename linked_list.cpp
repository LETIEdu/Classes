#include <iostream>
#include "linked_list.h"

using namespace std;

// Конструктор узла (элемента) связного списка
// Устанавливаем корректные указатели (чтобы точно не было в них мусора) и присваиваем данные узлу
LinkedListElem::LinkedListElem( uint32_t data )
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

// Конструктор связного списка
// Установка корректных указателей и устновка размера списка в ноль
LinkedList::LinkedList( void )
{
    this->head = nullptr;
    this->tail = nullptr;

    this->size = 0;
}

// Деструктор связного списка
// Проход по всему списку и очищение выделенной для каждого узла памяти
// Добавлен указатель на следующий узел, так как при очистке нынешнего узла адрес следующего будет потерян
LinkedList::~LinkedList()
{
    LinkedListElem *current_node  = nullptr;
    LinkedListElem *next_node     = nullptr;

    for ( current_node = this->head;
          current_node != nullptr;
          current_node = next_node)
    {
        next_node = current_node->next;

        delete current_node;
    }

    this->head = this->tail = nullptr;
}

// Получение адреса первого узла связного списка
LinkedListElemPtr LinkedList::get_head()
{
    return this->head;
}

// Функция добавления нового узла перед переданным в качестве аргумента узлом
// Данная функция создаст 2й по счету узел, если в качестве аргумента передан третий
void LinkedList::insert_before( LinkedListElemPtr node, uint32_t data )
{
    LinkedListElem *new_node = new LinkedListElem( data );

    new_node->next = node;
    new_node->prev = node->prev;

    if ( node->prev == nullptr ) {
        this->head          = new_node;
    } else {
        node->prev->next    = new_node;
        node->prev          = new_node;
    }

    this->size++;

    cout << "Element " << new_node->data << " is added before " << node->data << " to array" << endl;
}

// Функция добавления нового узла после переданного в качестве аргумента узла
// Данная функция создаст 4й по счету узел, если в качестве аргумента передан третий
void LinkedList::insert_after( LinkedListElemPtr node, uint32_t data )
{
    LinkedListElem *new_node = new LinkedListElem( data );

    new_node->next = node->next;
    new_node->prev = node;

    if ( node->next == nullptr ) {
        this->tail          = new_node;
    } else {
        node->next->prev    = new_node;
        node->next          = new_node;
    }

    this->size++;

    cout << "Element " << new_node->data << " is added after " << node->data << " to array" << endl;
}

// Функция получения узла (поиска) по переданным данным (первый аргумент)
// Второй аргумент опционален
//      Если он не передан - будет произведен поиск с начала списка и возвращен первый узел, имеющий идентичные данные
//      Если второй аргумент передан - поиск производится со следующего узла и возвращен узел, имеющий идентичные данные
// При отсутствии узла с идентичными данными - будет возвращен нулевой указатель
LinkedListElemPtr LinkedList::get_next_elem_with_data( uint32_t search_data, LinkedListElemPtr search_from_node )
{
    LinkedListElem *current_node  = nullptr;

    if ( search_from_node == nullptr )
        current_node = this->head;
    else
        current_node = search_from_node->next;

    for ( ; current_node != nullptr; current_node = current_node->next )
    {
        if ( search_data == current_node->data )
        {
            cout << "Element with data " << current_node->data << " is found" << endl;
            return current_node;
        }
    }

    cout << "Element with data " << search_data << " not found" << endl;
    return nullptr;
}

// Функция удаления узла (вырезки) из связного списка
// В качестве аргумента передается указатель на узел, который требуется удалить
void LinkedList::remove( LinkedListElemPtr node )
{
    if ( node->prev != nullptr )
        node->prev->next = node->next;
    else
        this->head = node->next;

    if ( node->next != nullptr )
        node->next->prev = node->prev;
    else
        this->tail = node->prev;

    cout << "Element " << node->data << " is deleted from array" << endl;

    delete node;
}

// Функция добавления нового узла в конец списка
void LinkedList::push_back( uint32_t data )
{
    LinkedListElem *new_node  = new LinkedListElem( data );

    if ( this->head == nullptr ) {
        this->head          = new_node;
    } else {
        this->tail->next    = new_node;
    }

    new_node->prev  = this->tail;
    this->tail      = new_node;
    this->size++;

    cout << "Element " << new_node->data << " is added to array" << endl;
}

// Перегруженный оператор вывода элементов связного списка
// Перегрузка используется для упрощения вывода полного списка по элементам
std::ostream& operator<<(std::ostream& out, LinkedList& f)
{
    LinkedListElem *current_node  = nullptr;
    int i_node       = 0;

    for ( current_node = f.get_head();
          current_node != nullptr;
          current_node = current_node->next)
    {
        out << i_node << ") Element with value: " << current_node->data << endl;
        i_node++;
    }

    return out;
}

int main()
{
    LinkedList my_array;

    for ( int i = 0; i < 5; i++ ) {
        my_array.push_back( i );
    }

    for ( int i = 1; i < 10; i++ ) {
        my_array.push_back( i );
    }

    // Получить первый элемент с данными == 3
    LinkedListElemPtr node = my_array.get_next_elem_with_data( 3 );

    if ( node == nullptr )
        cout << "Element is not found";

    // Вставить новый элемент с данными после <node>
    my_array.insert_after( node, 10 );
    // Вставить новый элемент с данными перед <node>
    my_array.insert_before( node, 20 );

    // Получить первый элемент после указанного <node> с данными == 5
    LinkedListElemPtr node_next = my_array.get_next_elem_with_data( 5, node );

    // Проверка на нулевой указатель (эффект такой же как и на строке 190)
    if ( !node_next )
        cout << "Element is not found";

    // Удалить элемент из списка
    my_array.remove( node );

    // Вставить новый элемент с данными после <node>
    my_array.insert_after( node_next, 30 );
    // Вставить новый элемент с данными перед <node>
    my_array.insert_before( node_next, 40 );

    // Удалить элемент из списка
    my_array.remove( node_next );

    // Вывод списка в cout
    cout << my_array << endl;

    return 0;
}
