#pragma once
#include <utility>

template <typename Type>
class Maybe {
   public:
    static Maybe<Type> Nothing() {
        return Maybe();
    }

    Maybe() : m_value(0), m_valid(false) {
    }

    Maybe(Type value) : m_value(value), m_valid(true) {
    }

    Maybe(Type& value) : m_value(value), m_valid(true) {
    }
    
    Maybe(Type&& value) : m_value(std::move(value)), m_valid(true) {
    }

    template <typename U>
    Maybe(U&& v) {
        m_value = std::forward<U>(v);
        m_valid = true;
    }

    Maybe(const Maybe& t) {
        m_valid = t.m_valid;
        m_value = t.m_value;
    }

    Maybe(Maybe&& t) {
        m_valid = std::move(t.m_valid);
        m_value = std::move(t.m_value);
    }

    Maybe& operator=(Maybe& other) {
        m_valid = other.m_valid;
        m_value = other.m_value;
        return *this;
    }

    Maybe& operator=(Maybe&& other) noexcept {
        if (this != &other) {
            m_valid = std::move(other.m_valid);
            m_value = std::move(other.m_value);
        }
        return *this;
    }

    bool isValid() {
        return m_valid;
    }
    
    Type getValue() {
        // assert(isValid());
        return m_value;
    }

   private:
    Type m_value;
    bool m_valid;
};