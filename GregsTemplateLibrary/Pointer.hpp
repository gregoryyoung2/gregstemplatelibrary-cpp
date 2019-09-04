//
//  Pointer.hpp
//  GregsTemplateLibrary
//
//  Created by Gregory Young on 9/3/19.
//  Copyright © 2019 Gregory Young. All rights reserved.
//

#ifndef Pointer_hpp
#define Pointer_hpp

#include <stdio.h>
#include <climits>
#include <iostream>

#include "Optional.hpp"

namespace GTL {

template <typename T> struct unownedpointer;

template <typename T>
struct internalpointer_t {
    T* address;
    unsigned short references;
    
    internalpointer_t(T *p = nullptr) {
        address = p;
        references = 1;
    }
};

template <typename T>
struct pointer {
    
private:
    internalpointer_t<T> *internal;
    
    void retain() {
#if DEBUG
        std::cout << "retain\n";
#endif
        internal->references++;
    }
    
    void release() {
#if DEBUG
        std::cout << "release\n";
#endif
        internal->references--;
        if (internal->references < 1 || internal->references == USHRT_MAX) {
#if DEBUG
            std::cout << "dealloc\n";
#endif
            delete internal->address;
            internal->address = nullptr;
            delete internal;
            internal = nullptr;
        }
    }
    
public:
    
    pointer(T *p) {
        internal = new internalpointer_t<T>(p);
    }
    
    pointer(T v) {
#if DEBUG
        std::cout << "alloc\n";
#endif
        T *address = new T(v);
        internal = new internalpointer_t<T>(address);
    }
    
    pointer() {
        internal = new internalpointer_t<T>(nullptr);
    }
    
    ~pointer() {
        release();
    }
    
    pointer(pointer &other) {
        other.retain();
        internal = other.internal;
    }
    
    
    pointer(unownedpointer<T> &other) {
        internal = other.internal;
        retain();
    }
    
    pointer(pointer &&other) noexcept {
        internal = other.internal;
        other.internal = new internalpointer_t<T>(nullptr);
    }
    
    pointer& operator=(const pointer &other) {
        release();
        other.retain();
        internal = other.internal();
        return *this;
    }
    
    pointer& operator=(T &other) {
#if DEBUG
        std::cout << "alloc\n";
#endif
        release();
        T *address = new T(other);
        internal = new internalpointer_t<T>(address);
        return *this;
    }
    
    pointer& operator=(const pointer &&other) noexcept {
        T prev = other.internal;
        other.internal = internal;
        internal = prev;
        return *this;
    }
    
    T* operator->() {
        return internal->address;
    }
    
    operator T() {
        return *(internal->address);
    }
    
    T* unsafePointer() {
        return internal->address;
    }
    
    unownedpointer<T> unownedPointer() {
        return unownedpointer<T>(*this);
    }
    
//    GTL::optional<T&> value() {
//        if (internal->address == nullptr) {
//            return GTL::nulloptional;
//        }
//        else {
//            return GTL::optional<T>(*(internal->address));
//        }
//    }
    
    inline bool isNull() {
        return internal->address == nullptr;
    }
    
    inline bool isNonNull() {
        return !isNull();
    }
    
    static pointer<T> retain(unownedpointer<T> p) {
        return pointer<T>(p);
    }

    friend struct unownedpointer<T>;
        
};


template <typename T>
struct unownedpointer {
    
private:
    internalpointer_t<T> *internal;
    
public:
    
    unownedpointer(pointer<T> &p) {
        internal = p.internal;
    }
    
    unownedpointer(unownedpointer &other) {
        internal = other.internal;
    }
    
    unownedpointer(unownedpointer &&other) noexcept {
        internal = other.internal;
        other.internal = new internalpointer_t<T>(nullptr);
    }
    
    unownedpointer& operator=(const pointer<T> &other) {
        internal = other.internal;
    }
    
    unownedpointer& operator=(const unownedpointer &other) {
        internal = other.internal;
        return *this;
    }
    
    unownedpointer& operator=(const unownedpointer &&other) noexcept {
        T prev = other.internal;
        other.internal = internal;
        internal = prev;
        return *this;
    }
    
    T* operator->() {
        return internal->address;
    }
    
    operator T() {
        return *(internal->address);
    }
    
    T* unsafePointer() {
        return internal->address;
    }
    
//    GTL::optional<T&> value() {
//        if (internal->address == nullptr) {
//            return GTL::nulloptional;
//        }
//        else {
//            return GTL::optional<T>(*(internal->address));
//        }
//    }
    
    inline bool isNull() {
        return internal->address == nullptr;
    }
    
    inline bool isNonNull() {
        return !isNull();
    }
    
    friend struct pointer<T>;
    
};

}


#endif /* Pointer_hpp */
