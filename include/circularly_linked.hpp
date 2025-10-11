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
        CircularlyLinkedList();

        int size() const {
            // ToDo
        }
    
        bool empty() const {
            // ToDo
        }

        T& front() {
            // ToDo
        }

        const T& front() const {
            // ToDo
        }

        T& back() {
            // ToDo
        }

        const T& back() const {
            // ToDo
        }

        void push_front(const T& elem) {
            if (sz == 0) {
                // ToDo
            } else {
                // ToDo
            }
            // ToDo
        }

        void push_back(const T& elem) {
            // ToDo
        }

        void pop_front() {
            // ToDo
            if (head == tail)
                // ToDo
            else
                // ToDo
            // ToDo
        }


        void rotate() {
            if (tail != nullptr)
                // ToDo
        }
    
        // Splits the current even-sized circular list into two equal-sized circular lists A and B
        // After splitting, A and B become the two halves (preserving original order), and the original list becomes empty. 
        //If the size is odd, throw std::logic_error
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            if (sz == 0) {     // nothing to split
                // ToDo
            }
            if (sz % 2 != 0) {
                // ToDo
            }

            // ToDo
        }

    private:
        // presumes valid empty list when called
        void clone(const CircularlyLinkedList& other) {
            // ToDo
        }

    public:
        // non-member function to swap two lists
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
            // ToDo
        }

        // Resets the list to empty
        void clear() {
            // ToDo
        }

        // Copy constructor
        CircularlyLinkedList(const CircularlyLinkedList& other) { 
            // ToDo
        }

        // Copy assignment
        CircularlyLinkedList& operator=(const CircularlyLinkedList& other) {
            // ToDo
        }

        // Move constructor
        CircularlyLinkedList(CircularlyLinkedList&& other) {
            // ToDo
        }

        // Move assignment
        CircularlyLinkedList& operator=(CircularlyLinkedList&& other) {
            // ToDo
        }

        // default destructor
        ~CircularlyLinkedList() {
            // ToDo
        }

};

}  // namespace dsac::list