#pragma once

#include <utility> // for std::swap

namespace dsa::list {

// similar to std::forward_list
template <typename T>
class SinglyLinkedList {
    private:
        class Node {
            public:
                Node* next;   // pointer to next node
                T elem;       // element
                Node(const T& element, Node* nxt = nullptr) 
                : elem{element}, next{nxt} {}
        };

        int sz{0};
        Node* head{nullptr};
        Node* tail{nullptr};

    public:
        
        // ToDo: Constructs an empty list
        SinglyLinkedList();

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
            return head->elem;
        }

        const T& front() const {
            if (empty()) {
                throw std::runtime_error("Empty List");
            }
            return head->elem;
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
            head = new Node(elem, head);

            if (sz == 0) {
                tail = head;
            }
            sz++;
        }

        void pop_front() {
            if (empty()) {
                return;
            }

            Node* origHead = head; //saves the original head
            head = head->next; 
            delete origHead; //deletes if not needed
            sz--;

            if (sz == 0) { //if list goes empty, tail is empty
                tail = nullptr;
            }
        }

        void push_back(const T& elem) {
            Node* newNode = new Node(elem);

            if (sz == 0) {//makes new nodes take place for empty list
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            sz++;
        }

    // Concatenate attaches the contents of another list M 
    // to the end of the current list and clears list M.
    // No nodes are copied or allocated; only pointer links are adjusted.
    void concatenate(SinglyLinkedList& M) {
        if (this == &M) 
            return;   // do nothing self-concatenation

        if (M.sz == 0) 
            return;

        if (sz == 0) {
            head = M.head;
            tail = M.tail;
        } else {
            tail->next = M.head;
            tail = M.tail;
        }
        sz += M.sz;
        M.head = nullptr;
        M.tail = nullptr;
        M.sz = 0;
    }

    // Reverses the linked list in place
    void reverse() {
        if (sz <= 1) 
            return;  // empty or single-node list
        
            Node* past_node = nullptr;
            Node* current_node = head;
            Node* next_node = nullptr;

            std::swap(head, tail);

            while (current_node != nullptr) {
                next_node = current_node->next;
                current_node->next = past_node;

                past_node = current_node;
                current_node = next_node;
            }
            
            
    }

    class iterator {
        // needed for SinglyLinkedLists's insert_after and erase_after
        friend class SinglyLinkedList;

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
            bool operator==(iterator rhs) const {
                return node_ptr == rhs.node_ptr;
            }
            bool operator!=(iterator rhs) const {
                return node_ptr != rhs.node_ptr;
            }
    };

    class const_iterator {
        private:
            Node* node_ptr;  // pointer to a node

        public:
            const_iterator(Node* ptr = nullptr)
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
            bool operator==(const_iterator rhs) const {
                return node_ptr == rhs.node_ptr;
            }
            bool operator!=(const_iterator rhs) const {
                return node_ptr != rhs.node_ptr;
            }
    };

    iterator begin() {
        return iterator(head);
    }

    const_iterator begin() const {
        return const_iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    iterator insert_after(iterator it, const T& elem) {
        Node* current_node = it.node_ptr;
        if (current_node == nullptr) {
            throw std::runtime_error("Can't inster after end iterator");
        }

        Node* new_node = new Node(elem, current_node->next);
        current_node->next = new_node;
        
        if(current_node == tail) {
            tail = new_node;
        }
        sz++;
        return iterator(new_node);
    }

    
    iterator erase_after(iterator it) {
        Node* current_node = it.node_ptr;
        if (current_node == nullptr || current_node->next == nullptr) {
            throw std::runtime_error("Can't erase, there is nothing after iterator");
        }

        Node* node_delete = current_node->next;
        current_node->next = node_delete->next;
        
        if(node_delete == tail) {
            tail = current_node;
        }
        delete node_delete;
        sz--;
        return iterator(current_node->next);
    }

    private:
        // presumes valid empty list when called
        void clone(const SinglyLinkedList& other) {
            if (other.head == nullptr) {
                return;
            }
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->elem);
                current = current->next;
            }
        }

    public:
        // non-member function to swap two lists
        friend void swap(SinglyLinkedList& a, SinglyLinkedList& b) {
            using std::swap;
            swap(a.head, b.head);
            swap(a.tail, b.tail);
            swap(a.sz, b.sz);
        }

        /// resets the list to empty
        void clear() {
            while(!empty()) {
                pop_front();
            }
            
        }

        /// copy constructor
        SinglyLinkedList(const SinglyLinkedList& other) {
            head = nullptr;
            tail = nullptr;
            sz = 0;

            clone(other);
        }

        /// copy assignment
        SinglyLinkedList& operator=(const SinglyLinkedList& other) {
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }

        /// move constructor
        SinglyLinkedList(SinglyLinkedList&& other) {
            :sz(other.sz), head(other.head), tail(other.tail) {
                other.head = nullptr;
                other.tail = nullptr;
                other.sz = 0;
            } 
        }

        /// move assignment
        SinglyLinkedList& operator=(SinglyLinkedList&& other) {
            if (this != &other) {
                clear();

                head = other.head;
                tail = other.tail;
                sz = other.sz;

                // null the others
                other.head = nullptr;
                other.tail = nullptr;
                other.sz = 0;
            }
            return *this;
        }

        /// destructor
        ~SinglyLinkedList() { clear(); }

};
}//dsac::list