
#include <sstream>
#include "WordSorter.h"

std::string             getWiki();


WordSorter::WordSorter()
{
    
}

void                                    WordSorter::run()
{
    std::string     s;
    do
    {
        if (s.find("wiki") == 0)
            downloadWikiPage(s.substr(4, s.length() - 3));
        if (s.find("print") == 0)
            printNode(s.substr(5, s.length() - 4));
        if (s.find("sentence") == 0)
            printSentence(s.substr(8, s.length() - 7));
        if (s.find("fullsentence") == 0)
            printSentence(s.substr(12, s.length() - 11), -1);
        else if (s == "stats")
            printStats();
        else if (s == "list")
            list();
        else if (s == "clear")
            for (int i(0) ; i < 50 ; ++i) std::cout << "\n\n\n\n\n\n\n" << std::endl;
        std::cout << ">> ";
    } while (std::getline(std::cin, s));
}

void                                    WordSorter::processInput(std::string const &i)
{
    std::string txt = i;
    char chars[] = "()-.,?!'«»’\":;[]";
    
    for (unsigned int i = 0; i < strlen(chars); ++i)
        txt.erase (std::remove(txt.begin(), txt.end(), chars[i]), txt.end());
    
    if (!txt.empty())
    {
        std::stringstream ss(txt);
        std::string s;
        while (ss >> s)
        {
            for (int i(0) ; i < s.size() ; ++i)
                s[i] = tolower(s[i]);
            if (!_map[s])
                _map[s] = new Node(s);
            else
                _map[s]->_occurences++;
            
            if (_previous)
                _previous->insertNext(_map[s]);
            
            _previous = _map[s];
            _recordedWords++;
        }
    }
    
}

bool                                    WordSorter::downloadWikiPage(std::string const &s)
{
    int nb = std::atoi(s.c_str());
    nb = (nb >= 1) ? nb : 1;
    
    for (int i(0) ; i < nb ; ++i)
    {
        if (nb > 1)
            std::cout << "====================[" << i+1 << "/" << nb << "]====================" << std::endl;
        std::string result = getWiki();
        if (result.empty())
            return false;
        std::cout << "Got : [" << result << "]" << std::endl;
        processInput(result);
    }
    return true;
}

void                                    WordSorter::printStats()
{
    int max(0);
    std::string mostUsed;
    for (auto n : _map)
    {
        if (n.second && max < n.second->_occurences)
        {
            max = n.second->_occurences;
            mostUsed = n.first;
        }
    }
    std::cout << "Recorded words : " << _recordedWords << std::endl;
    std::cout << "Unique words : " << _map.size() << std::endl;
    std::cout << "Most used word : [" << mostUsed << "] (" << max << " occurences)" << std::endl;
}

void                                    WordSorter::printNode(std::string const &node)
{
    std::stringstream ss(node);
    std::string s;
    
    ss >> s;
    for (int i(0) ; i < s.size() ; ++i)
        s[i] = tolower(s[i]);

    if (!_map[s])
        std::cout << "No entry for [" << s << "]" << std::endl;
    else
        _map[s]->printResult(1);
}

void                                    WordSorter::printSentence(std::string const &node, int length)
{
    std::stringstream ss(node);
    std::string s;
    
    ss >> s;
    for (int i(0) ; i < s.size() ; ++i)
        s[i] = tolower(s[i]);
    
    if (!_map[s])
        std::cout << "No entry for [" << s << "]" << std::endl;
    else
        std::cout << _map[s]->makeSentence(length) << std::endl;
}


void                                    WordSorter::list() const
{
    for (auto w : _map)
        if (w.second)
            std::cout << "[" << w.second->_occurences << "] - " << w.first << std::endl;
}