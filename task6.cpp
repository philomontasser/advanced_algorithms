#include <iostream>
#include <vector>
#include <array>
using namespace std;

class coin
{
public:
    int realWeight = 1;
    int fakeWeight = 2;
    int weight;

    coin(string type)
    {
        if (type == "real")
            weight = realWeight;
        else
            weight = fakeWeight;
    }
};

coin* if_not_make_even(vector<coin>& coins)
{
    coin* coinLast = nullptr;
    if (coins.size() % 2 != 0 && coins.size() > 3)
    {
        coinLast = &coins.back();
        coins.pop_back();
    }
    return coinLast;
}

array<int, 2> weigh_sides(const vector<coin>& coins)
{
    int leftWeight = 0;
    int rightWeight = 0;
    int half = coins.size() / 2;

    for (int i = 0; i < half; i++)
        leftWeight += coins[i].weight;

    for (int i = half; i < coins.size(); i++)
        rightWeight += coins[i].weight;

    return {leftWeight, rightWeight};
}

bool is_balanced(array<int, 2> weights)
{
    return weights[0] == weights[1];
}

void heavier_or_lighter(vector<coin>& coins)
{
    coin* coinLast = if_not_make_even(coins);

    if (coins.size() < 3)
    {
        cout << "Not enough coins to determine fake." << endl;
        return;
    }

    coin& A = coins[0];
    coin& B = coins[1];
    coin& C = coins[2];

    if (A.weight == B.weight)
    {
        coin& reference = A;

        if (coinLast != nullptr)
        {
            if (coinLast->weight > reference.weight)
                cout << "Fake coin is heavier (last coin)" << endl;
            else if (coinLast->weight < reference.weight)
                cout << "Fake coin is lighter (last coin)" << endl;
            return;
        }

        if (C.weight > reference.weight)
            cout << "Fake coin is heavier (C)" << endl;
        else if (C.weight < reference.weight)
            cout << "Fake coin is lighter (C)" << endl;
    }
    else
    {
        if (A.weight == C.weight)
        {
            if (B.weight > A.weight)
                cout << "Fake coin is heavier (B)" << endl;
            else
                cout << "Fake coin is lighter (B)" << endl;
        }
        else
        {
            if (A.weight > C.weight)
                cout << "Fake coin is heavier (A)" << endl;
            else
                cout << "Fake coin is lighter (A)" << endl;
        }
    }
}

int main()
{
    vector<coin> coins = {coin("real"), coin("real"), coin("fake"), coin("real"), coin("real")};

    heavier_or_lighter(coins);

    return 0;
}
