#include <iostream>
using namespace std;

template <typename T>
class DynamicArray{
private:
    T* arr;
    int fakeLen;
    int actualCapacity;
public:
    //constructor to init arr's size to 16
    DynamicArray(): fakeLen(0), actualCapacity(16){
        if (actualCapacity < 0){
            throw invalid_argument("Illegal Capacity: " + to_string(actualCapacity));
        }
        //init arr and cast it as type T
        arr = new T[actualCapacity];
    }

        DynamicArray(int initCapacity): fakeLen(0), actualCapacity(initCapacity){
        if (actualCapacity < 0){
            throw invalid_argument("Illegal Capacity: " + to_string(actualCapacity));
        }
        arr = new T[actualCapacity];
    }

    ~DynamicArray(){
        delete[] arr;
    }

    [[nodiscard]] int size()const{
        return fakeLen;
    }

    bool isEmpty()const{
        return size()==0;
    }

    //get element's index
    T get(int i)const{
        if (i<0 || i>=fakeLen){
            throw out_of_range("Index out of range");
        }
        return arr[i];
    }

    //put element in a specified index
    void set(int i, T element){
        if (i<0 || i>=fakeLen){
            throw out_of_range("Index out of range");
        }

        arr[i] = element;
    }

    void clear(){
        for (int i = 0; i < fakeLen; ++i) {
            arr[i] = T(); // Each element in the array is set to a new instance of type T
        }
        fakeLen = 0; // The length of the array is reset to 0
    }

    // check again
    void add(T element){
        if (fakeLen >= actualCapacity) {
            if (actualCapacity == 0){
                actualCapacity = 1;
            }
            else{
                actualCapacity *= 2; //double the size
            }

            T *new_arr = new T[actualCapacity];

            for (int i = 0; i < fakeLen; ++i) {
                new_arr[i] = arr[i];
            }

            delete[] arr;
            arr = new_arr;
        }
        arr[fakeLen++] = element;
    }

    T removeAt(int removeIndex){
        if (removeIndex >= fakeLen || removeIndex < 0) {
            throw out_of_range("Index out of range");
        }

        T data = arr[removeIndex];
        T* new_arr = new T[fakeLen-1];

        for (int i = 0, j = 0; i < fakeLen; ++i, ++j) {
            if (i == removeIndex){
                j--; // Skip over rm_index by fixing j temporarily
            }
            else{
                new_arr[j] = arr[i];
            }
        }
        delete[] arr;
        arr = new_arr;

        actualCapacity = --fakeLen;
        return data;
    }

    bool remove(const T& obj){
        int index = indexOf(obj);
        if (index == -1) {
            return false;
        }
        removeAt(index);
        return true;
    }

    int indexOf(const T& obj) const {
        for (int i = 0; i < fakeLen; i++) {
            if (obj == arr[i]) {
                return i;
            }
        }
        return -1;
    }

    bool contains(const T& obj) const {
        return indexOf(obj) != -1;
    }

    //iterator to iterate over the array allowing an abstraction for it
    class Iterator{
    private:
        const DynamicArray& arrayRef;
        int i;
    public:
        Iterator(const DynamicArray& arr) : arrayRef(arr), i(0) {}

        void setIndex(int index){
            i = index;
        }

        bool operator!=(const Iterator& other) const {
            return i != other.i;
        }

        T operator*() const {
            return arrayRef.arr[i];
        }

        const Iterator& operator++() {
            ++i;
            return *this;
        }

        bool hasNext(){
            return i < arrayRef.fakeLen;
        }

        T next(){
            if (!hasNext()){
                throw runtime_error("No more elements");
            }
            return arrayRef.arr[i++];
        }

//        void remove(){
//            throw runtime_error("Unsupported operation");
//        }
    };

    Iterator begin() const {
        return Iterator(*this);
    }

    Iterator end() const {
        Iterator iter(*this);
        iter.setIndex(fakeLen);
        return iter;
    }

};

void testAdd(DynamicArray<int>& arr) {
    cout << "Testing add function:\n";
    arr.add(1);
    arr.add(2);
    arr.add(3);
    for (int element: arr){
        cout << element << " ";
    }
    cout << endl;

    // ANOTHER WAY TO PRINT ALL ELEMENTS
    // iterators are typically used in a loop to access each element in a container from begin() to end()

//    for(auto it = myArray.begin(); it != myArray.end(); ++it) {
//        cout << *it << " ";
//    }
}

void testGet(DynamicArray<int>& arr) {
    cout << "Testing get function:\n";
    cout << arr.get(2) << endl;
}

void testSet(DynamicArray<int>& arr) {
    cout << "Testing set function:\n";
    arr.set(2,4);
    cout << arr.get(2) << endl;
}

void testSize(DynamicArray<int>& arr) {
    cout << "Testing size function:\n";
    cout << arr.size() << endl;
}

void testClear(DynamicArray<int>& arr) {
    cout << "Testing clear function:\n";
    arr.clear();
    cout << arr.isEmpty() << endl;
}

void testBegin(DynamicArray<int>& arr) {
    cout << "Testing begin function:\n";

    /*
     cant use: cout << myArray.begin()
     because myArray.begin() returns an iterator, not a value that can be printed directly
     therefore we dereference the iterator returned by begin() in order to be able to print it
     */

    if (!arr.isEmpty()) {
        cout << *(arr.begin()) << endl;
    }
}

void testEnd(DynamicArray<int>& arr) {
    cout << "Testing end function:\n";

    /*
      end() function returns an iterator pointing to one past the last element in the dynamic array.
      It’s used as a sentinel value to represent the end of the container, not an actual element.

      Therefore, trying to print myArray.end() or dereference it with *(myArray.end())
      will not give a meaningful value
   */

    if (!arr.isEmpty()) {
        cout << arr.get(arr.size() - 1) << endl;
    }
}

void testRemoveAt(DynamicArray<int>& arr) {
    cout << "Testing removeAt function:\n";
    int removedElement = arr.removeAt(1);
    cout << "Removed element: " << removedElement << endl;
}

void testRemove(DynamicArray<int>& arr) {
    cout << "Testing remove function:\n";
    bool isRemoved = arr.remove(2);
    cout << "Is element removed? " << (isRemoved ? "Yes" : "No") << endl;
}

void testIndexOf(DynamicArray<int>& arr) {
    cout << "Testing indexOf function:\n";
    int index = arr.indexOf(3);
    cout << "Index of element: " << index << endl;
}

void testContains(DynamicArray<int>& arr) {
    cout << "Testing contains function:\n";
    bool doesContain = arr.contains(3);
    cout << "Does array contain element? " << (doesContain ? "Yes" : "No") << endl;
}

void testIterator(DynamicArray<int>& arr) {
    cout << "Testing Iterator's hasNext and next functions:\n";
    //hasNext: returns true if there are more elements to iterate over
    //next: returns the next element in the container
    auto it = arr.begin();
    while(it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << endl;
}


int main(){
    DynamicArray<int> myArray;
    testAdd(myArray);
    testBegin(myArray);
    testEnd(myArray);
    testGet(myArray);
    testIndexOf(myArray);
//    testSet(myArray);
    testSize(myArray);
    testContains(myArray);
    testIterator(myArray);

//    testRemoveAt(myArray);
//    testRemove(myArray);
//    testClear(myArray);

}



