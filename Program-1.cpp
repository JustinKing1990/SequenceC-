
#include <iostream>
#include <cstdio>
using namespace std;

template <class T>
class Sequence
{
private: // Internal Representation

    class NodeRecord {
    public:
        T value;
        NodeRecord* next;
    };
    NodeRecord* head;
    int size;
    

public:
    Sequence();
    ~Sequence();
    void clear(void);

    //implement the following four functions
    void add(T& x, int pos) {
        //! updates self
        //! restores pos
        //! clears x
        //! requires: 0 â‰¤ pos â‰¤ |self|
        //! ensures: self = #self[0, pos) * <#x> * #self[pos, |#self|)
        NodeRecord* blip = new NodeRecord();
        blip->value = x;
        NodeRecord* temp = head;
        blip->next = NULL;
        if (size==0){
            head = blip;
        }
        else if(pos==0){
            blip->next = head;
            head = blip;
        }
        else if(pos==size){
                while(temp->next != NULL){
                temp = temp->next;
                }
                temp->next = blip;
        }
        else{
            for(int i; i<pos-1; i++){
            temp = temp->next;
            }
            blip->next = temp->next;
            temp->next = blip;
    }
        size++;
        x= 0;
    }//add

    void remove(T& x, int pos) {
        //! updates self
        //! restores pos //! replaces x
        //!requires: 0 â‰¤ pos < |self|
        //!ensures: <x> = #self[pos, pos+1) and
        //!        self = #self[0, pos) * #self[pos+1, |#self|)
        NodeRecord* temp = head;
        if(pos==0){
            x = head->value;
            cout<<"The removed value is: " << x<< "\n";
            head = head->next;
        } else{
            for (int i = 0; i < pos-1; i++) {
            temp = temp->next;
        }//for
            if(pos==size){
                x = temp->next->value;
                cout<<"The removed value is: "<<x<< "\n";
                temp->next = NULL;
            } else{
                x = temp->next->value;
                cout<<"The removed value is: "<<x<<"\n";
                temp->next = temp->next->next;
            }
        }
        size--;
    }//remove

    T& entry(int pos){
    //! restores self, pos
    //! requires: 0 â‰¤ pos < |self|
    //! ensures: <entry> = self[pos, pos+1)
	NodeRecord* temp = head;
	if(pos==0){
cout <<"The value at position " << pos<<" is " << temp->value<< "\n";
} else{
	for(int i = 0; i<pos;i++){
	temp = temp->next;
}//for
	cout <<"The value at position " << pos<<" is " << temp->value<< "\n";
}//else
    return temp->value;
}//entry
	

    int length(void){
    //! restores self
    //! ensures: length = |self|
	return size;
    }

    void outputSequence(void) {
        //! restores self
        //! ensures: self = #self
        NodeRecord* temp = head;
        cout<< "The linked list is: ";
        for(int i =0; i<size; i++){
            cout<<temp->value<<"\t";
            temp = temp->next;
            if(i%10==0&&i>1)
                cout<<"\n";
        }//while
         cout<<"\n";
    }//output

private: // Internal operations
    void reclaimAllNodes(NodeRecord*& p);
};

template <class T>
Sequence<T>::Sequence()
{
    head = NULL;
    size = 0;
}// Sequence

template <class T>
Sequence<T>::~Sequence()
{
    reclaimAllNodes(head);
}    // ~Sequence


template <class T>
void Sequence<T>::clear(void)
{
    reclaimAllNodes(head);
    head = NULL;
    size = 0;
} // clear

template <class T>
void Sequence<T>::reclaimAllNodes(NodeRecord*& initialP)
// requires: Null(initialP)  or  Alive(initialP)
//  ensures: all nodes in linked list
//           beginning with initialP are reclaimed
{
    if (initialP != NULL) {
        reclaimAllNodes(initialP->next);
        delete (initialP);
    } // end if
} // reclaimAllNodes

// You are required to implement add, remove, entry, length, and outputSequence functions here.


