#pragma once

#include <utility>     // provides std::swap

namespace dsa::list {

/// circularly linked list
template <typename T>
class CircularlyLinkedList {
    private:
        class Node {
            public:
                Node* next;    
                T elem;
                Node(const T& element, Node* nxt = nullptr) 
                : elem{element}, next{nxt} {}
        };
        int sz{0};
        Node* tail{nullptr};

    public:
        // ToDo: Constructs an empty list
        CircularlyLinkedList() : sz{0}, tail{nullptr} {}

        int size() const {
            return sz;
        }
    
        bool empty() const {
            return sz == 0;
        }

        T& front() {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return tail->next->elem;
        }

        const T& front() const {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return tail->next->elem;
        }

        T& back() {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return tail->elem;
        }

        const T& back() const {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return tail->elem;
        }

        void push_front(const T& elem) {
            if (sz == 0) {
                tail = new Node(elem);
                tail->next = tail;
            } else {
                Node* new_node = new Node(elem, tail->next);
                tail->next = new_node;
            }
            sz++;
        }

        void push_back(const T& elem) {
            if(empty()) {
                tail = new Node(elem);
                tail->next = tail;
            }
            else {
                Node* new_node = new Node(elem, tail->next);
                tail->next = new_node;
                tail=new_node;
            }
            sz++;
        }

        void pop_front() {
            if(empty()) {
                return;
            }
            
            Node* prev_head = tail->next;

            if (prev_head == tail)
                tail = nullptr;
            else{
                tail->next = prev_head->next;
            }
            delete prev_head;
            sz--;
        }


        void rotate() {
            if (tail != nullptr)
                tail = tail->next;
        }
    
        // Splits the current even-sized circular list into two equal-sized circular lists A and B
        // After splitting, A and B become the two halves (preserving original order), and the original list becomes empty. 
        //If the size is odd, throw std::logic_error
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            if (sz == 0) {     // nothing to split
                return;
            }
            if (sz % 2 != 0) {
                throw std::logic_error("Cant split list evenly");
            }

            int halfsize = sz/2;
            Node* head_A = this->tail->next;
            
            Node* tail_A = head_A;
            for (int i = 0; i < halfsize - 1; ++i) {
                tail_A = tail_A->next;
            }

            Node* head_B = tail_A->next;
            Node* tail_B = this->tail;

            //circular
            tail_A->next = head_A;
            A.tail = tail_A;
            A.sz = halfsize;

            tail_B->next = head_B;
            B.tail = tail_B;
            B.sz = halfsize;

            this->tail = nullptr;
            this->sz = 0;
        }

    private:
        // presumes valid empty list when called
        void clone(const CircularlyLinkedList& other) {
            if (other.empty()) 
                return;

            Node* current = other.tail->next;
            for (int i = 0; i < other.sz; ++i) {
                push_back(current->elem);
                current = current->next;
            }
        }

    public:
        // non-member function to swap two lists
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
            using std::swap;
            swap(a.tail, b.tail);
            swap(a.sz, b.sz);
        }

        // Resets the list to empty
        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        // Copy constructor
        CircularlyLinkedList(const CircularlyLinkedList& other) : sz{0}, tail{nullptr}  {     
                clone(other);
        }

        // Copy assignment
        CircularlyLinkedList& operator=(const CircularlyLinkedList& other) {
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }

        // Move constructor
        CircularlyLinkedList(CircularlyLinkedList&& other) : sz(other.sz), tail(other.tail) {
             
                other.tail = nullptr;
                other.sz = 0;
            
        }

        // Move assignment
        CircularlyLinkedList& operator=(CircularlyLinkedList&& other) {
            if (this != &other) {
                clear();
                tail = other.tail;
                sz = other.sz;

                other.tail = nullptr;
                other.sz =  0;
            }
            return *this;
        }

        // default destructor
        ~CircularlyLinkedList() {
            clear();
        }

};

}  // namespace dsac::list