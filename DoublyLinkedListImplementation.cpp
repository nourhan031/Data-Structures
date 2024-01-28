#include "bits/stdc++.h"
using namespace std;

template<typename T>
struct Node{
    T data;
    Node* prev;
    Node* next;

    Node(T data, Node* prev= nullptr, Node* next = nullptr): data(data), prev(prev), next(next) {}

    ~Node(){
        prev = next = nullptr;
    }
};

template<typename T>
class DoublyLinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int sz = 0;

public:
    DoublyLinkedList(): head(nullptr), tail(nullptr), sz(0) {}

    int size(){
        return sz;
    }

    bool isEmpty(){
        return size() == 0;
    }

    void addLast(T element){
        if (isEmpty()) {
            //head=tail=newNode
            head = tail = new Node<T>(element, nullptr, nullptr);
        }
        else {
            //next of tail is the new node
            tail->next = new Node<T>(element, tail, nullptr);
            //new tail is next of old tail
            tail = tail->next;
        }
        sz++;//inc list's size
    }

    void add(T elem) {
        addLast(elem);
    }

    void addFirst(T element){
        if (isEmpty()){
            head = tail = new Node<T>(element, nullptr, nullptr);
        }
        else{
            // prev of head = new
            head->prev = new Node<T>(element, nullptr, head);
            //set new as head
            head = head->prev;
        }
        sz++;
    }

    T peekFirst()const{
        return head->data;
    }

    T peekLast()const{
        return tail->data;
    }

    T removeFirst(){
        if (isEmpty()){
            throw runtime_error("Empty list");
        }
        //extract data at the head and move
        //the head ptr forwards one node
        T data = head->data;
        head = head->next;
        --sz;

        if(isEmpty()){
            tail = nullptr;
        }
        else{
            head->prev = nullptr;
        }
        return data;
    }

    T removeLast(){
        if (isEmpty()){
            throw runtime_error("Empty list");
        }
        T data = tail->data;
        tail = tail->prev;
        --sz;

        if(isEmpty()){
            head = nullptr;
        }
        else{
            tail->next = nullptr;
        }
        return data;
    }

    T removeNode(Node<T>* node) {
        if (node->prev == nullptr) return removeFirst();
        if (node->next == nullptr) return removeLast();

        //skip over node
        node->next->prev = node->prev;
        node->prev->next = node->next;

        //temporarily store data we want to return
        T data = node->data;

        //memory cleanup
        delete node;

        --sz;

        return data;
    }

    T removeAt(int i){
        if (i < 0 || i >= sz) {
            throw out_of_range("index out of range");
        }

        int index;
        Node<T>* trav;

        //is it more efficient to search from the front or the back?
        if(i<sz/2){//if i is less than half the size, start from the front
            for (index = 0, trav = head; index != i; index++) {
                trav = trav->next;
            }
        }
        else{
            //search from the back
            for(index=sz-1, trav=tail; index!=i; index--){
                trav = trav->prev;
            }
        }
        return removeNode(trav);
    }

    int indexOf(const T& element)const{
        int index = 0;
        Node<T>* trav = head;

        while(trav != nullptr){
            if(element == trav->data){
                return index;
            }
            trav = trav->next;
            index++;
        }
        return -1;
    }

    bool contains(const T& elem) const {
        return indexOf(elem) != -1;
    }

    //iterator to iterate over the array allowing an abstraction for it
    class Iterator {
    private:
        Node<T> *trav;
    public:
        Iterator(Node<T> *head) : trav(head) {}

        bool hasNext() {
            return trav != nullptr;
        }

        T next() {
            T data = trav->data;
            trav = trav->next;
            return data;
        }
    };

    Iterator iterator() const {
        return Iterator(head);
    }

    string toString() const {
        string result = "[ ";
        Node<T>* trav = head;//init ptr to the head
        while (trav != nullptr) {//loop on list till the end (trav becomes nil)
            result += to_string(trav->data);//append current node's data to result string
            //check if current node has a next one
            //if true, append a comma and a space to result (separation between elements)
            if (trav->next != nullptr) {
                result += ", ";
            }
            //move trav to the next node
            trav = trav->next;
        }
        result += " ]";
        return result;
    }
};

void testAdd(DoublyLinkedList<int>& arr){
    arr.add(1);
    arr.add(2);
    arr.add(3);

    cout << "Doubly Linked List: " << arr.toString() << endl;
}

void testAddFirst(DoublyLinkedList<int>& arr){
    arr.addFirst(1);
    arr.addFirst(2);
    arr.addFirst(3);

    cout << "Doubly Linked List: " << arr.toString() << endl;
}

void testAddLast(DoublyLinkedList<int>& arr){
    arr.addLast(1);
    arr.addLast(2);
    arr.addLast(3);

    cout << "Doubly Linked List: " << arr.toString() << endl;
}

void testSize(DoublyLinkedList<int>& arr) {
    cout << "Testing size function:\n";
    cout << arr.size() << endl;
}

void testIsEmpty(DoublyLinkedList<int>& arr){
    cout << "testing isEmpty function:\n";
    cout << arr.isEmpty() << endl;
}

void testPeekFirst(DoublyLinkedList<int>& arr){
    if (arr.isEmpty()) {
        throw runtime_error("Empty list");
    }
    cout << "testing peekFirst function:\n";
    cout << arr.peekFirst();
}

void testPeekLast(DoublyLinkedList<int>& arr){
    if (arr.isEmpty()) {
        throw runtime_error("Empty list");
    }
    cout << "testing peekFirst function:\n";
    cout << arr.peekLast();
}

void testRemoveFirst(DoublyLinkedList<int>& arr){
    cout << "linked list after removing the first element: \n";
    arr.removeFirst();
    cout << arr.toString();
}

void testRemoveLast(DoublyLinkedList<int>& arr){
    cout << "linked list after removing the last element: \n";
    arr.removeLast();
    cout << arr.toString();
}

void testRemoveAt(DoublyLinkedList<int>& arr, int index){
    cout << "Linked list after removing element at index " << index << ": \n";
    arr.removeAt(index);
    cout << arr.toString();
}

void testIndexOf(DoublyLinkedList<int>& arr, int element){
    cout << "Index of " << element << " in the linked list: " << arr.indexOf(element) << endl;
}

void testContains(DoublyLinkedList<int>& arr, int element){
    cout << "Does the linked list contain " << element << "? " << (arr.contains(element) ? "Yes" : "No") << endl;
}

int main() {
    DoublyLinkedList<int> my_doubly_list;
    testAdd(my_doubly_list);
//    testAddFirst(my_doubly_list);
//    testAddLast(my_doubly_list);
//    testSize(my_doubly_list);
//    testIsEmpty(my_doubly_list);
//    testPeekFirst(my_doubly_list);
//    testPeekLast(my_doubly_list);
//    testRemoveFirst(my_doubly_list);
//    testRemoveLast(my_doubly_list);

//    int indexToRemove;
//    cout << "Enter the index to remove: ";
//    cin >> indexToRemove;
//
//    try {
//        testRemoveAt(my_doubly_list, indexToRemove);
//    } catch (const out_of_range& e) {
//        cerr << "Error: " << e.what() << endl;
//    }
    int element;
    cout << "Enter the element to find: ";
    cin >> element;

    testIndexOf(my_doubly_list, element);
    testContains(my_doubly_list,element);

    return 0;
}
