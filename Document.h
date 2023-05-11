// Jana Elmidany, Haya Shalaby, Rana Taher
#ifndef _DOCUMENT_H
#define _DOCUMENT_H
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Document {
private:
  string fileName;
  vector<string> lines;
  int numOfWords;

public:
  Document();
  Document(string); // constructor, opens file FN, stores lines in vector lines
  void setFileName(string);  // Sets file name
  void setLines(string);     // Sets lines
  void addLine(string);      // Adds lines
  int numOfLines();          // Returns number of lines
  string getFileName();      // getter for fileName
  vector<string> getLines(); // getter for vector lines
  int getNumWords();         // returns no. of words in the document
  int countWords(string);    // Counts number of words in a sentence
};

#endif //_DOCUMENT_H

