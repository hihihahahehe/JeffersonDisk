#pragma once

#include <list>
#include <vector>

#include "JeffersonDisk.h"

class CJefferson
{
public:
   CJefferson();
   CJefferson(const char* sDst_);
   ~CJefferson() = default;

public:
   bool RandomFill(const char* sMethod_);
   bool ReadFile(const char* sDst_);
   bool WriteFile(const char* sDst_);
   bool GenDisks(const char* sDst_, const char* sMethod_ = "en");

   void SetKey(std::vector<int>& vKey_) { m_vKey = vKey_; }
   void ApplyKey();
   void ResetKey();

   void Turn(const std::string& sText_);
   std::string GetEncryptedMessage();
   void Reset() { m_pDisks = m_pDefaultDisks; }

private:
   static const int m_nCountOfDisks = 36;

   std::vector<int> m_vKey;

   std::list<CJeffersonDisk> m_pDisks;
   std::list<CJeffersonDisk> m_pDefaultDisks;

};

