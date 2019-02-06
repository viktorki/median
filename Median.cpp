#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits>
#include "Median.h"

using namespace std;

const double EPS = 0.0000001;

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

void assertEquals(double expected, double actual) {
    if (abs(expected - actual) > EPS) {
        printf("ERROR: Expected %lf but got %lf\n", expected, actual);
    }
}

void testNoEntries() {
    printf("Test if the median of an empty list is undefined (+inf)\n");

    Median<double> median;

    assertEquals(numeric_limits<double>::max(), median.getMedian());
}

void test1Entry() {
    printf("Test if the median of a single number is the number itself\n");

    double a = rand() % 2000000 - 1000000;

    Median<double> median;
    median.push(a);

    assertEquals(a, median.getMedian());
}

void test2Entries() {
    printf("Test if the median of two numbers is the average of the numbers\n");

    double a = rand() % 2000000 - 1000000, b = rand() % 2000000 - 1000000;

    Median<double> median;
    median.push(a);
    median.push(b);

    assertEquals((a + b) / 2, median.getMedian());
}

void testMultipleEntries(int testCount, int listSize) {
    printf("Test %d time(s) the median of a list of %d numbers\n", testCount, listSize);

    int i, j;

    for (i = 0; i <testCount; i++) {
        Median<double> median;
        vector<double> testMedian;

        for (j = 1; j <= listSize; j++) {
            double a = rand() % 2000000 - 1000000;

            median.push(a);
            testMedian.push_back(a);
            sort(testMedian.begin(), testMedian.end());

            if (j % 2 == 0) {
                assertEquals((testMedian[j / 2 - 1] + testMedian[j / 2]) / 2, median.getMedian());
            } else {
                assertEquals(testMedian[j / 2], median.getMedian());
            }
        }
    }
}

int main() {
    testNoEntries();
    test1Entry();
    test2Entries();
    testMultipleEntries(1, 10000);
    testMultipleEntries(1000, 100);

    return 0;
}
