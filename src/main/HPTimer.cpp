#include <chrono>
using namespace std;
using namespace chrono;
class HPTimer {
private:
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
public:
    void start() {
        startTime = high_resolution_clock::now();
    }

    unsigned long long end() {
        auto endTime = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(endTime - startTime);
        return duration.count();
    }
};