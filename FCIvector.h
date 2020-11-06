#ifndef FCIVECTOR_H
#define FCIVECTOR_H

template<typename T>
class FCIvector
{
    private:
        T *elements;
        int numberOfElements;
        int cap;

    public:
        FCIvector();
        int size();
        int capacity();
        bool empty();

        T& operator[](int index);
        T* begin(); /// returns first items address
        T& front(); /// returns first item value
        T& back();  /// returns last item address

        void dyCap(); // sets the capacity value dynamically to adapt to changes (extra)

        void insert(T* position, T val); /// insert value at certain position
        void push_back(T val); /// add value at the end
        void pop_back(); /// removes value from the end
        void clear(); /// set the size to 0 so we can push new values from the beginning
        void erase(T* position); /// removes item at certain position
};

#endif // FCIVECTOR_H
