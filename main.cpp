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

//list-related variables and getters/setters
public:
    int size = 0;
    int getLength(){
        return size;
    }

public:
    Node* headerNode = new Node();
    Node* lastNode = headerNode;
    /*Node* initialize(){
        Node *headerNode;
        headerNode = new Node();
        //headerNode->element = 0;
        headerNode->link = nullptr;


        return headerNode;
    }*/

public:
    void insertStart(T value){
        Node *addedNode = new Node;
        addedNode->link = headerNode;
        addedNode->element = value;

        headerNode->link = addedNode;

        if(size == 0){
            lastNode = addedNode->link;
        }
        size++;
    }
    void insertEnd(T value){
        //Node lastNode = *lastAddress;

        Node *addedNode;
        addedNode = new Node;

        addedNode->link = nullptr;
        addedNode->element = value;

        lastNode = addedNode;

        lastNode->link = addedNode;

        size++;
    }
    T removeStart(){
        Node *nextNode = (*headerNode).link;

        T poppedValue = (*nextNode).element;
        delete((*headerNode).link);

        (*headerNode).link = (*nextNode).link;

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

    Stack(string givenName){
        name = givenName;
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
    string listStructure;

    int valueInt;
    double valueDouble;
    string valueString;

    list<SimpleList<int>*> listSLi;
    list<SimpleList<double>*> listSLd;
    list<SimpleList<string>*> listSLs;

    cout << "This is the beginning of the function.";
    while(getline(input, line))
    {
        //cout << line;
        output << "PROCESSING COMMAND: " << line;
        if(split(line, ' ', 0) == "create"){
            listType = split(line, ' ', 1)[0];
            listName = split(line, ' ', 1);
            listStructure = split(line, ' ', 2);
            output << "list type: " << listType << endl;
            output << "list name: " << listName << endl;
            output << "list structure: " << listStructure << endl;

            if(listType == "d" && listStructure == "stack"){
                if(getList(listName, listSLd) == nullptr){
                    SimpleList<double> *pSLd;
                    pSLd = new Stack<double>(listName);
                    cout << "stack double created";
                    listSLd.push_front(pSLd);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
            else if(listType == "d" && listStructure == "queue"){
                if(getList(listName, listSLd) == nullptr){
                    SimpleList<double> *pSLd;
                    pSLd = new Queue<double>(listName);
                    cout << "queue double created";
                    listSLd.push_front(pSLd);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
            else if(listType == "i" && listStructure == "stack"){
                if(getList(listName, listSLi) == nullptr){
                    SimpleList<int> *pSLi;
                    pSLi = new Stack<int>(listName);
                    cout << "stack int created";
                    listSLi.push_front(pSLi);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
            else if(listType == "i" && listStructure == "queue"){
                if(getList(listName, listSLi) == nullptr){
                    cout << "queue int created";
                    SimpleList<int> *pSLi;
                    pSLi = new Queue<int>(listName);

                    listSLi.push_front(pSLi);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
            else if(listType == "s" && listStructure == "stack"){
                if(getList(listName, listSLi) == nullptr){
                    SimpleList<string> *pSLs;
                    pSLs = new Stack<string>(listName);
                    cout << "stack string created";
                    listSLs.push_front(pSLs);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
            else if(listType == "s" && listStructure == "queue"){
                if(getList(listName, listSLd) == nullptr){
                    SimpleList<string> *pSLs;
                    pSLs = new Queue<string>(listName);
                    cout << "queue string created";
                    listSLs.push_front(pSLs);
                }
                else{
                    output << "ERROR: This name already exists!";
                }
            }
        }
        /*
         * pop usage
         * first checks if array is empty
         * if not, pops the function and prints the value popped
         */
        /*
        else if(split(line, ' ', 0) == "pop"){
            listType = split(line, ' ', 1)[0];
            listName = split(line, ' ', 1);

            if(listType == "d"){
                SimpleList<double> *SLAddressD = getList(listName, listSLd);
                if(SLAddressD->getLength() == 0)
                {
                    output << "ERROR: This list is empty!";
                }
                else {
                    output << "Value popped: " << SLAddressD->pop();
                }
            }
            else if(listType == "i"){
                SimpleList<int>* SLAddressI = getList(listName, listSLi);
                if(SLAddressI->getLength() == 0)
                {
                    output << "ERROR: This list is empty!";
                }
                else {
                    output << "Value popped: " << SLAddressI->pop();
                }
            }
            else{
                SimpleList<string>* SLAddressS = getList(listName, listSLs);
                if(SLAddressS->getLength() == 0)
                {
                    output << "ERROR: This list is empty!";
                }
                else {
                    output << "Value popped: " << SLAddressS->pop();
                }
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
        }*/
    }
    input.close();
    output.close();
}


int main(){
    //cout << "MAIN WORKS!!!";
    parse("input.txt", "output.txt");

    return 0;
}


