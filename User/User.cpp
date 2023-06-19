//
// Created by Daniil on 13.06.2023.
//

#include "User.h"
#include "fstream"


using namespace std;


namespace DDP {
    User::User(string firstName, string lastName, int age)
            : firstName_(std::move(firstName)), lastName_(std::move(lastName)), age_(age) {}

    const string &User::getFirstName() const { return firstName_; }

    const string &User::getLastName() const { return lastName_; }

    int User::getAge() const { return age_; }

    void User::setFirstName(string firstName) { firstName_ = std::move(firstName); }

    void User::setLastName(string lastName) { lastName_ = std::move(lastName); }

    void User::setAge(int age) { age_ = age; }


    istream &operator>>(istream &in, User &user) {
        return in >> user.firstName_ >> user.lastName_ >> user.age_;
    }

    ostream &operator<<(ostream &out, const User &user) {
        return out << user.firstName_ << " " << user.lastName_ << " " << user.age_ << " ";
    }


    int compareByFirstName(const User & first, const User & second) {
        return first.getFirstName().compare(second.getFirstName());
    }
    int compareByLastName(const User & first, const User & second) {
        return first.getLastName().compare(second.getLastName());
    }
    int compareByAge(const User & first, const User & second) {
        return first.getAge() - second.getAge();
    }
}