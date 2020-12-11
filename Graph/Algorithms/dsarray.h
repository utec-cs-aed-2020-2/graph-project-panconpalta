#ifndef DSARRAY_H
#define DSARRAY_H

#include "ds.h"

template<typename T>
struct val_set {
    T data;
    int setRank;
    int set;

    val_set(T d, int s) : data(d), set(s), setRank(0) {}

    val_set() {}
};

//the sets are named by the index they start
template<typename T>
class DisjoinSetArray : public DisjoinSet<T> {
    //vector with the values and sets_
    vector<val_set<T>> sets_;
public:
    DisjoinSetArray(vector<T> data) : DisjoinSet<T>() {
        sets_.resize(data.size());
        for (int i = 0; i < data.size(); i++)
            sets_[i] = val_set<T>(data[i], i);
    }

    // implement all functions
    ~DisjoinSetArray() override {}

    //MakseSet the element with index x
    void MakeSet(int x) {
        sets_[x].set = x;
        sets_[x].setRank = 0;
    }

    //MakseSet all elements, reset all sets
    void MakeSet() {
        for (int i = 0; i < sets_.size(); i++) {
            sets_[i].set = i;
            sets_[i].setRank = 0;
        }
    }

    //Find the root of x
    int Find(int x) {
        if (x == sets_[x].set)
            return x;
        return Find(sets_[x].set);
    }

    int Find(T x) {
        for (int i = 0; i < sets_.size(); i++) {
            if (sets_[i].data == x)
                return Find(i);
        }
        return -1;
    }

    //Union two sets_ represented by x and y (apply setRank)
    void Union(int x, int y) {
        int xr = Find(x);
        int yr = Find(y);
        if (xr == yr)return;
        if (sets_[xr].setRank < sets_[yr].setRank)
            sets_[xr].set = yr;
        else if (sets_[xr].setRank > sets_[yr].setRank)
            sets_[yr].set = xr;
        else {
            sets_[yr].set = xr;
            sets_[xr].setRank++;
        }

    }

    //check whether there is a path between x and y
    bool isConnected(int x, int y) {
        return Find(x) == Find(y);
    }

    //total number of elements
    int size() { return sets_.size(); }

    //number of sets_
    int sets() {
        int count = 0;
        //counts the number of roots in te vector
        for (int i = 0; i < sets_.size(); i++)
            if (i == sets_[i].set) count++;

        return count;
    }

    //total number of elements that belong to the set of x
    int size(int x) {
        int count = 0;
        for (int i = 0; i < sets_.size(); i++)
            if (Find(i) == Find(x)) count++;

        return count;
    }

    //add the element to the set of x
    void Add(T element, int x) {
        sets_.push_back(val_set<T>(element, x));
    }

    void Add(T element) {
        sets_.push_back(val_set<T>(element, sets_.size()));
    }

    //return all elements that belong to the set of x
    vector<T> getElementsSet(int x) {
        vector<T> vec;
        for (int i = 0; i < sets_.size(); i++)
            if (Find(i) == Find(x))
                vec.push_back(sets_[i].data);

        return vec;
    }
};

#endif
