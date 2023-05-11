//Haya Shalaby, Rana Taher, Jana Elmidany
#ifndef _PLAGIARISMCHECKER_H
#define _PLAGIARISMCHECKER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pattern.h"
#include "Document.h"
using namespace std;

class PlagiarismChecker {
    private:
        int totalPlag;
        int totalRef;
        int totalSim;
        int totalQuotes;
        Document userDoc;
        vector<Document> database;
        vector<int> quoteIndex;
        Document highlightDoc;
        bool match ;
    public:
        PlagiarismChecker();
        PlagiarismChecker(string userFile); //opens userFile and ogFile
        bool isQuote(string line); //checks if similar line is a quotation & increments totalQuotes if true
        bool isRef(string sent);  //looks for reference page & adds count of all words starting there to totalRef
        void calcPlag(); //calculates totalPlag by subtracting totalRef and totalQuotes from totalSim
        void compDoc(); //compares userDoc against database for similarity, produces highlighted document
        int getTotalPlag(); //getter for totalPlag
        int getTotalRef(); //getter for totalRef
        int getTotalSim(); //getter for totalSim
        int getTotalQuotes(); //getter for totalQuotes
        Document getHighlightDoc(); //getter for highlightDoc
        void createCorpus();//enters the files into the vector
        void compLines(vector <string> data , vector <string> user);
        vector <string> getPat(string sentence);// gets the pattern of the sentence
        void stringMatching(string pat, string txt,long threshold,bool &match); //brute force & rabin karp
        int countWords(string sentence);
        int hammingDistance(string str1, string str2);
        bool rabinKarpSearch(string pattern, string text, int q);
    vector <string> createPat(vector <string> pats);
       
};

#endif //_PLAGIARISMCHECKER_H

