#include "Jefferson.h"
#include "JeffersonDisk.h"

#include <cmath>
#include <random>

// ================================================
CJefferson::CJefferson()
{
   for (int i = 0; i < m_nCountOfDisks; ++i)
      m_pDefaultDisks.emplace_back(CJeffersonDisk(i + 1));

   ResetKey();
}

CJefferson::CJefferson(const char* sDst_)
{
   for (int i = 0; i < m_nCountOfDisks; ++i)
      m_pDefaultDisks.emplace_back(CJeffersonDisk());

   ResetKey();

   ReadFile(sDst_);
}

// ================================================
bool CJefferson::RandomFill(const char* sMethod_)
{
   if (m_pDefaultDisks.empty())
      return false;

   for (auto& elem : m_pDefaultDisks)
      elem.RandomFill(sMethod_);

   m_pDisks = m_pDefaultDisks;

   return true;
}

bool CJefferson::ReadFile(const char* sDst_)
{
   if (m_pDefaultDisks.empty())
      return false;

   int count = 0;
   for (auto& elem : m_pDefaultDisks)
      elem.ReadFile(sDst_, count++);

   m_pDisks = m_pDefaultDisks;

   return true;
}

bool CJefferson::WriteFile(const char* sDst_)
{
   if (m_pDisks.empty())
      return false;

   for (auto& elem : m_pDisks)
      elem.WriteFile(sDst_);

   return true;
}

bool CJefferson::GenDisks(const char* sDst_, const char* sMethod_)
{
   RandomFill(sMethod_);
   WriteFile(sDst_);

   return true;
}

void CJefferson::ApplyKey()
{
   std::list<CJeffersonDisk> keyDisks;
   for (int i = 0; i < m_pDisks.size(); ++i)
   {
      auto it = m_pDisks.begin();
      std::advance(it, (m_vKey[i] - 1) );

      keyDisks.emplace_back(*it);
   }

   m_pDisks = keyDisks;
}

void CJefferson::ResetKey()
{
   for (int i = 0; i < m_pDisks.size(); ++i)
      m_vKey.push_back(i + 1);

   m_pDisks = m_pDefaultDisks;
}

// ================================================
void CJefferson::Turn(const std::string& sText_)
{
   const size_t textSize = sText_.size();
   int multiplie = std::ceill(textSize / static_cast<double>(m_pDisks.size()) );

   std::list<CJeffersonDisk> newDisks;

   for (int i = 0; i < multiplie; ++i)
      for (const auto& disk : m_pDisks)
         newDisks.emplace_back(disk);

   for (int i = 0; i < textSize; ++i)
   {
      auto it = newDisks.begin();
      std::advance(it, i);
      it->Turn(sText_[i]);
   }

   m_pDisks = newDisks;
}

std::string CJefferson::GetEncryptedMessage()
{
   std::random_device               rd;
   std::mt19937                     gen(rd());
   std::uniform_int_distribution<>  dist(1, static_cast<int>(m_pDisks.begin()->GetAlphabetLength() - 1));

   int index = dist(gen);

   std::string message{ "" };
   for (auto& elem : m_pDisks)
      message += elem.GetSymb(index);

   return message;
}
