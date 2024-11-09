#include <iostream>
#include <stdexcept>

// Виняток для нестачі пам'яті
class MemoryAllocationException : public std::runtime_error {
public:
    MemoryAllocationException() : std::runtime_error("Memory allocation failed") {}
};

// Виняток для видалення з пустого списку
class EmptyListException : public std::runtime_error {
public:
    EmptyListException() : std::runtime_error("Attempt to delete from an empty list") {}
};

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(T value) {
        Node* newNode = nullptr;
        try {
            newNode = new Node(value);
        } catch (const std::bad_alloc&) {
            throw MemoryAllocationException();
        }

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove() {
        if (head == nullptr) {
            throw EmptyListException();
        }

        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        DoublyLinkedList<int> list;
        list.add(1);
        list.add(2);
        list.print();
        list.remove();
        list.print();
        list.remove();
        list.remove(); // This will throw an exception
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
