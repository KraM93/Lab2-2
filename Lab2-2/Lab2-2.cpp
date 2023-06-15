#include <iostream>

class Interval {
private:
    int start;
    int end;
    bool isStartClosed;
    bool isEndClosed;

public:
    Interval(int start, int end, bool isStartClosed, bool isEndClosed)
        : start(start), end(end), isStartClosed(isStartClosed), isEndClosed(isEndClosed) {}

    bool intersects(const Interval& other) const {
        if (end < other.start || other.end < start)
            return false;
        if (end == other.start && !(isEndClosed && other.isStartClosed))
            return false;
        if (start == other.end && !(isStartClosed && other.isEndClosed))
            return false;
        return true;
    }

    Interval intersection(const Interval& other) const {
        if (!intersects(other))
            return Interval(0, 0, false, false);
        int newStart = (start < other.start) ? other.start : start;
        int newEnd = (end < other.end) ? end : other.end;
        bool newIsStartClosed = (newStart == start) ? isStartClosed : other.isStartClosed;
        bool newIsEndClosed = (newEnd == end) ? isEndClosed : other.isEndClosed;
        return Interval(newStart, newEnd, newIsStartClosed, newIsEndClosed);
    }

    Interval sum(const Interval& other) const {
        int newStart = (start < other.start) ? start : other.start;
        int newEnd = (end > other.end) ? end : other.end;
        bool newIsStartClosed = (newStart == start) ? isStartClosed : other.isStartClosed;
        bool newIsEndClosed = (newEnd == end) ? isEndClosed : other.isEndClosed;
        return Interval(newStart, newEnd, newIsStartClosed, newIsEndClosed);
    }

    Interval difference(const Interval& other) const {
        if (!intersects(other))
            return *this;
        if (start >= other.start && end <= other.end)
            return Interval(0, 0, false, false);
        if (start >= other.start)
            return Interval(other.end, end, other.isEndClosed, isEndClosed);
        if (end <= other.end)
            return Interval(start, other.start, isStartClosed, other.isStartClosed);
        return Interval(start, other.start, isStartClosed, other.isStartClosed).sum(Interval(other.end, end, other.isEndClosed, isEndClosed));
    }

    void print() const {
        std::cout << (isStartClosed ? "[" : "(") << start << ", " << end << (isEndClosed ? "]" : ")") << std::endl;
    }
};

int main() {
    Interval interval1(1, 4, true, true);
    Interval interval2(1, 6, false, false);
    Interval interval3(1, 500, true, false);
    
    Interval intersection = interval1.intersection(interval2);
    intersection.print();

    Interval sum = interval1.sum(interval2);
    sum.print();

    Interval difference = interval1.difference(interval2);
    difference.print();

    return 0;
}
