#include "wordfrequency.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/**
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

WordFrequency::WordFrequency()
{
    // ToDo
    map = new WordFreqMap;

}

WordFrequency::~WordFrequency()
{
    // ToDo
    delete map;

}

void WordFrequency::ReadText(const char* filename)
{
    // ToDo
    map = new WordFreqMap;
    string file = filename;
    string content;
    string tmp;
    ifstream MyReadFile(file);
    while (getline(MyReadFile, tmp)) {
        content.append(" ");
        content.append(tmp);
    }

    std::replace(content.begin(), content.end(), '\'', ' ');
    std::replace(content.begin(), content.end(), '\"', ' ');
    std::replace(content.begin(), content.end(), ';', ' ');
    std::replace(content.begin(), content.end(), ':', ' ');
    std::replace(content.begin(), content.end(), '-', ' ');
    std::replace(content.begin(), content.end(), '.', ' ');
    std::replace(content.begin(), content.end(), '\?', ' ');
    std::replace(content.begin(), content.end(), ',', ' ');
    std::replace(content.begin(), content.end(), '\n', ' ');
    std::replace(content.begin(), content.end(), '\t', ' ');

    istringstream iss(content);
    do
    {
        string sub;
        iss >> sub;

        int i = 0;
        int len = sub.length();
        while(i<len) {
            if(!isalpha(sub[i])) {
                sub.erase(i, i+1);
                len--;
            }else
                i++;
        }

        std::transform(sub.begin(), sub.end(), sub.begin(), ::tolower);

        if (!sub.empty()){
            if(map->find(sub)) {
                WordFreqElem *tmp = map->find(sub);
                tmp->val += 1;
            }
            else {
                map->insert(sub, 1);
            }
        }
    } while (iss);
}

int WordFrequency::GetFrequency(const std::string word)
{
    // ToDo
    if (map->find(word))
    {
        WordFreqElem *tmp = map->find(word);
        return tmp->val;
    }
    else{
        return 0;
    }
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
    // ToDo
    if (map->find(word))
    {
        WordFreqElem *tmp = map->find(word);
        tmp->val +=1;
    }
    else{
        map->insert(word, 1);
    }
}
