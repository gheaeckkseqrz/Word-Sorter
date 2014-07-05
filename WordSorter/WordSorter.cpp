
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
        if (s == "wiki")
            downloadWikiPage(s);
        else if (s == "stats")
            printStats();
        else if (s == "list")
            list();
        std::cout << ">> ";
    } while (std::cin >> s);
}

void                                    WordSorter::processInput(std::string const &i)
{
    std::string txt = i;
    char chars[] = "()-.,?!'«»’\":;";
    
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
    std::string result = getWiki();
    if (result.empty())
        return false;
    std::cout << "Got : [" << result << "]" << std::endl;
    processInput(result);
    return true;
}

void                                    WordSorter::printStats()
{
    int max(0);
    std::string mostUsed;
    for (auto n : _map)
    {
        if (max < n.second->_occurences)
        {
            max = n.second->_occurences;
            mostUsed = n.first;
        }
    }
    std::cout << "Total words : " << _map.size() << std::endl;
    std::cout << "Most used word : [" << mostUsed << "] (" << max << " occurences)" << std::endl;
}

void                                    WordSorter::printNode(std::string const &node)
{
    std::cout << node << std::endl;
}

void                                    WordSorter::list() const
{
    for (auto w : _map)
        std::cout << "[" << w.second->_occurences << "] - " << w.first << std::endl;
}