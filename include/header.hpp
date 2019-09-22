// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <cstddef>
#include <utility>

class Control {
 private:
  std::atomic_int counter;

 public:
  Control() {
      counter = 1;
  }

  explicit Control(size_t i){
      counter = i;
  }

  void increase() { counter++; }
  void decrease() { counter--; }
  /*
  Control& operator= (Control& i){
      counter = i.counter;
  }*/

  size_t cou() {
       if(!counter) return 0;
      return static_cast<size_t>(counter); }

  ~Control() = default;
};

template <typename T>
class SharedPtr {
 private:
  Control* control;
  T* data;

 public:
  SharedPtr() {
    control = nullptr;
    data = nullptr;
  }

  explicit SharedPtr(T* dat) {
    control = new Control(1);
    data = dat;
  }

  SharedPtr(const SharedPtr& ptr) {
    control = ptr.control;
    data = ptr.data;
    control->increase();
  }

  SharedPtr(SharedPtr&& ptr) noexcept {
    control = ptr.control;
    data = ptr.data;
    control->increase();
  }

  ~SharedPtr() {
    if (*this) {
      control->decrease();
      if (use_count() == 0 && data!=nullptr) {
        delete data;
        delete control;
      }
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    reset();
      control = r.control;
      data = r.data;
    control->increase();
    return *this;
  }

  auto operator=(SharedPtr&& r) noexcept -> SharedPtr& {
    reset();
      control = r.control;
      data = r.data;
    control->increase();
    return *this;
  }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const { return data != nullptr; }

  auto operator*() const -> T& { return *data; }

  auto operator-> () const -> T* { return data; }

  auto get() -> T* { return data; }

  void reset() {
    if (!*this) return;
    control->decrease();
      if (control->cou() == 0) {
        delete data;
        delete control;
      }

      data = nullptr;
      control = nullptr;

  }

  void reset(T* ptr) {
      if (*this) {
          control->decrease();
          if (control->cou() == 0) {
              delete data;
              delete control;
          }
      }
      control = new Control(1);
      data = ptr;
  }

  void swap(SharedPtr& r) {
    SharedPtr temp(r);
    r = *this;
    *this = temp;
    temp.reset();
  }

  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t {
    if (!control) return 0;
    return static_cast<size_t>(control->cou());
  }
};

#endif  // INCLUDE_HEADER_HPP_
