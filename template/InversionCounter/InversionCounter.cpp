// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/InversionCounter/InversionCounter.cpp
template <typename T>
struct InversionCounter {

    static long long count(std::vector<T> arr) {
        std::vector<T> temp(arr.size());
        return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
    }

    static long long countAndSort(std::vector<T>& arr) {
        std::vector<T> temp(arr.size());
        return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
    }

private:
    static long long mergeSortAndCount(std::vector<T>& arr, std::vector<T>& temp, int left, int right) {
        if (left >= right) return 0;

        int mid = (left + right) / 2;
        long long count = 0;

        count += mergeSortAndCount(arr, temp, left, mid);
        count += mergeSortAndCount(arr, temp, mid + 1, right);
        count += mergeAndCount(arr, temp, left, mid, right);

        return count;
    }

    static long long mergeAndCount(std::vector<T>& arr, std::vector<T>& temp, int left, int mid, int right) {
        int i = left, j = mid + 1, k = left;
        long long inv_count = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
                inv_count += (mid - i + 1);
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (int p = left; p <= right; ++p) {
            arr[p] = temp[p];
        }

        return inv_count;
    }
};
