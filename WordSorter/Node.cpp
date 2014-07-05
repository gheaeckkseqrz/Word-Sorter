#include "Node.h"
#include <iostream>

void                                    Node::insertNext(Node *next)
{
    for (auto &e : _next)
    {
        if (e.first == next)
        {
            e.second++;
            return;
        }
    }
    _next.push_back(std::pair<Node *, int>(next, 1));
    _sorted = false;
}

void                                    Node::printResult(int depth)
{
    if (depth > 5)
        return;
    
    if (!_sorted)
    {
        std::sort(_next.begin(), _next.end(), sortingFunctor());
        _sorted = true;
    }
    
    std::cout << " ====== Result for [" << _word << "]" << std::endl;
    
    for (auto n : _next)
    {
        std::cout << "[" << n.second << "] - " << n.first->_word << " (" << n.first->_occurences << ")" << std::endl;
    }
    if (_next.empty())
        std::cout << "No succesors." << std::endl;
        
}

std::string                             Node::makeSentence(int nbWord, std::string s)
{
    if (_next.empty())
    {
        std::cout << _word << " has no successor" << std::endl;
    }
    
    if (nbWord == 0 || _next.empty())
        return s;
    
    if (!_sorted)
    {
        std::sort(_next.begin(), _next.end(), sortingFunctor());
        _sorted = true;
    }
    
    
    return _next[0].first->makeSentence(nbWord - 1, s + " [" + _word + "]");
}