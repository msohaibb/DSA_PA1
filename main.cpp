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
string split(string phrase, int index){
    string firstWord;
    string secondWord;
    string thirdWord;
    int temp;

    for(int i = 0; i < phrase.length(); i++)
    {
        if(phrase[i] == ' ' || phrase[i] == '\n')
        {
            temp = i;
            break;
        }
        firstWord += phrase[i];
    }
    for(int j = temp + 1; j < phrase.length(); j++){
        if(phrase[j] == ' ' || phrase[j] == '\n')
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

            if(phrase[k] == 0 || phrase[k] == ' ' || phrase[k] == '\n')
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
private:
    struct Node{
        T element;
        Node* link;
    };
//defining methods for use for subclasses and constructor
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    //virtual string getName() = 0;

//defining size
private:
    int size = 0;
    string Name;

public:
    int getLength(){
        return size;
    }
    string getName(){
        return Name;
    }
    SimpleList(string givenName){
        Name = givenName;
    }

//creating a header node and storing the address of the last node for use in push/pop functions
public:
    Node* headerNode{};
    Node* lastNode{};
    void initialize(){
        headerNode = new Node();
        headerNode->link = nullptr;

        lastNode = headerNode;
    }

protected:
    /*
     * Creates a new node with given value
     * Links the new node to the node that was previously first
     * Changes header link to the address of the new node (effectively inserting new node at the beginning)
     * This is the push implementation for Stacks
     */
    void insertStart(T value) {
        Node *addedNode = new Node;

        addedNode->link = headerNode->link;
        addedNode->element = value;
        headerNode->link = addedNode;

        //not required as lastNode is not useful in Stacks, just done for consistency's sake
        if(size == 0){
            lastNode = headerNode;
        }
        size++;
    }
    /*
     * Creates a new node with given value
     * The node that was previously last has its link changed to the address of the new node
     * The last node is now the new node
     * This is the push implementation for Queues
     */
    void insertEnd(T value){
        //Node lastNode = *lastAddress;

        Node *addedNode;
        addedNode = new Node;

        addedNode->link = nullptr;
        addedNode->element = value;

        lastNode->link = addedNode;

        lastNode = addedNode;

        cout << size;

        if(size == 0){
            headerNode->link = lastNode;
        }

        size++;
    }
    /*
     * Finds the first node and the element inside of it.
     * Finds the second node.
     * Deletes the first node, and sets the second node to be the first
     */
    T removeStart(){
        Node *firstNode = headerNode->link;
        T poppedValue = firstNode->element;

        Node *secondNode = firstNode->link;

        delete((headerNode->link));
        headerNode->link = secondNode;

        size--;
        return poppedValue;

    }
};

/*
 * FIFO implementation of SimpleList. Push is insertStart()
 */
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

    Stack(string givenName):SimpleList<T>(givenName){
        name = givenName;
    }
};

/*
 * LIFO implementation of SimpleList. Push is insertEnd()
 */
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
    Queue(string givenName):SimpleList<T>(givenName){
        name = givenName;
    }
};

/*
 * Search method. Looks through a C++ List of SimpleLists until it finds the one that has the right name
 */
template <typename T>
SimpleList<T>* getList(string name, list<SimpleList<T>*> listSL){
    for (auto iter = listSL.begin(); iter != listSL.end(); ++iter){
        if(((*iter)->getName()) == name)
            return *iter;
    }
    return nullptr;
}
/*
 * Function that opens and reads the file, and outputs results to another file
 */
