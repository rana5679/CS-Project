#include <string>
#include <vector>
#include <ctype.h>
#include "PlagiarismChecker.h"
#include "Document.h"
using namespace std;
 
// d is the number of characters in the input alphabet //for stringMatching
#define d 256

PlagiarismChecker::PlagiarismChecker()
{
  userDoc=Document();

  totalPlag = 0;
  totalRef = 0;
  totalSim = 0;
  totalQuotes = 0;
    match=false;
}

PlagiarismChecker::PlagiarismChecker(string userFile)
{
 

  userDoc=Document(userFile);
  createCorpus();

}

void PlagiarismChecker::createCorpus()
{
  int size;
  string filename;
  Document corpus;

  cout<<"Enter the number of files you want to check from "<<endl;
  cin>>size;

  cout<<"Enter names of files"<<endl;
  
  for(int i=0; i<size ; i++)
    {
      cin>>filename;

      corpus=Document(filename+".txt");
      database.push_back(corpus);
    }
}

bool PlagiarismChecker::isQuote(string Line) {
  totalQuotes = 0;
  if(Line[0] == '"' && Line[Line.length() - 2] == '"')
    {
      return true;
      
    }
      
  
  return false;
}

bool PlagiarismChecker::isRef(string sent)
{
  if(sent.substr(0,10) == "References" || sent.substr(0,11) == "Works Cited" ) //or should it be sent == "References"
  {
     return true;
  }
  return false;
}

void PlagiarismChecker::calcPlag()
{
  totalPlag = totalSim - (totalQuotes + totalRef);
}

void PlagiarismChecker::compDoc() // We will count the words for refrences and quotes here -rana
{
  vector <string> dataLines,userLines;
  userLines=userDoc.getLines();
  for(int i=0 ; i<database.size() ; i++)
  {
    dataLines=database[i].getLines();
    compLines(dataLines,userLines);
     
    
  }
    cout<<"The number of words in a quotation: "<<totalQuotes<<endl;
    cout<<"The number of words in refrences: "<<totalRef<<endl;
    calcPlag();
    cout<<"The number of words that are plagiraised: "<<totalPlag<<endl;
}

vector <string> PlagiarismChecker::createPat(vector <string> patterns)
{
    string temp;
    int count=0;
    vector <string> fullPats;
    
    for(int s=0 ; s<fullPats.size()+1 ; s++)
    {
        temp="";
        
        while(count<6)
        {
            temp += patterns[count];
            count++;
        }
        fullPats.push_back(temp);
        patterns.erase(patterns.begin());
    }
    
    return fullPats;
}

void PlagiarismChecker::compLines(vector <string> data , vector <string> user) // We will count the words for refrences and quotes here
{
    
    string sent;
 // long Start=0;
  long threshold;
    bool x;
    
    vector <string> patterns;
    vector <string> fullPats;
 // int count_while=0;
  //int count_space=0;
  for(int j=0; j<user.size(); j++)
  {
      patterns=getPat(user[j]);
      sent=user[j];
      threshold=user[j].length()/2;
      
      fullPats=createPat( patterns);
     
          x=isRef(sent);
          
          if(x==true)
          {
            cout<<"The remaining is refreneces"<<endl;
              for(int in=j ; in<user.size() ; in++)
              {
                  totalRef += countWords(user[in]);
                  totalSim += countWords(user[j]);
              }
              break;
          }
          else if(isQuote(sent))
            {
              cout<<"a quote was found"<<endl;
              totalQuotes+=countWords(sent);
              totalSim += countWords(user[j]);
            }
          else
          {
              for(int index=0 ; index<fullPats.size() ;index++ ){
                  for(int k=0 ; k<data[k].size() ; k++)
                  {
                       
                        stringMatching(fullPats[index],data[k],threshold,match);
                          //rabinKarpSearch( pat.pattern, data[k] , 5);
                      if(match)
                      {
                          cout<<"correct"<<endl;
                          totalSim += countWords(user[j]);
                          
                      }
                  }
              }
          }
      }
}

