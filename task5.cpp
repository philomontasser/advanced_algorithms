#include <iostream>
#include <algorithm>
using namespace std;


void arrange(char arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int j = i;
        while(arr[j] == 'l' && arr[j - 1] != 'l')
        {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}


int main()
{
    char arr[] = {'l','d','l','l','d','l','d','l','d','d'};
    int size = 10;
    arrange(arr, size);
    for(int i=0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}