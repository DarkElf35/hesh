#include <iostream>
#include <vector> 
#include <deque> 
#include <algorithm> 
#include <iterator> 

using namespace std;

template <class T>
class Set {

private:

    vector<deque<T> > TableHash;
    static const int HSize = 256;
    int Size;

    
    int hashFun(const T& t) const
    {
        unsigned char* value = (unsigned char*)&t;
        return (int)*value % HSize;
    }


public:

   
    Set(void) : Size(0)
    {
        TableHash.resize(HSize);
    }

    Set(const Set& s) {
        TableHash = s.TableHash;
        Size = s.Size;
    }

    
    Set operator + (const T& t) const
    {
        Set elem(*this);
        elem += t;
        return elem;
    }

    friend Set operator + (const T& t, const Set& s)
    {
        Set elem(s);
        elem += t;
        return elem;
    }

    Set& operator += (const T& t)
    {
        int post = hashFun(t);
        typename deque<T>::iterator iter = find(TableHash[post].begin(), TableHash[post].end(), t);
        if (iter == TableHash[post].end())
        {
            TableHash[post].push_back(t);
            Size++;
        }
        return *this;
    }

    
    Set operator - (const T& t) const
    {
        Set elem(*this);
        elem -= t;
        return elem;
    }

    Set& operator -= (const T& t)
    {
        int post = hashFun(t);
        typename deque<T>::iterator iter = find(TableHash[post].begin(), TableHash[post].end(), t);
        if (iter != TableHash[post].end())
        {
            TableHash[post].erase(iter);
            Size--;
        }
        return *this;
    }

    
    bool exists(const T& t) const
    {
        int post = hashFun(t);
        typename deque<T>::const_iterator iter = find(TableHash[post].begin(), TableHash[post].end(), t);
        if (iter == TableHash[post].end())
            return false;

        return true;
    }

    
    Set operator + (const Set& s) const
    {
        Set elem(*this);
        elem += s;
        return elem;
    }

    Set& operator += (const Set& s)
    {
        for (unsigned int i = 0; i < HSize; i++)
        {
            typename deque<T>::const_iterator iter = s.TableHash[i].begin();
            while (iter != s.TableHash[i].end())
            {
                *this += *iter;
                ++iter;
            }
        }
        return *this;
    }

    
    Set operator - (const Set& s) const
    {
        Set elem(*this);
        elem -= s;
        return elem;
    }

    Set& operator -= (const Set& s)
    {
        for (int i = 0; i < HSize; ++i)
        {
            typename deque<T>::const_iterator iter = s.TableHash[i].begin();
            while (iter != s.TableHash[i].end())
            {
                *this -= *iter;
                ++iter;
            }
        }
        return *this;
    }

    
    bool operator == (const Set& s) const
    {
        return TableHash == s.TableHash;

    }

    bool operator != (const Set& s) const
    {
        return TableHash != s.TableHash;
    }

    
    int size(void) const
    {
        return Size;
    }

    
    friend ostream& operator << (ostream& os, const Set& s)
    {
        vector <T> elem;
        for (unsigned int i = 0; i < HSize; i++) {
            for (typename deque<T>::const_iterator iter = s.TableHash[i].begin(); iter != s.TableHash[i].end(); iter++)
            {
                elem.push_back(*iter);
            }
        }
        sort(elem.begin(), elem.end());
        for (typename vector <T>::iterator iter = elem.begin(); iter != elem.end(); iter++)
        {
            os << *iter << " ";
        }
        return os;
    }

    
};
