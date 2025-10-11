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
            header = new Node();
            trailer = new Node();
            header->next = trailer;
            trail->prev = header;
            sz = 0;
        }

    public:
        // Constructs an empty list
        DoublyLinkedList() {
            create_sentinels();
        }

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
            return header->next->elem;
        }

        const T& front() const {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return header->next->elem;
        }

        T& back() { 
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return trailer->prev->elem;
        }

        const T& back() const { 
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return trailer->prev->elem;
        }

    private:
        Node* insert_before(T elem, Node* successor) {
            Node* previous_successor = successor->prev;
            Node* new_node = new Node(elem, previous_successor, successor);
            previous_successor->next = new_node;
            successor->prev = new_node;
            sz++;
            return new_node; 
        }

        void erase(Node* node) {
            if (node == header || node == trailer) {
                throw std::runtime_error("Cant erase nodes");
            }
            Node* previous_successor = node->prev;
            Node* successor = node->next;
            previous_successor->next = successor;
            successor->prev = previous_successor;
            sz--;
        }

    public:
        void push_front(const T& elem) {
            insert_before(elem, header->next);
        }

        void push_back(const T& elem) {
            insert_before(elem, trailer);
        }

        void pop_front() {
            if (empty()) 
                return;
                erase(header->next);
        }

        void pop_back() {
            if (empty()) 
                return;
                erase(trailer->prev);
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
                Node* M_first_node = M.header->next;
                Node* M_last_node = M.trailer->prev;

                header->next = M_first_node;
                M_first_node->prev = header;

                trailer->prev = M_last_node;
                M_last_node->next = trailer;

            } else {
                Node* this_node = trailer->prev;
                Node* M_first_node = M.header->next;
                Node* M_last_node = M.trailer->prev;

                this_node->next = M_first_node;
                M_first_node->prev = this_node;

                trailer->prev = M_last_node;
                M_last_node->next = trailer;
            }

            sz += M.sz;

            M.header->next = M.trailer;
            M.trailer->prev = M.header;
            M.sz = 0;
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
                    return node_ptr->elem;
                }
                T* operator->() const {
                    return &(node_ptr->elem);
                }
                iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                iterator operator++(int) {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }
                iterator& operator--() {
                    node_ptr = node_ptr->prev;
                    return *this;
                }
                iterator operator--(int) {
                    iterator old = *this;
                    --(*this);
                    return old;
                }
                bool operator==(const iterator& other) const { 
                    return node_ptr == other.node_ptr;
                }
                bool operator!=(const iterator& other) const {
                    return node_ptr != other.node_ptr;
                }
            };

        class const_iterator {
            private:
                const Node* node_ptr;

            public:
                const_iterator(const Node* ptr = nullptr) 
                : node_ptr(ptr) {}

                const T& operator*() const { 
                    return node_ptr->elem;
                }
                const T* operator->() const { 
                    return &(node_ptr->elem);
                }
                const_iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }
                const_iterator& operator--() {
                    node_ptr = node_ptr->prev;
                    return *this;
                }
                const_iterator operator--(int) {
                    const_iterator old = *this;
                    --(*this);
                    return old;
                }
                bool operator==(const const_iterator& other) const { 
                    return node_ptr == other.node_ptr;
                }
                bool operator!=(const const_iterator& other) const {
                    return node_ptr != other.node_ptr;
                }
        };

        iterator begin() {
            return iterator(header->next);
        }

        const_iterator begin() const {
            return const_iterator(header->next);
        }

        iterator end() {
            return iterator(trailer);
        }

        // Returns const_iterator for the end of the list
        const_iterator end() const {
            return const_iterator(trailer);
        }

        iterator insert(iterator it, const T& elem) {
            Node* new_node = insert_before(elem, it.node_ptr);
            return iterator(new_node);
        }

        iterator erase(iterator it) {
            if (it.node_ptr == trailer || it.node_ptr == header) {
                throw std::runtime_error("Cant erase end() iterator");
            }
            Node* successor = it.node_ptr->next;
            erase(it.node_ptr);
            return iterator(successor);
        }


    private:
        // presumes valid empty list when called
        void clone(const DoublyLinkedList& other) {
            for (*Node p = other.header->next; p != other.trailer; p = p->next) {
                push_back(p->elem);
            }
        }

        public:
        // non-member function to swap two lists
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
            using std::swap;
            swap(a.header, b.header);
            swap(a.trailer, b.trailer);
            swap(a.sz, b.sz);
        }
        
        // resets the list to empty
        void clear() {
            while(!empty()) {
                pop_front();
            }
        }

        DoublyLinkedList(const DoublyLinkedList& other) {
            create_sentinels();
            clone(other);
        }


        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
             if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }

        DoublyLinkedList(DoublyLinkedList&& other) {
           : header(other.header), trailer(other.trailer), sz(other.sz) {
                other.header = nullptr;
                other.trailer = nullptr;
                other.sz = 0;
            } 
        }

        DoublyLinkedList& operator=(DoublyLinkedList&& other) {
            if (this != other) {
                clear();
                delete header;
                delete trailer;

                header = other.header;
                trailer = other.trailer;
                sz = other.sz;

                //nulll original others
                other.header = nullptr;
                other.trailer = nullptr;
                other.sz = 0;
            }
            return *this;
        }

        ~DoublyLinkedList() {
            clear();
            delete header;
            delete trailer;
        }
};

}//dsac::list