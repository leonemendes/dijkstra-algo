#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Libraries
#include <iostream>

// Library headerfile
#include "defs.hpp"

// Using from other namespaces
using std::cout;
using std::endl;

namespace ipc
{
    namespace detail
    {
        template<class T>
        class Node
        {
            public:
            T* data;
            
            Node<T>* prev;
            Node<T>* next;
        };      
    }

    template <class T>
    class LinkedList
    {
        private:
        detail::Node<T>* head;

        public:
        LinkedList():head(nullptr)
        {
            if (DebugLevel > 3) cout << "LinkedList Class constructor called." << endl;
        }


        detail::Node<T>* h(){ return this->head; }

        void setHeadPointer(detail::Node<T>* n){ this->head = n; }

        detail::Node<T>* newNode(T* n, detail::Node<T>* prev = nullptr, detail::Node<T>* next = nullptr)
        {
            ipc::detail::Node<T>* result = new ipc::detail::Node<T>{.data = n, .prev = prev, .next = next};

            return result;
        }
        
        ReturnStatus prependNode(detail::Node<T>* n)
        {
            n->next = this->head;
            if (this->head != nullptr) this->head->prev = n;
            this->setHeadPointer(n);

            if (DebugLevel > 3) cout << "Node added." << endl;

            return ReturnSuccess;
        }

        ReturnStatus prepend(T* n)
        {
            detail::Node<T>* tmp = this->newNode(n);

            return ipc::LinkedList<T>::prependNode(tmp);
        }

        detail::Node<T>* popHead()
        {
            if(this->head == nullptr) return nullptr;
            else
            {
                detail::Node<T>* tmp = this->head;
                this->setHeadPointer(this->head->next);
                
                return tmp;
            }
        }

        int size()
        {
            if (DebugLevel > 3) cout << "Size function called." << endl;
            int size = 0;

            detail::Node<T>* current = this->head;

            while(current != nullptr)
            {
                size++;
                current = current->next;
            } 
            if (DebugLevel > 3) cout << "Size:" << size << endl;

            return size;
        }

        ~LinkedList()
        {
            if (DebugLevel > 3) cout << "LinkedList Class destructor called." << endl;

            ipc::detail::Node<T>* current = this->head;

            while(current != nullptr)
            {
                current = current->next;
                delete this->head;
                this->head = current;
            }
        }
    };
}

#endif