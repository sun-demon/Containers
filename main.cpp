#include <iostream>
#include <sstream>
#include <deque>
#include <algorithm>
#include <random>
#include <fstream>
#include <stack>
#include <list>
#include <conio.h>

#include "User.h"


using namespace std;


template <typename T>
istream & operator>>(istream &, deque<T> &);
template <typename T>
ostream & operator<<(ostream &, const deque<T> &);
template <typename T>
ostream & operator<<(ostream &, const vector<T> &);


template <typename T>
vector<T> toVector(const stack<T> &);
template <typename T>
stack<T> toStack(const vector<T> &);


template <typename T>
istream & operator>>(istream &, stack<T> &);
template <typename T>
ostream & operator<<(ostream &, const stack<T> &);


template <typename T>
void removeByPosition(deque<T> &, int);
template <typename T, typename Updater>
void update(deque<T> &, Updater updater);
template <typename T, typename Updater>
void removeByPositionAndUpdate(deque<T> &, int, Updater);


template <typename T, typename Updater>
void dequeTask(istream & in1, istream & in2, ostream & out, Updater updater) {
    deque<T> elements1;
    in1 >> elements1;
    out << "Entered: " << elements1 << "\r\n\r\n";

    int position = rand() % elements1.size(); // NOLINT(cert-msc50-cpp)
    out << "Position of removable element: " << position + 1 << "\r\n";
    out << "Removing element: " << *(elements1.begin() + position) << "\r\n\r\n";
    removeByPositionAndUpdate(elements1, position, updater);

    out << "Updated: " << elements1 << "\r\n\r\n";

    deque<T> elements2;
    in2 >> elements2;
    out << "Entered 2: " << elements2 << "\r\n\r\n";

    position = rand() % (elements1.size() - 1); // NOLINT(cert-msc50-cpp)
    int n = rand() % (elements1.size() - position); // NOLINT(cert-msc50-cpp)
    auto firstIter = elements1.begin() + position;
    auto lastIter = elements1.begin() + position + n;
    out << "Position of first removable element: " << position + 1 << "\r\n";
    out << "Count removable elements: " << n << "\r\n";
    out << "Removable elements from: " << *(elements1.begin() + position)
        << ", to: " << *(elements1.begin() + position + n) << "\r\n\r\n";
    elements1.erase(firstIter, lastIter);
    copy(elements2.cbegin(), elements2.cend(), back_inserter(elements1));

    out << "Updated: " << elements1 << "\r\n";
    out << "Deque 2: " << elements2;
}


template <typename T, typename Comparator, typename Predicate>
void stackTask(istream & in, ostream & out, Comparator cmp, Predicate pred) {
    stack<T> elements;
    in >> elements;

    vector<T> buffer = toVector(elements);
    sort(buffer.begin(), buffer.end(), cmp);
    reverse(buffer.begin(), buffer.end());
    elements = toStack(buffer);

    out << "Stack: " << elements << "\r\n\r\n";

    auto iter = find_if(buffer.begin(), buffer.end(), pred);

    if (iter == buffer.end())
        out << "Nothing is find";
    else
        out << "User satisfy conditions: " << *iter;
    out << "\r\n\r\n";

    deque<T> elements2;
    copy_if(buffer.cbegin(), buffer.cend(), back_inserter(elements2), pred);
    out << "Deque: " << elements2 << "\r\n\r\n";

    out << "Sorting..." << "\r\n\r\n";
    sort(buffer.begin(), buffer.end(), cmp);
    elements = toStack(buffer);
    sort(elements2.begin(), elements2.end(), cmp);

    out << "Stack: " << elements << "\r\n"
        << "Deque: " << elements2 << "\r\n\r\n";

    deque<T> elements3;
    merge(buffer.begin(), buffer.end(), elements2.begin(), elements2.end(), back_inserter(elements3), cmp);

    out << "Deque of margin: " << elements3 << "\r\n\r\n";

    out << "Count of elements satisfy conditions in list: " << count_if(elements3.cbegin(), elements3.cend(), pred);
}


int main() {
    cout << "\r\n\r\n====================deque<float>===================\r\n\r\n";

    ifstream fin1("floats1.txt");
    ifstream fin2("floats2.txt");
    dequeTask<float, void (*)(float &)>(
            fin1, fin2,
            cout,
            [](float & elem) -> void { elem *= 2; }
    );
    fin1.close();
    fin2.close();

    cout << "\r\n\r\n====================deque<User>====================\r\n\r\n";

    fin1.open("users1.txt");
    fin2.open("users2.txt");
    dequeTask<DDP::User, void (*)(DDP::User &)>(
            fin1, fin2,
            cout,
            [](DDP::User & user) -> void {
                user.setAge(user.getAge() + 1);
            });
    fin1.close();
    fin2.close();

    cout << "\r\n\r\n====================stack<User>====================\r\n\r\n";

    fin1.open("users1.txt");
    stackTask<DDP::User>(
            fin1,
            cout,
            DDP::compareByFirstName,
            [](const DDP::User & user) -> bool {
                int age = user.getAge();
                return 18 <= age && age <= 60;
            });
    fin1.close();
    getch();
    return 0;
}


template <typename T>
istream & operator>>(istream & in, deque<T> & elements) {
    elements.clear();
    T buffer;
    while (in >> buffer)
        elements.push_back(buffer);
    return in;
}
template <typename T>
ostream & operator<<(ostream & out, const deque<T> & elements) {
    for (auto iter = elements.begin(); iter < elements.end(); ++iter)
        out << *iter << " ";
    return out;
}
template <typename T>
ostream & operator<<(ostream & out, const vector<T> & elements) {
    for (auto iter = elements.begin(); iter < elements.end(); ++iter)
        out << *iter << " ";
    return out;
}



template <typename T>
vector<T> toVector(const stack<T> & elements) {
    stack<T> buffer = elements;
    vector<T> result(elements.size());
    for (int i = buffer.size() - 1; i >= 0; --i) {
        result[i] = buffer.top();
        buffer.pop();
    }
    return result;
}
template <typename T>
stack<T> toStack(const vector<T> & elements) {
    stack<T> result;
    for (auto iter = elements.begin(); iter < elements.end(); ++iter)
        result.push(*iter);
    return result;
}


template <typename T>
istream & operator>>(istream & in, stack<T> & elements) {
    elements = stack<T>();
    T buffer;
    while (in >> buffer)
        elements.push(buffer);
    return in;
}
template <typename T>
ostream & operator<<(ostream & out, const stack<T> & elements) {
    return out << toVector(elements);
}


template <typename T>
void removeByPosition(deque<T> & elements, int position) {
    if (elements.size() == 0 || position < 0 || elements.size() <= position)
        return;
    elements.erase(elements.cbegin() + position);
}
template <typename T, typename Updater>
void update(deque<T> & elements, Updater updater) {
    for (auto iter = elements.begin(); iter < elements.end(); ++iter)
        updater(*iter);
}
template <typename T, typename Updater>
void removeByPositionAndUpdate(deque<T> & elements, int position, Updater updater) {
    removeByPosition(elements, position);
    update<T, Updater>(elements, updater);
}