int main() {
    /* Complete this main function to test all functions of the Sequence class.
       Must use at least 3 Sequence type objects to test the functions.
       Make sure to test all boundary conditions (See Canvas assignment for more info.).
       Copy and paste properly labeled outputs below the main function.
    */
    Sequence<char> *s1 = new Sequence<char>();
    char input;
    int i = 0;
    char a;
    int removePos;
    int entryPos;
    for(int j=0; j<3;j++){
        cout<<"TESTING INITIAL CREATION OF LINKED LIST!"<<"\n"<<"========================="<<"\n";
    while (input != 'n')
    {
        cout << "Enter the value to be placed in linked list "<< j+1<<" (enter 'n' to exit): ";
        cin>>input;
        if(input != 'n')
        s1->add(input, i);
        i++;
    }
        cout<<"TESTING SIZE OF THE LIST!"<<"\n"<<"======================"<<"\n";
    cout<<"The size of list "<<j+1<<" is "<<s1->length()<<"\n";
    i--;
        cout<<"TESTING FIRST OUTPUT OF THE LINKED LIST!"<<"\n"<<"===================="<<"\n";
    s1->outputSequence();
        cout<<"TESTING THE REMOVE FUNCTION!"<<"\n"<<"===================="<<"\n";
    cout << "Enter a position for a value to be removed: ";
    cin >> removePos;
        if(removePos>i-1 || removePos<0)
            cout<<"You have entered a value out of bounds to the size of the list!"<<"\n";
    else{ 
    s1->remove(a,removePos);
    s1->outputSequence();
        cout<<"The size of list "<<j+1<<" is "<<s1->length()<<"\n";
        i--;
    }
        cout<<"TESTING THE ENTRY FUNCTION"<<"\n"<<"===================="<<"\n";
    cout<< "Enter a postion to see its value ";
    cin>>entryPos;
        if(entryPos>i-1 || entryPos<0){
		 cout<<"You have entered a value out of bounds to the size of the list!"<<"\n";
            return 0;
        } else{
    s1->entry(entryPos);
    cout<<"The size of list "<<j+1<<" is "<<s1->length()<<"\n";
        }//else
        cout<<"TESTING THE ADD FUNCTION AT A SPECIFIC POSITION!"<<"\n"<<"=================="<<"\n";
    cout<<"Enter a position in the list to add a value ";
        cin>>entryPos;
        if(entryPos>i || entryPos<0){
            cout<<"You have entered a value out of bounds with the list!";
            return 0;
        }
    cout<<"Enter a value to insert at position "<<entryPos<<": ";
        cin>>input;
        s1->add(input, entryPos);
        s1->outputSequence();
        cout<<"NOW CLEARING THE LIST!"<<"\n"<<"==============="<<"\n";
    cout<<"Now clearing sequence "<<j+1<<" !"<<"\n"<<"==============="<<"\n";
    s1->clear();
    s1->outputSequence();
        input = '0';
        i = 0;
    }
    return 0;
}

/*  Copy and paste PROPERLY LABELED (Must identify each and every output, what Sequence and what function being tested)
TESTING INITIAL CREATION OF LINKED LIST!
=========================
Enter the value to be placed in linked list 1 (enter 'n' to exit): 1
Enter the value to be placed in linked list 1 (enter 'n' to exit): 2
Enter the value to be placed in linked list 1 (enter 'n' to exit): 3
Enter the value to be placed in linked list 1 (enter 'n' to exit): 4
Enter the value to be placed in linked list 1 (enter 'n' to exit): n
TESTING SIZE OF THE LIST!
======================
The size of list 1 is 4
TESTING FIRST OUTPUT OF THE LINKED LIST!
====================
The linked list is: 1	2	3	4	
TESTING THE REMOVE FUNCTION!
====================
Enter a position for a value to be removed: 1
The removed value is: 2
The linked list is: 1	3	4	
The size of list 1 is 3
TESTING THE ENTRY FUNCTION
====================
Enter a postion to see its value 1
The value at position 1 is 3
The size of list 1 is 3
TESTING THE ADD FUNCTION AT A SPECIFIC POSITION!
==================
Enter a position in the list to add a value 1
Enter a value to insert at position 1: 1
The linked list is: 1	1	3	4	
NOW CLEARING THE LIST!
===============
Now clearing sequence 1 !
===============
The linked list is: 
TESTING INITIAL CREATION OF LINKED LIST!
=========================
Enter the value to be placed in linked list 2 (enter 'n' to exit): adsfadfhga
Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): Enter the value to be placed in linked list 2 (enter 'n' to exit): n
TESTING SIZE OF THE LIST!
======================
The size of list 2 is 10
TESTING FIRST OUTPUT OF THE LINKED LIST!
====================
The linked list is: a	d	s	f	a	d	f	h	g	a	
TESTING THE REMOVE FUNCTION!
====================
Enter a position for a value to be removed: 2
The removed value is: s
The linked list is: a	d	f	a	d	f	h	g	a	
The size of list 2 is 9
TESTING THE ENTRY FUNCTION
====================
Enter a postion to see its value 2
The value at position 2 is f
The size of list 2 is 9
TESTING THE ADD FUNCTION AT A SPECIFIC POSITION!
==================
Enter a position in the list to add a value 2
Enter a value to insert at position 2: 2
The linked list is: a	2	d	f	a	d	f	h	g	a	
NOW CLEARING THE LIST!
===============
Now clearing sequence 2 !
===============
The linked list is: 
TESTING INITIAL CREATION OF LINKED LIST!
=========================
Enter the value to be placed in linked list 3 (enter 'n' to exit): terwan
Enter the value to be placed in linked list 3 (enter 'n' to exit): Enter the value to be placed in linked list 3 (enter 'n' to exit): Enter the value to be placed in linked list 3 (enter 'n' to exit): Enter the value to be placed in linked list 3 (enter 'n' to exit): Enter the value to be placed in linked list 3 (enter 'n' to exit): TESTING SIZE OF THE LIST!
======================
The size of list 3 is 5
TESTING FIRST OUTPUT OF THE LINKED LIST!
====================
The linked list is: t	e	r	w	a	
TESTING THE REMOVE FUNCTION!
====================
Enter a position for a value to be removed: 1    
The removed value is: e
The linked list is: t	r	w	a	
The size of list 3 is 4
TESTING THE ENTRY FUNCTION
====================
Enter a postion to see its value 1
The value at position 1 is r
The size of list 3 is 4
TESTING THE ADD FUNCTION AT A SPECIFIC POSITION!
==================
Enter a position in the list to add a value 1
Enter a value to insert at position 1: 1
The linked list is: t	1	r	w	a	
NOW CLEARING THE LIST!
===============
Now clearing sequence 3 !
===============
The linked list is: 
 */
