#include "Chaining.h"

void Chaining::createAccount(std::string id, int count=0)
{
    // IMPLEMENT YOUR CODE HERE
    Account a;
    a.id = id;
    a.balance = count;
    int hs = hash(id);
    if (hs >= bankStorage2d.size())
    {
        for(int i=0;i<=100000;i++){
            Account test;
            test.balance=-1;
            test.id="";
            std::vector<Account> v;
            v.push_back(test);
            bankStorage2d.push_back(v);
        }
    }
    if(count>=0 && bankStorage2d[hs][0].balance>-1){
        bankStorage2d[hs].push_back(a);
        Insert(count);
        size++;
    }
    else if(count>=0 && bankStorage2d[hs][0].balance==-1){
        bankStorage2d[hs][0].balance=count;
        bankStorage2d[hs][0].id=id;
        Insert(count);
        size++;
    }
}

std::vector<int> Chaining::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> v;
    int last = sorted.size() - 1;
    while (k > 0 && last >= 0)
    {
        v.push_back(sorted[last]);
        k--;
        last--;
    }
    return v; // Placeholder return value
}

int Chaining::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id))
    {
        return bankStorage2d[hash(id)][position].balance;
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id))
    {
        int idx = BinarySearch(bankStorage2d[hash(id)][position].balance);
        if(bankStorage2d[hash(id)][position].balance+count>=0){
            bankStorage2d[hash(id)][position].balance += count;
            sorted.erase(sorted.begin() + idx);
            Insert(bankStorage2d[hash(id)][position].balance);
        }
    }
    else if (!doesExist(id) && count >= 0)
    {
        createAccount(id, count);
    }
}

bool Chaining::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    if(size>0){
        if (bankStorage2d[h].size() > 0)
        {
            for (int i = 0; i < bankStorage2d[h].size(); i++)
            {
                if (bankStorage2d[h][i].id == id)
                {
                    position = i;
                    return true;
                }
            }
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int hashed = hash(id);
    if (doesExist(id))
    {
        int idx = BinarySearch(bankStorage2d[hashed][position].balance);
        sorted.erase(sorted.begin() + idx);
        bankStorage2d[hashed].erase(bankStorage2d[hashed].begin() + position);
        size--;
        return true;
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    long long h = int(id[0]) * int(id[1]) * int(id[2]) * int(id[3]);
    std::string s1 = id.substr(4, 3);
    std::string s2 = id.substr(7, 4);
    std::string s3 = id.substr(12, 5);
    std::string s4 = id.substr(17, 5);
    long long p2 = std::stoi(s1) ^ std::stoi(s2);
    long long p3 = std::stoi(s3) + std::stoi(s4);
    h ^= p2;
    h = (h << 7) | (h >> 25);
    h ^= p3;
    h = (h << 12) | (h >> 20);
    return h % 100000; 
}

void Chaining::Insert(int n)
{
    if (sorted.size() == 0)
    {
        sorted.push_back(n);
    }
    else if (Binary(n) != -1)
    {
        int index = Binary(n);
        sorted.insert(sorted.begin() + index, n);
    }
}

int Chaining::Binary(int n)
{
    int start = 0;
    int end = sorted.size() - 1;
    while ((end - start) > 1)
    {
        int mid = (start + end) / 2;
        if (n >= sorted[mid])
        {
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    if (sorted[start] < n && sorted[end] > n)
    {
        return start + 1;
    }
    else if (sorted[end] <= n)
    {
        return end + 1;
    }
    else if (sorted[start] >= n)
    {
        return start;
    }
    else
    {
        return -1;
    }
}

int Chaining::BinarySearch(int n)
{
    int start = 0;
    int end = sorted.size() - 1;
    while ((end - start) > 1)
    {
        int mid = (start + end) / 2;
        if (n >= sorted[mid])
        {
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    if (sorted[start] == n)
    {
        return start;
    }
    else if (sorted[end] == n)
    {
        return end;
    }
    else
    {
        return -1;
    }
}