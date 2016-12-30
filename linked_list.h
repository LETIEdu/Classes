#ifndef MAIN_H
#define MAIN_H

struct LinkedListElem
{
    uint32_t            data;
    LinkedListElem      *next;
    LinkedListElem      *prev;

    LinkedListElem( uint32_t data );
};

typedef LinkedListElem * LinkedListElemPtr;

class LinkedList
{
private:
    int                 size;
    LinkedListElemPtr   head;
    LinkedListElemPtr   tail;

public:
    LinkedList( void );
    ~LinkedList( void );
    LinkedListElemPtr get_head();
    void insert_before(LinkedListElemPtr node, uint32_t data);
    void insert_after(LinkedListElemPtr node, uint32_t data);
    LinkedListElemPtr get_next_elem_with_data(uint32_t search_data, LinkedListElemPtr search_from_node = nullptr);
    void remove(LinkedListElemPtr node);
    void push_back(uint32_t data);
};

#endif // MAIN_H
