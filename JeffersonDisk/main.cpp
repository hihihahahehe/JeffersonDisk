/*
   toDo:                                                                 
                                             (1)                         
                                    +class CJeffersonDisk  <------------+
                                       +std::list  alphabet             |
    (3)                                +int        numberOfDisk         |
 -ui class                                                              |
     |                                 +random fill disk                |
     |                                 +read   disk from file           |
     |                                 +write  disk to   file           |
     |                                                                  |
     |                                                                  |
     |         (2)                                                      |
     +->  -class Jefferson                                              |
             +write  disks    info  to    file                          |
             +read   disks    info  form  file                          |
             +random generate disks info                                |
                                                                        |
                                                                        |
             -encrypter                                                 |
                                                                        |
             -std::vector<int> key                                      |
             +std::vector<CJeffersonDisk> disks ------------------------+
*/

#include <iostream>
#include "Jefferson.h"

int main()
{
   std::cout << "Jefferson Encrypter\n" << std::endl;

   CJefferson jf("C:/Users/deleted/Desktop/JF.txt");

   jf.WriteFile("C:/Users/deleted/Desktop/JF_BEFORE_APPLY_KEY.txt");

   std::vector<int> vKey{ 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
   jf.SetKey(vKey);
   jf.ApplyKey();

   jf.WriteFile("C:/Users/deleted/Desktop/JF_AFTER_APPLY_KEY.txt");
   
   //jf.Turn("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
   jf.Turn("JZGGJVJGFFKKVOVRGOFONYDZZFLROWFNWQUNJZGGJVJGFFKKVOVRGOFONYDZZFLROWFNWQUNJZGGJVJZCNDVIQPJSTZTAXXHPASUWZFKHDPS");
   jf.WriteFile("C:/Users/deleted/Desktop/JF_TURNED.txt");

   std::cout << jf.GetEncryptedMessage();

   jf.Reset();

   return 0;
}