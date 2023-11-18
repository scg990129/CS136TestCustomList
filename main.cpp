#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class CustomListIterator {
public:
    explicit CustomListIterator(Node<T>* node) : currentNode(node) {}

    CustomListIterator& operator++() {
        if (currentNode) {
            currentNode = currentNode->next;
        }
        return *this;
    }

    T& operator*() const {
        return currentNode->data;
    }

    bool operator!=(const CustomListIterator& other) const {
        return currentNode != other.currentNode;
    }

private:
    Node<T>* currentNode;
};

template <typename T>
class CustomList {
public:
    CustomList() : head(nullptr) {}

    ~CustomList() {
        // Clean up nodes when the list is destroyed
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // Add an element to the front of the list
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Return an iterator pointing to the beginning of the list
    CustomListIterator<T> begin() const {
        return CustomListIterator<T>(head);
    }

    // Return an iterator pointing to one past the end of the list
    CustomListIterator<T> end() const {
        return CustomListIterator<T>(nullptr);
    }

private:
    Node<T>* head;
};

int main() {
    CustomList<int> myList;
    myList.push_front(3);
    myList.push_front(2);
    myList.push_front(1);

    // Using the custom iterator to traverse the list
    for (CustomListIterator<int> it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
