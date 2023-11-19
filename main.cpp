#include <iostream>

template <typename T>
class CustomLinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        explicit Node(const T& data) : data(data), next(nullptr) {}
    };

public:
    class CustomListIterator {
    public:
        explicit CustomListIterator(Node* node) : currentNode(node) {}

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
        Node* currentNode;
    };

    CustomLinkedList() : head(nullptr) {}

    ~CustomLinkedList() {
        // Clean up nodes when the list is destroyed
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Add an element to the front of the list
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Return an iterator pointing to the beginning of the list
    [[nodiscard]] CustomListIterator begin() const {
        return CustomListIterator(head);
    }

    // Return an iterator pointing to one past the end of the list
    [[nodiscard]] CustomListIterator end() const {
        return CustomListIterator(nullptr);
    }

private:
    Node* head;
};

int main(const int argc, const char* argv[]){
    CustomLinkedList<int> myList;
    myList.push(3);
    myList.push(2);
    myList.push(1);

    // Using the custom iterator to traverse the list
//    for (CustomListIterator<int> it = myList.begin(); it != myList.end(); ++it) {
//        std::cout << *it << " ";
//    }
    for(auto i: myList){
        std::cout << i << " ";
    }

    return 0;
}
