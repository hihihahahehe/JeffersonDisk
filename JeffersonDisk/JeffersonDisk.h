#pragma once
#include <list>
#include <string>

class CJeffersonDisk
{
public:
   CJeffersonDisk();
   CJeffersonDisk(int nNumber_);
   CJeffersonDisk(const std::string& sAlphabet_, int nNumber_);
   CJeffersonDisk(const std::list<char>& pAlphabet_, int nNumber_);

   ~CJeffersonDisk();

public:
   bool RandomFill(const char* sMethod_);
   bool ReadFile(const char* sSrc_, int nNumber_);
   bool WriteFile(const char* sDst_);

public:
   void Turn(char cSymb_);
   int GetSymb(int nIndex_);
   int GetAlphabetLength() { return m_pAlphabet.size(); }

private:
   bool randomFillEn();

public:
   static int _GetAllCount() { return counter; }

private:
   static int counter;

   std::list<char>   m_pAlphabet;
   int               m_nNumber;

};
