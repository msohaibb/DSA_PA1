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
#include <utility>
using namespace std;


/* function that accepts string, a char, and an integer
 * splits the string according to the splitter
 * returns the section specified by index
 * meant to split commands by the spaces
 */
string split(string phrase, char splitter, int index){
    string firstWord;
    string secondWord;
    string thirdWord;
    int temp;

    for(int i = 0; i < phrase.length(); i++)
    {
        if(phrase[i] == splitter)
        {
            temp = i;
            break;
        }
        firstWord += phrase[i];
    }
    for(int j = temp + 1; j < phrase.length(); j++){
        if(phrase[j] == splitter)
        {
            temp = j;
            break;
        }
        secondWord += phrase[j];
    }
    if(index == 0){
        return firstWord;
    }
    else if(index == 1){
        return secondWord;
    }
    else{
        for(int k = temp + 1; k <= phrase.length(); k++){
            if(phrase[k] == 0)
            {
                return thirdWord;
            }
            thirdWord += phrase[k];
        }
    }
    return "";
}



//abstract class implementing a singly-linked list; superclass for Stack and Queue
template<typename T>
class SimpleList
{
//nodes consist of the value and a link to the next node
public:
    struct Node{
        T element;
        Node* link;
    };
//defining methods for use for subclasses and constructor
public:

    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual string getName() = 0;
    virtual void setName(string theName);

//list-related variables and getters/setters
public:

    int size = 0;

    void setHeaderAddress(Node* address){
        headerAddress = address;
    }
    Node* getHeaderAddress(){
        return headerAddress;
    }
    int getLength(){
        return size;
    }


public:
    Node* lastAddress = nullptr;
    Node* headerAddress = nullptr;
    Node* initialize(){
        Node headerNode = new Node();
        headerNode->element = 0;
        headerNode->link = nullptr;

        setHeaderAddress(*headerNode);

        return *headerNode;
    }

public:
    void insertStart(T value){
        Node *headerNode = headerAddress;
        Node *addedNode = new Node;

        addedNode->link = headerNode;
        addedNode->element = value;

        (*headerNode).link = addedNode;

        if(size == 0){
            lastAddress = addedNode->link;
        }
        size++;
    }
    void insertEnd(T value){
        Node lastNode = &lastAddress;

        Node *addedNode = nullptr;
        addedNode = new Node;

        addedNode->link = nullptr;
        addedNode->element = value;

        lastAddress = *addedNode;

        lastNode.link = *addedNode;

        size++;
    }
    T removeStart(){
        Node *headerNode = headerAddress;
        Node nextNode = *(*headerNode).link;

        T poppedValue = nextNode.element;
        delete((*headerNode).link);

        (*headerNode).link = nextNode.link;

        size--;
        return poppedValue;

    }
};

template<typename T>
class Stack:public SimpleList<T>{
string name;
//LIFO
public:

    void push(T value){
        this->insertStart(value);
    }

    T pop(){
        return this->removeStart();
    }
    string getName(){
        return name;
    }
    void setName(string givenName){
        name = givenName;
    }
    Stack(string givenName){
        setName(givenName);
    }
};


template<typename T>
class Queue:public SimpleList<T>{
//LIFO
string name;
public:
    void push(T value){
        this->insertEnd(value);
    }
    T pop(){
        return this->removeStart();
    }
    string getName(){
        return name;
    }
    Queue(string givenName){
        name = givenName;
    }
};

template <typename T>
SimpleList<T>* getList(string name, list<SimpleList<T>*> listSL){
    for (auto it = listSL.begin(); it != listSL.end(); ++it){
        if(((*it)->getName()) == name)
            return *it;
    }
    return nullptr;
}

void parse(const string& readFile, const string& writeFile) { //opens the input file
    ifstream input(readFile);
    ofstream output(writeFile);
    string line;
    string listType;
    string listName;

    int valueInt;
    double valueDouble;
    string valueString;

    list<SimpleList<int>*> listSLi;
    list<SimpleList<double>*> listSLd;
    list<SimpleList<string>*> listSLs;


    while(getline(input, line))
    {
        if(split(line, ' ', 0) == "create"){
             listType = split(line, ' ', 1)[0];
             listName = split(line, ' ', 1);
             if(listType == "d"){
                 if(getList(listName, listSLd) == nullptr){
                     SimpleList<double> *pSLd;
                     pSLd = new Stack<double>(listName);
                     listSLd.push_front(pSLd);
                 }
                 else{
                     cout << "ERROR: This name already exists!";
                 }
             }
             else if(listType == "i"){
                 if(getList(listName, listSLi) == nullptr){
                     SimpleList<int> *pSLi;
                     pSLi = new Stack<int>(listName);
                     listSLi.push_front(pSLi);
                 }
                 else{
                     cout << "ERROR: This name already exists!";
                 }
             }
             else{
                 if(getList(listName, listSLd) == nullptr){
                     SimpleList<string> *pSLs;
                     pSLs = new Stack<string>(listName);
                     listSLs.push_front(pSLs);
                 }
                 else{
                     cout << "ERROR: This name already exists!";
                 }
             }
        }
        else if(split(line, ' ', 0) == "pop"){
            listType = split(line, ' ', 1)[0];
            listName = split(line, ' ', 1);
            if(listType == "d"){
                SimpleList<double> *SLAddressD = getList(listName, listSLd);
                cout << SLAddressD->pop();
            }
            else if(listType == "i"){
                SimpleList<int>* SLAddressI = getList(listName, listSLi);
                cout << SLAddressI->pop();
            }
            else{
                SimpleList<string>* SLAddressS = getList(listName, listSLs);
                cout << SLAddressS->pop();
            }
        }
        else{
            listType = split(line, ' ', 1)[0];
            listName = split(line, ' ', 1);
            if(listType == "d"){
                valueDouble = std::stod(split(line, ' ', 2));
                SimpleList<double> *SLAddressD = getList(listName, listSLd);
                SLAddressD->push(valueDouble);
            }
            else if(listType == "i"){
                valueInt = std::stoi(split(line, ' ', 2));
                SimpleList<int> *SLAddressI = getList(listName, listSLi);
                SLAddressI->push(valueInt);
            }
            else{
                valueString = split(line, ' ', 2);
                SimpleList<string> *SLAddressS = getList(listName, listSLs);
                SLAddressS->push(valueString);
            }
        }
    }
    input.close();
    output.close();
}


int main(){
    string fileInput;
    string fileOutput;

    cout << "Enter name of input file: ";
    cin >> fileInput;

    cout << "Enter name of output file: ";
    cin >> fileOutput;

    parse(fileInput, fileOutput);

    return 0;
}


