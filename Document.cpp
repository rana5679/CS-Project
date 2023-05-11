#include "Document.h"
#include <vector>
#include <iostream>
using namespace std;

Document::Document() {
  fileName = "";
  numOfWords = 0;
}

Document::Document(string FN) {
  setFileName(FN);
  setLines(FN);
}

void Document::setFileName(string FN) { fileName = FN; }

void Document::setLines(string FN) {
  fstream file;
  file.open(FN);
  string temp;
  int words =0, numOfWords = 0;
  while (!file.eof()) {
    getline(file, temp, '.');
    lines.push_back(temp);
    words = countWords(temp);
    numOfWords = numOfWords + words;
  }
  cout << numOfWords << endl;
}

void Document::addLine(string sentence) {
  lines.push_back(sentence);
  int words = countWords(sentence);
  numOfWords += words;
}

string Document::getFileName() { return fileName; }

vector<string> Document::getLines() { return lines; }

int Document::numOfLines()
{
    double L=lines.size();
    return L;
    
}

int Document::getNumWords() { return numOfWords; }

int Document::countWords(string sentence) {
  int count = 1, i=0;
  while (sentence[i]==' '){ //tab doesnt work
    i++;
  }
    for (int j=i; j < sentence.length(); j++) {
    if(sentence[j]==' '){
      count++;
    }
  }
  return count;
}

