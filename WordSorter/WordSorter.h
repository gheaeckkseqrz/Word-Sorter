//
//  WordSorter.h
//  WordSorter
//
//  Created by Pierre WILMOT on 5/07/2014.
//  Copyright (c) 2014 WILMOT. All rights reserved.
//

#ifndef __WordSorter__WordSorter__
#define __WordSorter__WordSorter__

#include <iostream>
#include <map>
#include "Node.h"

class WordSorter
{
public:
    WordSorter();
    
    void                                    run();

protected:
    void                                    processInput(std::string const &i);
    bool                                    downloadWikiPage(std::string const &s);
    void                                    printStats();
    void                                    printNode(std::string const &node);
    void                                    list() const;
    
private:
    std::map<std::string, Node *>           _map;
    Node                                    *_previous;
    unsigned int                            _recordedWords;
};

#endif /* defined(__WordSorter__WordSorter__) */
