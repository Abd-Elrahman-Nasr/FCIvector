#include "FCIvector.h"
#include <iostream>

using namespace std;

template<typename T>
FCIvector<T>::FCIvector()
{
    numberOfElements = 0;
    cap = 0;
}

template<typename T>
int FCIvector<T>::size(){
    return numberOfElements;
}

template<typename T>
int FCIvector<T>::capacity(){
    return cap;
}

template<typename T>
bool FCIvector<T>::empty(){
    if(numberOfElements == 0){
        return true;
    }
    return false;
}

template<typename T>
T& FCIvector<T>::operator[](int index){
    return *(elements + index);
}

template<typename T>
T* FCIvector<T>::begin(){
    return elements;
}

template<typename T>
T& FCIvector<T>::front(){
    return *elements;
}

template<typename T>
T& FCIvector<T>::back(){
    return *(elements + numberOfElements-1);
}

//****************[EXTRA FUNCTION]*********************//
template<typename T>
void FCIvector<T>::dyCap(){
    /// vector initial dynamic capacity
    if(numberOfElements + 1 == sizeof(T)-1){
        cap = sizeof(T);
    }
    /// vector capacity expanding * 2
    else if (numberOfElements + 1 > cap || numberOfElements + 1 == 2){
        cap *= 2;
    }

    /// expanding
    elements = new T[cap];
}
//****************************************************//

template<typename T>
void FCIvector<T>::insert(T* position, T val){

    /// if there's no elements and the user wants to insert a value at position 0 then push_back it
    if(numberOfElements == 0 && position == elements){
        push_back(val);
    }
    /// if there's at least 1 element then insert it based on the given position
    else if(numberOfElements >= 1){
        T *temp = elements;

        /// make the capacity adapts to changes
        dyCap();

        int n = 0; /// used for transferring index value from array to another

        for(int i=0; i < numberOfElements+1; ++i){
            /// compares the address giving of the value to be inserted
            /// to the address of the current item (in for loop)

            if( position != (temp + i) ){
                elements[i] = temp[i-n];
            } else {
                elements[i] = val;
                n = 1;
            }
        }

        delete[] temp;
        numberOfElements++;
    }
}

template<typename T>
void FCIvector<T>::push_back(T val){

    /// if size = 0 then expand without saving old values because there's none
    if(cap == 0){
        cap++;
        elements = new T[cap];
    } else {
        /// if there's old values save it, exapnd and finally take it back
        T *temp = elements;

        /// make the capacity adapts to changes
        dyCap();

        /// take old values from temp array
        for(int i=0; i < numberOfElements; ++i){
            elements[i] = temp[i];
        }

        delete[] temp;
    }

    elements[numberOfElements] = val; /// push input to the last element
    numberOfElements++; /// the actual data size
}

template<typename T>
void FCIvector<T>::pop_back(){
    if(numberOfElements > 0) numberOfElements--; /// to prevent negative
}

template<typename T>
void FCIvector<T>::clear(){
    numberOfElements = 0;
}

template<typename T>
void FCIvector<T>::erase(T* position){

    if(numberOfElements > 1){
        T *temp = elements;
        elements = new T[numberOfElements-1];
        int n = 0; /// used for transferring index value from array to another

        for(int i=0; i < numberOfElements; ++i){

            /// compares the address giving of the value to be deleted
            /// to the address of the current item (in for loop)
            if( position != (temp + i) ){
                elements[i-n] = temp[i];
            } else {
                n = 1; /// ignore the item which need to be deleted and store next values
            }
        }

        delete[] temp;
    }
    if(numberOfElements > 0) numberOfElements--; /// to prevent negative
}
