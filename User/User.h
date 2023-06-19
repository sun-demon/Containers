//
// Created by Daniil on 13.06.2023.
//

#ifndef CONTAINERS_USER_H_DDP
#define CONTAINERS_USER_H_DDP


#include <string>


namespace DDP {
    class User {
    public:
        explicit User(std::string = "", std::string = "", int = 0);


        const std::string &getFirstName() const;

        const std::string &getLastName() const;

        int getAge() const;

        void setFirstName(std::string);

        void setLastName(std::string);

        void setAge(int);


        friend std::istream &operator>>(std::istream &, User &);

        friend std::ostream &operator<<(std::ostream &, const User &);


    private:
        std::string firstName_;
        std::string lastName_;
        int age_;
    };


    int compareByFirstName(const User &, const User &);
    int compareByLastName(const User &, const User &);
    int compareByAge(const User &, const User &);
}


#endif //CONTAINERS_USER_H_DDP
