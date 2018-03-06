#include "a3.h"
#include <string>
using namespace std;

SpellCheck::SpellCheck()
{
  root_ = nullptr;
  for (int i = 0; i < max; i++)
  {
    next[i] = nullptr;
  }
}
void SpellCheck::PreOrderTraverse(SpellCheck * node, string suggestions[], int& correct)
{

  if (node != nullptr)
  {
    if (node->isStr)
    {
      suggestions[correct] = node->value;  // set the first value to the stirng array
      correct++;
    }
    for (int i = 0; i < max; i++)  // 26 letters loop 26 times
    {
      PreOrderTraverse(node->next[i], suggestions, correct);
    }
  }
}
SpellCheck::SpellCheck(string data[],int sz){
  root_ = new SpellCheck();
  for (int i = 0; i < sz; i++)
    addWord(data[i]);
}
void SpellCheck::addWord(const string& newWord){
  if (root_ != nullptr && newWord.length() != 0)
  {
    SpellCheck *p = root_;
    int i;
    for (auto s = newWord.begin(); s != newWord.end(); s++)
    {
      if (p->next[*s - 'a'] == nullptr)
      {
        SpellCheck *temp = new SpellCheck();
        temp->isStr = false;
        p->next[*s - 'a'] = temp;
        p = p->next[*s - 'a'];
      }
      else
      {
        p = p->next[*s - 'a'];
      }
    }
    p->isStr = true;
    p->value = newWord;
  }
}
bool SpellCheck::lookup(const string& word) const{
  SpellCheck *p = root_;
  if (p != nullptr&&word.length() > 0)
  {
    for (auto s = word.begin(); s != word.end(); s++)
    {
      if (p->next[*s - 'a'] == nullptr)
        return false;
      p = p->next[*s - 'a'];
    }
  }
  return ( p!=nullptr&&p->isStr);
}
int SpellCheck::suggest(const string& partialWord, string suggestions[]) {
  SpellCheck *p = root_;
  int correct = 0;
  if (p != nullptr&&partialWord.length() > 0)
  {
    for (auto s = partialWord.begin(); s != partialWord.end(); s++) // find the start root
    {
      if (p->next[*s - 'a'] == nullptr)
        return false;
      p = p->next[*s - 'a'];
    }
    PreOrderTraverse(p, suggestions, correct);  // call preOrder function start from root(apple)
  }
  else
    return 0;
  return correct;
}
void SpellCheck::deleteMemory(SpellCheck * node)
{
  if (node != nullptr)
  {
    for (int i = 0; i < max; i++)  // use the post order delete memory
    {
      deleteMemory(node->next[i]);
    }
    if (node != nullptr)
      delete node;
  }
}
SpellCheck::~SpellCheck(){
  deleteMemory(root_);
}