void parse(const string& readFile, const string& writeFile) {
    ifstream input(readFile);
    ofstream output(writeFile);
    string line;
    string listType;
    string listName;
    string listStructure;

    int valueInt;
    double valueDouble;
    string valueString;

    /*
     * These are the C++ lists that contain the SimpleLists of each type
     * Each C++ list contains both Stacks and Queues
     */
    list<SimpleList<int>*> listSLi;
    list<SimpleList<double>*> listSLd;
    list<SimpleList<string>*> listSLs;

    while(getline(input, line))
    {
        output << "PROCESSING COMMAND: " << line << endl;
        /*
         * This is where SimpleLists are created
         * Checks whether file is asking for Stack/Queue
         * Checks which type of list it will be
         * Checks to see if a simpleList of that name already exists
         * If not, creates a Stack/Queue of the given type and pushes it to the appropriate C++ list
         */
        if(split(line, 0) == "create"){

            listType = split(line,  1)[0];
            listName = split(line, 1);
            listStructure = split(line,  2);

            if(listType == "d" && listStructure == "stack"){
                if(getList(listName, listSLd) == nullptr){
                    SimpleList<double> *pSLd;
                    pSLd = new Stack<double>(listName);
                    pSLd->initialize();
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
                    pSLd->initialize();
                    listSLd.push_front(pSLd);
                }
                else{
                    output << "ERROR: This name already exists!" << endl;
                }
            }
            else if(listType == "i" && listStructure == "stack"){
                if(getList(listName, listSLi) == nullptr){
                    SimpleList<int> *pSLi;
                    pSLi = new Stack<int>(listName);
                    pSLi->initialize();
                    listSLi.push_front(pSLi);
                }
                else{
                    output << "ERROR: This name already exists!" << endl;
                }
            }
            else if(listType == "i" && listStructure == "queue"){
                if(getList(listName, listSLi) == nullptr){
                    SimpleList<int> *pSLi;
                    pSLi = new Queue<int>(listName);
                    pSLi->initialize();
                    listSLi.push_front(pSLi);
                }
                else{
                    output << "ERROR: This name already exists!" << endl;
                }
            }
            else if(listType == "s" && listStructure == "stack"){
                if(getList(listName, listSLi) == nullptr){
                    SimpleList<string> *pSLs;
                    pSLs = new Stack<string>(listName);
                    pSLs->initialize();
                    listSLs.push_front(pSLs);
                }
                else{
                    output << "ERROR: This name already exists!" << endl;
                }
            }
            else if(listType == "s" && listStructure == "queue"){
                if(getList(listName, listSLd) == nullptr){
                    SimpleList<string> *pSLs;
                    pSLs = new Queue<string>(listName);
                    pSLs->initialize();
                    listSLs.push_front(pSLs);
                }
                else{
                    output << "ERROR: This name already exists!" << endl;
                }
            }
        }
        /*
         * This is where SimpleLists are popped.
         * It checks which type of SimpleList it is and uses the appropriate C++ List
         * It looks for the name in the C++ List.
         * If it finds it, pops the function and prints the value popped
         */

        else if(split(line, 0) == "pop"){
            listType = split(line, 1)[0];
            listName = split(line, 1);
            if(listType == "d"){
                SimpleList<double> *SLAddressD = getList(listName, listSLd);
                if(SLAddressD == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else if(SLAddressD->getLength() < 1)
                {
                    output << "ERROR: This list is empty!" << endl;
                }
                else{
                    output << "Value popped: " << SLAddressD->pop() << endl;
                }
            }
            else if(listType == "i"){
                SimpleList<int>* SLAddressI = getList(listName, listSLi);
                if(SLAddressI == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else if(SLAddressI->getLength() < 1)
                {
                    output << "ERROR: This list is empty!" << endl;
                }
                else{
                    output << "Value popped: " << SLAddressI->pop() << endl;
                }
            }
            else{
                SimpleList<string>* SLAddressS = getList(listName, listSLs);
                if(SLAddressS == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else if(SLAddressS->getLength() < 1)
                {
                    output << "ERROR: This list is empty!" << endl;
                }
                else{
                    output << "Value popped: " << SLAddressS->pop() << endl;
                }
            }
        }
        /*
         * This is where SimpleLists are pushed.
         * It checks which type of SimpleList it is and uses the appropriate C++ List
         * It looks for the name in the C++ List.
         * If it finds it, pushes the given value onto the SimpleList
         */
        else{
            listType = split(line, 1)[0];
            listName = split(line, 1);
            if(listType == "d"){
                valueDouble = std::stod(split(line, 2));
                SimpleList<double> *SLAddressD = getList(listName, listSLd);
                if(SLAddressD == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else{
                    SLAddressD->push(valueDouble);
                }

            }
            else if(listType == "i"){
                valueInt = std::stoi(split(line, 2));
                SimpleList<int> *SLAddressI = getList(listName, listSLi);
                if(SLAddressI == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else{
                    SLAddressI->push(valueInt);
                }
            }
            else{
                valueString = split(line, 2);
                SimpleList<string> *SLAddressS = getList(listName, listSLs);
                if(SLAddressS == nullptr){
                    output << "ERROR: This name does not exist!" << endl;
                }
                else{
                    SLAddressS->push(valueString);
                }
            }
        }
    }
    input.close();
    output.close();
}


int main(){
    cout << endl;
    parse("input.txt", "output.txt");
    return 0;
}