void PlagiarismChecker::stringMatching(string pat, string txt,long threshold, bool &match)
{
    
    long n=txt.length();
    long m=pat.length();
    int distance;
    
    for (int i = 0; i <= n-m; i++)
    {
        // Check for exact matches using Rabin-Karp algorithm
        if (rabinKarpSearch(pat, txt, 101)) {
            match=true;
        }
        // Check for approximate matches using Hamming distance
        else {
            distance = hammingDistance( pat, txt);
            if (distance <= threshold) {
                match=true;
            }
        }
    }
}

 vector <string> PlagiarismChecker::getPat(string sentence)
  {
     vector <string> pattern;
     string temp;
     
     for(int i=1 ; i<sentence.length() ; i++)
     {
          temp="";
         
         while(sentence[i]!=' ')
         {
             temp += sentence[i];
         }
         
         pattern[i]=temp;
     }
     
     return pattern;
     
  }

int PlagiarismChecker::hammingDistance(string str1, string str2)
{
    int distance = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}

bool PlagiarismChecker::rabinKarpSearch(string pat, string txt , int q)
{
        long M = pat.length();
        long N = txt.length();
        int i, j;
        int p = 0; // hash value for pattern
        int t = 0; // hash value for txt
        int h = 1;

        // The value of h would be "pow(d, M-1)%q"
        for (i = 0; i < M - 1; i++)
            h = (h * d) % q;

        // Calculate the hash value of pattern and first
        // window of text
        for (i = 0; i < M; i++) {
            p = (d * p + pat[i]) % q;
            t = (d * t + txt[i]) % q;
        }

        // Slide the pattern over text one by one
        for (i = 0; i <= N - M; i++) {

            // Check the hash values of current window of text
            // and pattern. If the hash values match then only
            // check for characters one by one
            if (p == t) {
                /* Check for characters one by one */
                for (j = 0; j < M; j++) {
                    if (txt[i + j] != pat[j]) {
                        break;
                    }
                }

                // if p == t and pat[0...M-1] = txt[i, i+1,
                // ...i+M-1]

                if (j == M)
                    cout << "Pattern found at index " << i
                         << endl;
            }

            // Calculate hash value for next window of text:
            // Remove leading digit, add trailing digit
            if (i < N - M) {
                t = (d * (t - txt[i] * h) + txt[i + M]) % q;

                // We might get negative value of t, converting
                // it to positive
                if (t < 0)
                    t = (t + q);
            }
        }
    return false;
}


int PlagiarismChecker::getTotalPlag()
{
  return totalPlag;
}

int PlagiarismChecker::getTotalRef()
{
  return totalRef;
}

int PlagiarismChecker::getTotalSim()
{
  return totalSim;
}

int PlagiarismChecker::getTotalQuotes()
{
  return totalQuotes;
}

Document PlagiarismChecker::getHighlightDoc(){
  return highlightDoc;
}

int PlagiarismChecker::countWords(string sentence){
    int count = 0 ;/*, i=0;
  while (sentence[i]==' '){ //tab doesnt work
    i++;
  }
  for (int j=i-1; j < sentence.length(); j++) {
    if(sentence[j]==' '){
      count++;
    }
  }*/

    for(int i=0 ; i<sentence.length() ; i++)
    {
        if((sentence[i] ==' ' || sentence[i] =='.' || sentence[i] ==',' || sentence[i] ==';') && ((sentence[i+1]>='a' || sentence[i+1]<='z') || (sentence[i+1]>='A' || sentence[i+1]<='Z')))
        {
            count++;
        }
    }
    
  return count-1;
}

/*vector<int> plagiarismDetector(string document, string pattern, int threshold) {
    vector<int> matches;
    long n = document.length();
    long m = pattern.length();
    int distance;

    for (int i = 0; i <= n-m; i++) {
        // Check for exact matches using Rabin-Karp algorithm
        if (rabinKarpSearch(pattern, document.substr(i, m), 256, 101)) {
            matches.push_back(i);
        }
        // Check for approximate matches using Hamming distance
        else {
            distance = hammingDistance(pattern, document.substr(i, m));
            if (distance <= threshold) {
                matches.push_back(i);
            }
        }
    }

    return matches;
}*/



