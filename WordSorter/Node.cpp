#include "Node.h"
#include <iostream>

void                                    Node::insertNext(Node *next)
{
    for (auto &e : _next)
    {
        if (e.first == next)
        {
            e.second++;
            next->insertPrevious(this);
            _sorted = false;
            return;
        }
    }
    _next.push_back(std::pair<Node *, int>(next, 1));
    next->insertPrevious(this);
    _sorted = false;
}

void                                    Node::insertPrevious(Node *previous)
{
    for (auto &e : _previous)
    {
        if (e.first == previous)
        {
            e.second++;
            return;
        }
    }
    _previous.push_back(std::pair<Node *, int>(previous, 1));
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
    
    std::cout << " ========= Result for [" << _word << "]" << std::endl;
    std::cout << " === Next :" << std::endl;
    for (auto n : _next)
    {
        std::cout << "[" << n.second << "] - " << n.first->_word << " (" << n.first->_occurences << ")" << std::endl;
    }
    if (_next.empty())
        std::cout << "No succesors." << std::endl;
    std::cout << " === Previous :" << std::endl;
    for (auto n : _previous)
    {
        std::cout << "[" << n.second << "] - " << n.first->_word << " (" << n.first->_occurences << ")" << std::endl;
    }
    if (_previous.empty())
        std::cout << "No before." << std::endl;

}

std::string                             Node::makeSentence(int nbWord, std::string s)
{
    std::vector<Node *> usedWords;
    return makeSentence(usedWords, nbWord, s);
}

std::string                             Node::makeSentence(std::vector<Node *> &usedWords, int nbWord, std::string s)
{
    if (nbWord == 0 || _next.empty())
        return s;
    
    if (!_sorted)
    {
        std::sort(_next.begin(), _next.end(), sortingFunctor());
        std::sort(_previous.begin(), _previous.end(), sortingFunctor());
        _sorted = true;
    }
    
    s += " " + _word;
    usedWords.push_back(this);
    
    for (auto it = _next.begin() ; it != _next.end() ; ++it)
    {
        if (std::find(usedWords.begin(), usedWords.end(), (*it).first) == usedWords.end())
        {
            return (*it).first->makeSentence(usedWords, nbWord - 1, s);
        }
    }
    std::cout << "Can't find anything unused to put after " << _word << std::endl;
    return s;
}