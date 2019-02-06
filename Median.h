#include <queue>

using namespace std;

template <class T> class Median {

public:
    void push(const T &value);
    double getMedian() const;

private:
    priority_queue<T> pq1;
    priority_queue<T, vector<T>, greater<T> > pq2;
};

#include <limits>

template <class T> void Median<T>::push(const T &value) {
    if (pq1.empty()) {
        pq1.push(value);
    } else if (pq1.size() > pq2.size()) {
        if (value < pq1.top()) {
            pq2.push(pq1.top());
            pq1.pop();
            pq1.push(value);
        } else {
            pq2.push(value);
        }
    } else if (pq1.size() < pq2.size()) {
        if (value > pq2.top()) {
            pq1.push(pq2.top());
            pq2.pop();
            pq2.push(value);
        } else {
            pq1.push(value);
        }
    } else if (value < pq2.top()) {
        pq1.push(value);
    } else {
        pq2.push(value);
    }
}

template<class T> double Median<T>::getMedian() const {
    if (pq1.empty()) {
        return numeric_limits<T>::max();
    }

    if (pq1.size() > pq2.size()) {
       return pq1.top();
    } else if (pq1.size() < pq2.size()) {
        return pq2.top();
    } else {
        return (pq1.top() + pq2.top()) / 2.0;
    }
}
