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
