#include <iostream>
# include <stack>
using namespace std;

template<typename T>
class queue{
private:
    stack<T> input;
    stack<T> output;

public:
    void push(T x){
        input.push(x);
    }

    T pop(){
        peek();

        int result = output.top();
        output.pop();

        return result;
    }

    T peek(){
        if(output.empty()){
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
        }
        return output.top();
    }

    bool empty(){
        return input.empty() && output.empty();
    }

    void print() {
        stack<T> temp = output;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }

        temp = input;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }

        cout << endl;
    }
};

int main() {
    queue<int> myQueue;
    myQueue.push(4);
    myQueue.push(5);
    myQueue.push(6);
    myQueue.push(7);

    cout << "Queue elements: ";
    myQueue.print();

    cout << myQueue.pop() << endl;  // Should print 4
    cout << myQueue.peek() << endl; // Should print 5

    return 0;
}
