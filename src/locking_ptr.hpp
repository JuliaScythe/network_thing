#pragma once

#include <mutex>
#include <memory>

template <typename T>
class locking_ptr {
private:
  class accessor {
    friend locking_ptr;
  protected:
    accessor(locking_ptr<T> &ptr) : m_ptr(ptr) {
      ptr.m_mutex->lock();
    }
    locking_ptr<T> &m_ptr;
  public:
    ~accessor() {
      m_ptr.m_mutex->unlock();
    }

    T *operator->() {
      return m_ptr.m_inst.get();
    }
  };
  std::shared_ptr<T> m_inst;
  std::shared_ptr<std::mutex> m_mutex;
public:
  accessor lock() {
    return accessor(*this);
  }

  const locking_ptr &operator=(const locking_ptr &other) {
    m_inst = other.m_inst;
    m_mutex = other.m_mutex;
    return other;
  }

  locking_ptr() {
    m_inst = std::make_shared<T>();
    m_mutex = std::make_shared<std::mutex>();
  }

  locking_ptr(std::shared_ptr<T> inst) : m_inst(inst) {
    m_mutex = std::make_shared<std::mutex>();
  }
};

// vim: sw=2 et
