#include "LinearProbing.h"

void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called createAccount"<<std::endl;
    Account a;
    a.id = id;
    a.balance = count;
    int hs = hash(id);
    if (hs >= bankStorage1d.size())
    {
        Account test;
        test.balance=-1;
        test.id="";
        for(int i=0;i<=99999;i++){
            bankStorage1d.push_back(test);
        }
    }
    if(count>=0){
        if(bankStorage1d[hs].balance<0){
            bankStorage1d[hs].balance=a.balance;
            bankStorage1d[hs].id=a.id;
            Insert(count);
            size++;
        }
        else if(bankStorage1d[hs].balance>=0){
            while(true){
                if(bankStorage1d[hs%100000].balance<0){
                    bankStorage1d[hs%100000]=a;
                    Insert(count);
                    size++;
                    break;
                }
                else{
                    hs++;
                }
            }
        }
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called getTopK"<<std::endl;
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

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called getBalance"<<std::endl;
    if(doesExist(id)){
        return bankStorage1d[position].balance;
    }
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called addTransaction"<<std::endl;
    if(doesExist(id)){
        int idx=BinarySearch(bankStorage1d[position].balance);
        bankStorage1d[position].balance += count;
        sorted.erase(sorted.begin() + idx);
        Insert(bankStorage1d[position].balance);
    }
    else if (!doesExist(id) && count >= 0)
    {
        createAccount(id, count);
    }
}

bool LinearProbing::doesExist(std::string id) {
    //std::cout<<"Called doesExist"<<std::endl;
    // IMPLEMENT YOUR CODE HERE
    int hs=hash(id);
    int cnt=0;
    if(size>0){
        while(cnt<=100000){
            if(bankStorage1d[hs%100000].id==id){
                position=hs%100000;
                return true;
            }
            else{
                hs++;
            }
            cnt++;
        }
    }
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called deleteAccount"<<std::endl;
    int hashed = hash(id);
    if (doesExist(id))
    {
        int idx = BinarySearch(bankStorage1d[position].balance);
        sorted.erase(sorted.begin() + idx);
        bankStorage1d[position].balance=-1;
        bankStorage1d[position].id="";
        size--;
        return true;
    }
    return false;// Placeholder return value
}
int LinearProbing::databaseSize() {
    //std::cout<<"Called databaseSize"<<std::endl;
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    //std::cout<<"Called hash"<<std::endl;
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
    return h % 100000;   // Placeholder return value
}

void LinearProbing::Insert(int n)
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

int LinearProbing::Binary(int n)
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

int LinearProbing::BinarySearch(int n)
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