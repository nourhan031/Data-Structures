#include <iostream>
#include <list>
using namespace std;


template<typename T>
class Queue{
private:
    list<T> list;
public:
    Queue(){}

    Queue(T firstElement){
        push(firstElement);
    }

    int size()const{
        return list.size();
    }

    bool isEmpty()const{
        return size()==0;
    }

    void enqueue(T element){
        list.push_front(element);
    }

    void dequeue(){
        if (isEmpty()){
            throw runtime_error("queue is  empty");
        }
        list.pop_back();
    }

    T peek()const{
        if (isEmpty()){
            throw out_of_range("Queue is empty");
        }
        return list.back();
    }

    void print()const{
        for(const auto& element: list){
            cout << element << " ";
        }
        cout << endl;
    }

};

int main() {
    Queue<int> queue;
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);

    cout << "head of queue: " << queue.peek() << endl;
    cout << "size: " << queue.size() << endl;
    cout << "stack elements: ";
    queue.print();
    cout << "queue elements after dequeuing (removing the head): ";
    queue.dequeue();
    queue.print();
    cout << endl;
    return 0;
}
