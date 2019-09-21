// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
class Control {
private:
std::atomic_int counter;
public:
Control(){
    counter = 1;
}

void operator ++(){
    counter++;
}
    void operator --(){
        counter--;
    }
/*
Control& operator= (Control& i){
    counter = i.counter;
}*/

std::atomic_int cou(){return counter;}

~Control() = default;
};

template <typename T>
class SharedPtr{
private:
    Control * control ;
    T * data ;
public:
    SharedPtr() {
        control = nullptr;
        data = nullptr;
    }

    explicit SharedPtr(T* dat){
            data = dat;
            control = new Control;
    }


    SharedPtr(const SharedPtr& ptr){
        control = ptr.control;
        data = ptr.data;
        control++;
    }

    SharedPtr(SharedPtr&& ptr) {
        control = ptr.control;
        data = ptr.data;
        control++;
    }

    auto opeartor=(const SharedPtr& r) -> SharedPtr&{
        reset();
        data = r.data;
        control = r.control;
        control++;
    }


    auto opeartor=(SharedPtr&& r) -> SharedPtr&{
            reset();
            data = r.data;
            control = r.control;
            control++;
    }

// проверяет, указывает ли указатель на объект
    operator bool() const{
        return data != nullptr;
    }

auto operator*() const -> T&{
    return &data;
}

auto operator->() const -> T*{
    return data;
}

    auto get() -> T*{
        return data;
    }

    void reset(){
        control-- ;

        if(control->counter == 0){ delete [] data;
            delete []  control;}

        data = nullptr;
        control = nullptr;
    }

    void reset(T* ptr){
        reset();
        data = ptr;
        control = new Control();
    }


    void swap(SharedPtr& r){
        SharedPtr temp(r);
        r = *this;
        *this = temp;
        temp.reset();
    }

// возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t{
        if(!control) return 0;
        return static_cast<size_t>(control.cou());
    }

};

#endif // INCLUDE_HEADER_HPP_
