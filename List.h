//
// Created by Anastasia Chichagova on 08.06.2023.
//

#ifndef AISD_LIST_H
#define AISD_LIST_H


template <class T>
struct Node{
    T val; // данные
    Node* next; // следующий элемент
};


template <class T>
class List {
private:
    Node<T>* p_top;
    int size;
public:
    List(){
        p_top = nullptr;
        size = 0;
    }
    bool is_empty();
    void push_front(T _val);
    void pop_front();
    T begin();
    int get_size();
};


template<class T>
bool List<T>::is_empty() {
    return p_top == nullptr;
}

template<class T>
void List<T>::push_front(T _val) {
    Node<T>* p = new Node<T>;
    p -> val = _val;
    p -> next = p_top;
    p_top = p;

    ++size;
}

template<class T>
void List<T>::pop_front() {
    if (is_empty())
        return;
    Node<T>* p = p_top;
    p_top = p_top -> next;
    delete p;
    --size;
}

template<class T>
T List<T>::begin() {
    return p_top -> val;
}

template<class T>
int List<T>::get_size() {
    return size;
}


#endif //AISD_LIST_H
