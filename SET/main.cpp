#include <iostream>
#include <vector>
using namespace std;
class SET
{
public:
    vector<int> vect;
    SET()
    {
        vect = {};
    }
    void Insert(int n, int use = 0)
    {
        if (vect.size() == 0)
        {
            vect.push_back(n);
        }
        else if (Binary(n) != -1)
        {
            int index = Binary(n);
            vect.insert(vect.begin() + index, n);
        }
        if (use == 0)
        {
            cout << vect.size() << endl;
        }
    }
    void Delete(int n)
    {
        if (vect.size() == 0)
        {
            cout << 0 << endl;
        }
        else if (BinarySearch(n) == -1)
        {
            cout << vect.size() << endl;
        }
        else
        {
            int index = BinarySearch(n);
            vect.erase(vect.begin() + index);
            cout << vect.size() << endl;
        }
    }
    void Belongs_To(int n)
    {
        if (vect.size() == 0)
        {
            cout << 0 << endl;
        }
        else if (BinarySearch(n) == -1)
        {
            cout << 0 << endl;
        }
        else if (BinarySearch(n) != -1)
        {
            cout << 1 << endl;
        }
    }
    void Union(SET s, int n = 0)
    {
        if (vect.size() == 0)
        {
            vect = s.vect;
        }
        else if (s.vect.size() > 0)
        {
            for (int i = 0; i < s.vect.size(); i++)
            {
                this->Insert(s.vect[i], 1);
            }
        }
        if (n == 0)
        {
            cout << vect.size() << endl;
        }
    }
    void Intersection(SET s)
    {
        vector<int> result;
        int i = 0, j = 0;

        while (i < vect.size() && j < s.vect.size())
        {
            if (vect[i] < s.vect[j])
            {
                i++;
            }
            else if (vect[i] > s.vect[j])
            {
                j++;
            }
            else
            {
                result.push_back(vect[i]);
                i++;
                j++;
            }
        }

        vect = result;
        cout << vect.size() << endl;
    }
    void Size()
    {
        cout << vect.size() << endl;
    }
    void Difference(SET s, int use = 0)
    {
        if (s.vect.size() != 0 && vect.size() != 0)
        {
            vector<int> result;
            int i = 0, j = 0;

            while (i < vect.size() && j < s.vect.size())
            {
                if (vect[i] < s.vect[j])
                {
                    result.push_back(vect[i]);
                    i++;
                }
                else if (vect[i] > s.vect[j])
                {
                    j++;
                }
                else
                {
                    i++;
                    j++;
                }
            }

            while (i < vect.size())
            {
                result.push_back(vect[i]);
                i++;
            }

            vect = result;

            if (use == 0)
            {
                cout << vect.size() << endl;
            }
        }
        if (use == 0)
        {
            cout << vect.size() << endl;
        }
    }
    void Symmetric_Difference(SET s)
    {
        if (vect.size() == 0 && s.vect.size() != 0)
        {
            vect = s.vect;
        }
        else if (vect.size() > 0 && s.vect.size() > 0)
        {
            SET test_vect = s;
            SET copy = *this;
            Difference(s, 1);
            test_vect.Difference(copy, 1);
            Union(test_vect, 1);
        }
        cout << vect.size() << endl;
    }
    void Print()
    {
        if (vect.size() == 0)
        {
            cout << endl;
        }
        else
        {
            for (int i = 0; i < vect.size() - 1; i++)
            {
                cout << vect[i] << ",";
            }
            cout << vect[vect.size() - 1] << endl;
        }
    }
    int BinarySearch(int n)
    {
        int start = 0;
        int end = vect.size() - 1;
        while ((end - start) > 1)
        {
            int mid = (start + end) / 2;
            if (n >= vect[mid])
            {
                start = mid;
            }
            else
            {
                end = mid;
            }
        }
        if (vect[start] == n)
        {
            return start;
        }
        else if (vect[end] == n)
        {
            return end;
        }
        else
        {
            return -1;
        }
    }
    int Binary(int n)
    {
        int start = 0;
        int end = vect.size() - 1;
        while ((end - start) > 1)
        {
            int mid = (start + end) / 2;
            if (n >= vect[mid])
            {
                start = mid;
            }
            else
            {
                end = mid;
            }
        }
        if (vect[start] < n && vect[end] > n)
        {
            return start + 1;
        }
        else if (vect[end] < n)
        {
            return end + 1;
        }
        else if (vect[start] > n)
        {
            return start;
        }
        else
        {
            return -1;
        }
    }
};

int main()
{
    vector<SET *> sets;
    int a, b, c;
    while (cin >> a)
    {
        switch (a)
        {
        case (1):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            sets[b]->Insert(c);
            break;
        case (2):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                cout << -1 << endl;
            }
            else
            {
                sets[b]->Delete(c);
            }
            break;
        case (3):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                cout << -1 << endl;
            }
            else
            {
                sets[b]->Belongs_To(c);
            }
            break;
        case (4):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            if (sets.size() <= c)
            {
                sets.push_back(new SET());
            }
            sets[b]->Union(*sets[c]);
            break;
        case (5):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            if (sets.size() <= c)
            {
                sets.push_back(new SET());
            }
            sets[b]->Intersection(*sets[c]);
            break;
        case (6):
            cin >> b;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            sets[b]->Size();
            break;
        case (7):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            if (sets.size() <= c)
            {
                sets.push_back(new SET());
            }
            sets[b]->Difference(*sets[c]);
            break;
        case (8):
            cin >> b >> c;
            if (sets.size() <= b)
            {
                sets.push_back(new SET());
            }
            if (sets.size() <= c)
            {
                sets.push_back(new SET());
            }
            sets[b]->Symmetric_Difference(*sets[c]);
            break;
        case (9):
            cin >> b;
            if (sets.size() <= b)
            {
                cout << endl;
            }
            else
            {
                sets[b]->Print();
                break;
            }
        }
    }
}