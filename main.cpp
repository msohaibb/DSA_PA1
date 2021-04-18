/*
 * Sohaib Bhatti
 * This program implements a singly-linked list class, which is then used to implement a stack class and a queue class.
 * This program also reads, processes, and executes a list of commands in a .txt file, and outputs it to another .txt
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <new>
using namespace std;

void readWrite(const string& readFile) { //opens the input file
    ifstream input(readFile);
    string line;

    while(getline(input, line))
    {
        cout << line + "\n";
    }
    input.close();
}

//abstract class implementing a singly-linked list; superclass for Stack and Queue
template<typename T>
class SimpleList
{
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;

public:
    class iterator{

    };

//nodes consist of the value and a link to the next node
private:
    struct Node{
        T element;
        Node* link;

    };


protected:
    void insertStart(T value){

    }
    void insertEnd(T value){

    }
    T removeStart(T* headerAddress){
        Node headerNode = *headerAddress;
        Node nextNode = *headerNode.link;

        headerNode.link = nextNode.link;
        T poppedValue = nextNode.element;

        delete(headerNode.link);

        return poppedValue;
    }
};

template<typename T>
class Stack:public SimpleList<T>{
//LIFO
public:
    void push(T value){
        insertStart(value);
    }

    T pop(){
        //removeStart();
        return 0;
    }

};

template<typename T>
class Queue:public SimpleList<T>{
//FIFO
public:
    void push(T value){
        insertEnd(value);
    }

    T pop(){
        //removeStart();
        return 0;
    }

};

int main(){
    string fileInput;
    string fileOutput;

    cout << "Enter name of input file: ";
    cin >> fileInput;

    cout << "Enter name of output file: ";
    cin >> fileOutput;

    readWrite(fileInput);



    return 0;
}


