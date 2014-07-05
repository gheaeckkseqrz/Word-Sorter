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
    std::vector<Node *> usedWords;
    return makeSentence(usedWords, nbWord, s);
}

std::string                             Node::makeSentence(std::vector<Node *> &usedWords, int nbWord, std::string s)
{
    if (_next.empty())
    {
        std::cout << "\n" << _word << " has no successor" << std::endl;
    }
    
    if (nbWord == 0 || _next.empty())
        return s;
    
    if (!_sorted)
    {
        std::sort(_next.begin(), _next.end(), sortingFunctor());
        _sorted = true;
    }
    
    usedWords.push_back(this);
    for (auto it = _next.begin() ; it != _next.end() ; ++it)
    {
        if (std::find(usedWords.begin(), usedWords.end(), (*it).first) == usedWords.end())
        {
            return (*it).first->makeSentence(usedWords, nbWord - 1, s + " " + _word);
        }
    }
    std::cout << "Can't find anything unused to put after " << _word << std::endl;
    return s + " " + _word;
}