/*
The Iterator design pattern is a behavioral pattern that provides a way to access the elements of a collection (like an array, list, or string) 
sequentially without exposing its underlying representation.

Key Points:
Iterator: An object that enables traversing a container, element by element.
Decouples traversal logic from the container’s implementation.
Allows multiple iterators to traverse the same collection independently.
*/

#include <iostream>
#include <cstring>

class StringIterator
{
        const char *position, *end;
public:
        StringIterator(const char * str) : 
                position(str), 
                end(str + strlen(str))  { }
        bool at_end() const { return position == end; }
        void advance() { ++position; }
        char get_char() const { return *position; }
};

void hello_world(StringIterator & iterator)
{
        for(StringIterator i=iterator; !i.at_end(); i.advance())
        {
                std::cout << i.get_char();
        }
}

int main()
{
        StringIterator iterator("Hello world!\n");
        hello_world(iterator);
        return 0;
}

/*
Key Components:
- Iterator Interface – Defines methods like hasNext() and next().
- Concrete Iterator – Implements the iterator interface and maintains traversal state.
- Aggregate Interface – Defines a method to create an iterator.
- Concrete Aggregate – Implements the aggregate interface and provides an iterator.
Usefulness:
- Encapsulation – Hides the internal structure of collections.
- Flexibility – Allows different traversal algorithms without modifying the collection.
- Consistency – Provides a uniform way to iterate over different types of collections.
- Simplifies Code – Reduces complexity in handling collections manually
- Supports Multiple Iterators – Multiple iterators can traverse the same collection independently.
When to Use:
- When you need to traverse a collection without exposing its internal structure.
- When you want to provide a uniform interface for different types of collections.
// - When you need to support multiple traversal algorithms or patterns.
// - When you want to decouple the traversal logic from the collection's implementation.
// Example: How your code uses it:
StringIterator is a custom iterator for a C-style string.
It keeps track of the current position and the end of the string.
Methods like at_end(), advance(), and get_char() allow safe, sequential access to each character.
The hello_world function uses the iterator to print each character, without knowing how the string is stored.

Why is it useful?
Encapsulation: Users don’t need to know the internal structure of the collection.
Flexibility: You can change the collection’s implementation without changing the traversal code.
Reusability: The same iterator interface can be used for different types of collections.
*/
