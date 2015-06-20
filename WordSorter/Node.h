#include <vector>
#include <iomanip>

struct sortingFunctor;

class Node
{
public:
  Node(std::string const &word)
    :_sorted(true), _word(word), _occurences(1)
    {
        
    }

    void                                    insertNext(Node *next);
    void                                    printResult(int depth);
    std::string                             makeSentence(int nbWord = 10, std::string s = "");
    std::string                             makeSentence( std::vector<Node *> &usedWords, int nbWord = 10, std::string s = "");

protected:
    void                                    insertPrevious(Node *previous);
    
public: //private:
    bool                                    _sorted;
    std::string                             _word;
    unsigned int                            _occurences;
    std::vector<std::pair<Node*, int> >     _next;
    std::vector<std::pair<Node*, int> >     _previous;
};

struct sortingFunctor
{
    inline bool operator() (const std::pair<Node*, int>& struct1, const std::pair<Node*, int>& struct2)
    {
        return (struct1.second > struct2.second);
    }
};
