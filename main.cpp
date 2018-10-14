// CS212 Spring 2018
// Created by Gordon Malan on 5/20/2018.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

// function just to print array
template<typename T>
void printList(const LinkedList<T>& list)
{
    Iterator<T> current = list.begin();
    while (current != list.end())
    {
        cout << *current << " ";
        current++;
    }
    cout << endl;
}


int main()
{
    // Create a list for strings
    LinkedList<string> list;
    list.add("Beijing");
    list.add("Tokyo");
    list.add("New York");
    list.add("London");
    list.add("Paris");

    // Create another list for strings
    LinkedList<string> list2;
    list2.add("Beijing");
    list2.add("Shanghai");
    list2.add("Paris");
    list2.add("Berlin");
    list2.add("Rome");

    LinkedList<string> list1(list);
    cout << "list1: ";
    printList(list1);
    cout << "list2: ";
    printList(list2);
    list1.addAll(list2);
    cout << "list is : ";
    printList(list);
    cout << "After list1.addAll(list2), list1 is ";
    printList(list1);
    list1 = list;
    cout << "(Should be Beijing, Tokyo, New York, London, Paris) -- list1: ";
    printList(list1);
    cout << "list2: ";
    printList(list2);//asd
    list1.removeAll(list2);
    cout << "After list1.removeAll(list2), list1 is ";
    printList(list1);
    list1 = list;
    cout << "list1: ";
    printList(list1);
    cout << "list2: ";
    printList(list2);
    list1.retainAll(list2);
    cout << "After list1.retainAll(list2), list1 is ";
    printList(list1);
    list1 = list;
    cout << "list1: ";
    printList(list1);
    cout << "list2: ";
    printList(list2);
    list1 = list1 + list2;
    cout << "After list1 = list1 + list2, list1 is ";
    printList(list1);
    list1 = list; // be certain this is a deep copy
    cout << "list1: ";
    printList(list1);
    cout << "list2: ";
    printList(list2);
    list1 = list1 - list2;
    cout << "After list1 = list1 - list2, list1 is ";
    printList(list1);
    list1 = list;
    cout << "list1: ";
    printList(list1);
    cout << "list2: ";
    list1 = list1 ^ list2;
    cout << "After list1 = list1 ^ list2, list1 is ";
    printList(list1);
    list1 = list;
    cout << list1[0] << endl;
    list1[0] = "Paris";
    cout << list1[0] << endl;

    // So contains and last index will be easy once all of above are working
    cout << "Contains Seattle? " << list1.contains("Seattle") << endl;
    cout << "Last index of Seattle: " << list1.lastIndexOf("Seattle") << endl;
    list1.remove("Seattle");
    cin.get();
    return 0;
}