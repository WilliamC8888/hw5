#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void buildWords(std::string& curr,const std::string& in,std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    if(in.empty()){ //handle empty input
      return results;
    }

    std::string curr = in;
    buildWords(curr, in, floating, 0, dict, results);
    return results;
}

// Define any helper functions here
void buildWords(std::string& curr, const std::string& in, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results){
    if(index == in.size()){
        if(floating.empty() && dict.find(curr) != dict.end()){
            results.insert(curr);
        }
        return;
  }

  if(in[index] != '-') {
    curr[index] = in[index];
    buildWords(curr, in, floating, index + 1, dict, results);
  }
  else{
    for(char letter = 'a'; letter <= 'z'; ++letter){
      curr[index] = letter;
      size_t pos = floating.find(letter);
      if(pos != std::string::npos){
        std::string newFloating = floating;
        newFloating.erase(pos, 1);
        buildWords(curr, in, newFloating, index + 1, dict, results);
      }
      else{
        if(in.size() - index > floating.size()){
          buildWords(curr, in, floating, index + 1, dict, results);
        }
      }
    }
  }
}
