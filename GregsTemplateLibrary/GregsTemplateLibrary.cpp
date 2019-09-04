//
//  GregsTemplateLibrary.cpp
//  GregsTemplateLibrary
//
//  Created by Gregory Young on 9/3/19.
//  Copyright © 2019 Gregory Young. All rights reserved.
//

#include <iostream>
#include "GregsTemplateLibrary.hpp"
#include "GregsTemplateLibraryPriv.hpp"

void GregsTemplateLibrary::HelloWorld(const char * s)
{
    GregsTemplateLibraryPriv *theObj = new GregsTemplateLibraryPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void GregsTemplateLibraryPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

