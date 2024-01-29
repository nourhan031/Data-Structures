#include <iostream>
#include <list>
using namespace std;

template<typename T>
class Stack{
private:
    list<T> list;
public:
    Stack(){} //empty stack

    Stack(T firstElement){
        push(firstElement);
    }

    int size()const{
       return list.size();
    }

    bool isEmpty()const {
        return size() == 0;
    }

    void push(T element){
        list.push_back(element);
    }

    void pop(){
        if (isEmpty()){
            throw out_of_range("Stack is empty");
        }
        T element = list.back();//pop an element off the back
        list.pop_back();
    }

    T peek()const{
        if (isEmpty()){
            throw out_of_range("Stack is empty");
        }
        return list.back();
    }

    void print()const {
        for(const auto& element : list){
            cout << element << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "top: " << stack.peek() << endl;
    cout << "size: " << stack.size() << endl;
    cout << "stack elements: ";
    stack.print();
    cout << "stack elements after popping the top: ";
    stack.pop();
    stack.print();
    cout << endl;
    return 0;
}
