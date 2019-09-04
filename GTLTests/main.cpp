//
//  main.cpp
//  GTLTests
//
//  Created by Gregory Young on 9/3/19.
//  Copyright © 2019 Gregory Young. All rights reserved.
//

#include <iostream>
#include <string>
#include "Optional.hpp"
#include "Pointer.hpp"

using namespace std;
using namespace GTL;

struct Message;

void realMain();
pointer<string> getTitle();
void messagePrinter(pointer<Message> message);

struct Message {
    string title;
    string message;
  
    Message(string t, string m): title(t), message(m) {}
};

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    optional<string> name;
    string val = "Greg";
    name = val;
    cout << "Hello, " << !name << "!\n";
    realMain();
    return 0;
}

void thingsYouCanDo() {
    auto stackMessage = Message("Stack Message", "This message belongs on the stack");
    pointer<Message> message = Message("Hello", "This is a message retained by this pointer");
    pointer<Message> heapMessage = stackMessage; // now our stack message is retained
    auto unowned = heapMessage.unownedPointer(); // this doesn't really do much different than unsafe pointer
    auto unsafe = heapMessage.unsafePointer();
    if (unowned.isNonNull()) {
        cout << unowned->message << endl;
    }
    if (unsafe != nullptr) {
        cout << unsafe->message << endl;
    }
}


void realMain() {
    pointer<Message> message = Message(getTitle(), "Hello World!");
    messagePrinter(message);
}

pointer<string> getTitle() {
    pointer<string> title = string("Hello");
    return title;
}


void messagePrinter(pointer<Message> message) {
    cout << message->title << endl << message->message << endl;
}
