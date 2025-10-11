#pragma once

#include <utility>     // provides std::swap

namespace dsa::list {

// doubly linked list, similar to std::list
template <typename T>
class DoublyLinkedList {
    private:
        class Node {
            public:
                Node* prev{nullptr};
                Node* next{nullptr};
                T elem;

                Node() {}
                Node(const T& element, Node* prv, Node* nxt)
                : elem{element}, prev{prv}, next{nxt} {}
        };
        Node* header;
        Node* trailer;
        int sz{0};

        // utility to configure an empty list
        void create_sentinels() {
            // ToDo
        }

    public:
        // Constructs an empty list
        DoublyLinkedList() {
            // ToDo
        }

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

    private:
        Node* insert_before(T elem, Node* successor) {
            // ToDo
        }

        void erase(Node* node) {
            // ToDo
        }

    public:
        void push_front(const T& elem) {
            // ToDo
        }

        void push_back(const T& elem) {
            // ToDo
        }

        void pop_front() {
            // ToDo
        }

        void pop_back() {
            // ToDo
        }

        // Concatenates all nodes from list M to the end of this list in O(1) time.
        // After the operation, M becomes an empty list
        // No nodes are copied or allocated; only pointer links are adjusted.
        // Does nothing if M is empty or if this and M are the same list.
        void concat(DoublyLinkedList& M) {
            if (this == &M) 
                return; // self-concat not allowed
            if (M.sz == 0) 
                return;  // nothing to add

            if (sz == 0) {
                // ToDo
            } else {
                // ToDo
            }

            // ToDo
        }

        class iterator {
            // needed for DoublyLinkedList's insert and erase
            friend class DoublyLinkedList;

            private:
                Node* node_ptr;  // pointer to a node

            public:
                iterator(Node* ptr = nullptr) 
                : node_ptr(ptr) {}

                T& operator*() const {
                    // ToDo
                }
                T* operator->() const {
                    // ToDo
                }
                iterator& operator++() {
                    // ToDo
                }
                iterator operator++(int) {
                    // ToDo
                }
                iterator& operator--() {
                    // ToDo
                }
                iterator operator--(int) {
                    // ToDo
                }
                bool operator==(const iterator& other) const { 
                    // ToDo
                }
                bool operator!=(const iterator& other) const {
                    // ToDo
                }
            };

        class const_iterator {
            private:
                const Node* node_ptr;

            public:
                const_iterator(const Node* ptr = nullptr) 
                : node_ptr(ptr) {}

                const T& operator*() const { 
                    // ToDo
                }
                const T* operator->() const { 
                    // ToDo
                }
                const_iterator& operator++() {
                    // ToDo
                }
                const_iterator operator++(int) {
                    // ToDo
                }
                const_iterator& operator--() {
                    // ToDo
                }
                const_iterator operator--(int) {
                    // ToDo
                }
                bool operator==(const const_iterator& other) const { 
                    // ToDo
                }
                bool operator!=(const const_iterator& other) const {
                    // ToDo
                }
        };

        iterator begin() {
            // ToDo
        }

        const_iterator begin() const {
            // ToDo
        }

        iterator end() {
            // ToDo
        }

        // Returns const_iterator for the end of the list
        const_iterator end() const {
            // ToDo
        }

        iterator insert(iterator it, const T& elem) {
            // ToDo
        }

        iterator erase(iterator it) {
            // ToDo
        }


    private:
        // presumes valid empty list when called
        void clone(const DoublyLinkedList& other) {
            // ToDo
        }

        public:
        // non-member function to swap two lists
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
            // ToDo
        }
        
        // resets the list to empty
        void clear() {
            // ToDo
        }

        DoublyLinkedList(const DoublyLinkedList& other) {
            // ToDo
        }


        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            // ToDo
        }

        DoublyLinkedList(DoublyLinkedList&& other) {
            // ToDo
        }

        DoublyLinkedList& operator=(DoublyLinkedList&& other) {
            // ToDo
        }

        ~DoublyLinkedList() {
            // ToDo
        }
};

}//dsac::list