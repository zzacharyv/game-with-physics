
// #include <vector>
// #include <iostream>
// #include <unordered_set>
// #include <algorithm>

// using namespace std;

// class Library
// {
// private:
//     vector<int> books;
// public:
//     Library();
//     void addBook(int);
//     void remove(int);
//     vector<int> * getBooks();
// };

// Library::Library() {
//     books = {};
//     // books.push_back(1);
// }

// void Library::addBook(int book)
// {
//     books.push_back(book);
//     cout << books.size() << endl;
// }

// void Library::remove(int book) {
//     books.erase(find(books.begin(), books.end(), book));
//         cout << books.size() << endl;

// }

// vector<int> * Library::getBooks() {
//     return &books;
// }

// int main(int argc, char *args[])
// {
//     Library library;
//     library.addBook(1);
//     library.addBook(2);
//     vector<int>::iterator it;
//     it = find (library.getBooks()->begin(), library.getBooks()->end(), 2);
//   if (it != library.getBooks()->end())
//     std::cout << "Element found in myvector: " << *it << '\n';
//   else
//     std::cout << "Element not found in myvector\n";
// }

#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Library
{
private:
    vector<int *> books;

public:
    Library();
    void addBook(int *);
    void remove(int *);
    vector<int *> *getBooks();
};

Library::Library()
{
    books = {};
    // books.push_back(1);
}

void Library::addBook(int * book)
{
    books.push_back(book);
    cout << books.size() << endl;
}

void Library::remove(int *book)
{
    books.erase(find(books.begin(), books.end(), book));
    cout << books.size() << endl;
}

vector<int *> *Library::getBooks()
{
    return &books;
}

int main(int argc, char *args[])
{
    Library library;
    int a = 1;
    int b = 2;
    library.addBook(&a);
    library.addBook(&b);
    vector<int *>::iterator it;

    int *f = &a;
    auto result = std::find_if(library.getBooks()->begin(), library.getBooks()->end(), [f](int *item)
                               { 
    if (item == nullptr) return false; // may want to do something else here
    return *item == *f; });

    if (result != library.getBooks()->end())
    {
        // found it!
        std::cout << "Element found in myvector: " << **result << '\n';
    } else {
        cout << "poop" << endl;
    }
    library.getBooks()->erase(result);

    //   [f](const int* p) { return *p == *f; });
    // it = find (library.getBooks()->begin(), library.getBooks()->end(), 2);
    // if (it != library.getBooks()->end())
    //     std::cout << "Element found in myvector: " << *it << '\n';
    // else
    //     std::cout << "Element not found in myvector\n";
}