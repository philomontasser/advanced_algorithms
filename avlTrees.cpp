#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class avlNode
{
public:
    string word;
    avlNode * left;
    avlNode * right;
    int height;

    avlNode(string word)
    {
        this -> word = word;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class avlTree
{
public:

    avlNode * root;

    avlTree()
    {
        root = nullptr;
    }

    int height(avlNode * node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return node -> height;
        }
    }

    avlNode * rightRotate(avlNode * y)
    {
        avlNode * x = y -> left;
        avlNode * T2 = x -> right;

        x -> right = y;
        y -> left = T2;

        y -> height = 1 + max(height(y -> left), height(y -> right));
        x -> height = 1 + max(height(x -> left), height(x -> right));

        return x;
    }

    avlNode* leftRotate(avlNode * x)
    {
        avlNode* y = x -> right;
        avlNode* T2 = y -> left;

        y -> left = x;
        x -> right = T2;

        x -> height = 1 + max(height(x -> left), height(x -> right));
        y -> height = 1 + max(height(y -> left), height(y -> right));

        return y;
    }

    int balanceFactor(avlNode * node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return height(node -> left) - height(node -> right);
        }
    }

    avlNode * insert(avlNode * node, string word)
    {
        if (node == nullptr)
        {
            return new avlNode(word);
        }

        if (word < node -> word)
        {
            node -> left = insert(node -> left, word);
        }
        else if (word > node -> word)
        {
            node -> right = insert(node -> right, word);
        }
        else
        {
            return node;
        }

        node -> height = 1 + max(height(node -> left), height(node -> right));

        int balance = balanceFactor(node);

        if (balance > 1 && word < node -> left -> word)
        {
            return rightRotate(node);
        }

        if (balance < -1 && word > node -> right -> word)
        {
            return leftRotate(node);
        }

        if (balance > 1 && word > node -> left -> word)
        {
            node -> left = leftRotate(node -> left);
            return rightRotate(node);
        }

        if (balance < -1 && word < node -> right -> word)
        {
            node -> right = rightRotate(node -> right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(string word)
    {
        root = insert(root, word);
    }

    void findAllWithPrefix(avlNode* node, const string& prefix) 
    {
        if (!node) return;

        if (node->word >= prefix)
            findAllWithPrefix(node->left, prefix);

        if (node->word.find(prefix) == 0)
            cout << node->word << endl;

        if (node->word <= prefix + char(127))
            findAllWithPrefix(node->right, prefix);
    }

    void findAllWithPrefix(const string& prefix) 
    {
        findAllWithPrefix(root, prefix);
    }
};

vector<string> readWords()
{
    string filePath;
    cout << "file path: ";
    getline(cin, filePath);

    ifstream file(filePath);
    if (file.is_open() == 0)
    {
        cout << "could not open file " << filePath << endl;
        return {};
    }

    vector<string> words;
    string word;
    while (getline(file, word))
    {
        if (!word.empty())
        {
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

int main() 
{

    avlTree tree;

    vector<string> words = readWords(); 
    for (string w : words)
        tree.insert(w);

    string prefix;
    while (true)
    {
        cout << "prefix or 'exit' to quit: ";
        cin >> prefix;
        if (prefix == "exit") break;

        cout << "suggestions:" << endl;
        tree.findAllWithPrefix(prefix);
    }

    return 0;
}