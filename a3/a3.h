#ifndef A3_H
#define A3_H
#include <string>
using namespace std;
const int max = 26;
class SpellCheck{
  bool isStr;                             
  SpellCheck  *next[max];            
  SpellCheck *root_;
  string value;
public:
  SpellCheck();
  void PreOrderTraverse(SpellCheck* node, string suggestions[],int& correct);
	SpellCheck(string data[],int sz);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]);
  void deleteMemory(SpellCheck* node);
	~SpellCheck();	
};
#endif