#include "JeffersonDisk.h"

#include <random>
#include <fstream>


// ================================================
int CJeffersonDisk::counter = 0;

// ================================================
CJeffersonDisk::CJeffersonDisk()
{
   RandomFill("en");

   ++counter;

   m_nNumber = counter;
}

CJeffersonDisk::CJeffersonDisk(int nNumber_)
{
   RandomFill("en");

   ++counter;

   m_nNumber = nNumber_;
}

CJeffersonDisk::CJeffersonDisk(const std::string& sAlphabet_, int nNumber_)
{
   m_nNumber = nNumber_;
   for (auto const& symb : sAlphabet_)
      m_pAlphabet.emplace_back(symb);

   ++counter;
}

CJeffersonDisk::CJeffersonDisk(const std::list<char>& pAlphabet_, int nNumber_)
{
   m_nNumber = nNumber_;
   m_pAlphabet = pAlphabet_;

   ++counter;
}

CJeffersonDisk::~CJeffersonDisk()
{
   m_nNumber = 0;
   m_pAlphabet.clear();

   --counter;
}

// ================================================
bool CJeffersonDisk::RandomFill(const char* sMethod_)
{
   if (sMethod_ == "en")
      return randomFillEn();

   return false;
}

bool CJeffersonDisk::ReadFile(const char* sSrc_, int nNumber_)
{
   std::ifstream in(sSrc_, std::ios::in|std::ios::binary);
   if (!in)
      return false;

   std::string temp;
   for (int i = 0; i < nNumber_; ++i)
      std::getline(in, temp);

   in >> m_nNumber;

   std::string sAlph{ "" };
   std::getline(in, temp);
   for(const auto& elem : temp)
   {
      if (elem == ' ' || elem == '\r' || elem == '\t' || elem == '\n')
         continue;

      sAlph.push_back(elem);
   };

   m_pAlphabet.clear();

   for (auto const& symb : sAlph)
      m_pAlphabet.emplace_back(symb);

   in.close();
   return true;
}

bool CJeffersonDisk::WriteFile(const char* sDst_)
{
   std::ofstream out(sDst_, std::ios::app|std::ios::out|std::ios::binary);
   if (!out)
      return false;

   if (m_nNumber > 9)
      out << m_nNumber;
   else
      out << 0 << m_nNumber;

   out << '\t';

   std::_List_iterator it = m_pAlphabet.begin();
   for (size_t i = 0; i < m_pAlphabet.size(); ++i)
      out << *it++;

   out << '\n';

   out.close();
   return true;
}

// ================================================
void CJeffersonDisk::Turn(char cSymb_)
{
   int index = 0;
   for (const auto& elem : m_pAlphabet)
   {
      if (elem == cSymb_)
         break;

      ++index;
   }

   std::list<char> newAlphabet;
   for (int i = index; i < m_pAlphabet.size() + index; ++i)
   {
      auto it = m_pAlphabet.begin();
      std::advance(it, (i % m_pAlphabet.size() ));
      char x = *it;
      newAlphabet.emplace_back(x);
   }

   m_pAlphabet.clear();
   m_pAlphabet = newAlphabet;
}

int CJeffersonDisk::GetSymb(int nIndex_)
{
   auto it = m_pAlphabet.begin();
   std::advance(it, nIndex_);

   return *it;
}

// ================================================
bool CJeffersonDisk::randomFillEn()
{
   std::string sAlph = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

   std::random_device               rd;
   std::mt19937                     gen(rd());
   std::uniform_int_distribution<>  dist(0, static_cast<int>(sAlph.size() - 1));

   for (size_t i = 0; i < sAlph.size() * 2; ++i)
   {
      int nFirst = dist(gen);

      int nSecond = 0;
      do
      {
         nSecond = dist(gen);
      } while (nFirst == nSecond);

      std::swap(sAlph[nFirst], sAlph[nSecond]);
   }

   m_pAlphabet.clear();

   for (auto const& symb : sAlph)
      m_pAlphabet.emplace_back(symb);

   return true;
}
