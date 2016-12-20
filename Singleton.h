//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_SINGLETON_H
#define FINANCE_SINGLETON_H

template<typename T>
class Singleton {
public:
    static T &getInstance() {
        static T instance_;
        return instance_;
    }

    Singleton(Singleton const &) = delete;

    Singleton(Singleton &&) = delete;

    Singleton &operator=(Singleton const &)= delete;

    Singleton &operator=(Singleton &&)= delete;

protected:
    Singleton() {}

    virtual ~Singleton() {}
};

#endif //FINANCE_SINGLETON_H
