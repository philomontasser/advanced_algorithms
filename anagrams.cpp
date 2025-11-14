#include <iostream>
using namespace std;

bool isAnagram(string word1, string word2)
{
    if (word1.length() != word2.length())
        return false;
    for (int i = 0; i < word1.length(); i++)
    {
        int charFound = 0;
        for (int j = 0; j < word2.length(); j++)
        {
            if (word1[i] == word2[j])
            {
                charFound++;
                word2.erase(j, 1);
                break;
            } 
        }
        if (charFound == 0)
        {
            return false;
        }
    }
    return true;
    
}



int main()
{
    cout << isAnagram("acbd", "bacd");
    return 0;
}