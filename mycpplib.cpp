
#include <cmath>
extern "C" {
    long long count3d(int n) {
        long long count = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                    count++;
        return count;
    }
}
