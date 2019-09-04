//
//  Optional.hpp
//  GregsTemplateLibrary
//
//  Created by Gregory Young on 9/3/19.
//  Copyright © 2019 Gregory Young. All rights reserved.
//

#ifndef Optional_hpp
#define Optional_hpp

namespace GTL {

struct nulloptional_t {
    nulloptional_t() {}
};

static nulloptional_t nulloptional = nulloptional_t();

template <typename T>
struct optional {
public:
    
    optional(): none(true) {}
    
    optional(const T& v): value(v), none(false) {}
    
    inline bool isNull() {
        return none;
    }
    
    inline bool isNonNull() {
        return !none;
    }
    
    T& operator!() {
        return value;
    }
    
    const T& operator!() const {
        return value;
    }
    
    inline optional& operator=(const optional& other) {
        none = other.none;
        if (other.isNonNull()) {
            value = other.value;
        }
        return *this;
    }
    
    inline optional& operator=(const T& other) {
        none = false;
        value = other;
        return *this;
    }
    
    inline optional& operator=(const nulloptional_t& other) {
        none = true;
        return *this;
    }
    
    
private:
    bool none;
    T value;
};

}





#endif /* Optional_hpp */
