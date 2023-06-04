

#include <c++/7/vector>
#include <iostream>

namespace bm17 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param nums int整型vector
     * @param target int整型
     * @return int整型
     */
    int search(std::vector<int> &nums, int target)
    {
        int low = 0, hi = nums.size();
        int mid;
        while (low <= hi)
        {
            mid = (low + hi) / 2;
            if (target < nums[mid])
                hi = mid - 1;
            else if (nums[mid] < target)
                low = mid + 1;
            else
                return mid;
        }
        return -1;
    }
};
}

namespace bm18 {
class Solution
{
public:
    bool Find(int target, std::vector<std::vector<int>> array)
    {
        int row = array.size();
        if (row == 0)
            return false;
        int col = array[0].size();
        int left = 0, down = row - 1;
        while (left < col && down >= 0)
        {
            int tmp = array[down][left];
            if (target < tmp)
                --down;
            else if (target > tmp)
                ++left;
            else
                return true;
        }
        return false;
    }
};
}

namespace bm19 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param nums int整型vector
     * @return int整型
     */
    int findPeakElement(std::vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        int mid;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (nums[mid] > nums[mid+1])
                right = mid;
            else
                left = mid + 1;
        }
        return right;
    }
};
}

namespace bm20 {
class Solution
{
public:
    constexpr static int MOD = 10'0000'0007;
    void merge(std::vector<int> &data, std::vector<int> &aux, int left, int mid, int right, int &ret)
    {
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right)
        {
            if (data[i] > data[j])
            {
                aux[k++] = data[j++];
                ret += (mid - i + 1);
                ret %= MOD;
            }
            else
            {
                aux[k++] = data[i++];
            }
        }
        while (i <= mid)
            aux[k++] = data[i++];
        while (j <= right)
            aux[k++] = data[j++];

        for (k = 0, i = left; i <= right; ++i, ++k)
            data[i] = aux[k];
    }




    void merge_sort(std::vector<int> &data, std::vector<int> &aux, int left, int right, int &ret)
    {
        if (left >= right)
            return ;
        int mid = left + (right - left) / 2;
        merge_sort(data, aux, left, mid, ret);
        merge_sort(data, aux, mid + 1, right, ret);
        merge(data, aux, left, mid, right, ret);
    }



    int InversePairs(std::vector<int> data)
    {
        std::vector<int> aux(data.size());
        int ret = 0;

        merge_sort(data, aux, 0, data.size() - 1, ret);

        return ret;
    }
};
}

namespace bm21 {
class Solution
{
public:
    int minNumberInRotateArray(std::vector<int> rotateArray)
    {
        if (rotateArray.size() == 0)
            return 0;
        int i = 0, j = rotateArray.size() - 1;
        int m;
        while (i < j)
        {
            m = (i + j) / 2;
            if (rotateArray[m] > rotateArray[j])
                i = m + 1;
            else if (rotateArray[m] < rotateArray[j])
                j = m;
            else
                --j;
        }
        return rotateArray[j];
    }
};
}

namespace bm22 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 比较版本号
     * @param version1 string字符串
     * @param version2 string字符串
     * @return int整型
     */
    int compare(std::string version1, std::string version2)
    {
        int n1 = version1.size();
        int n2 = version2.size();

        int i = 0, j = 0;
        while (i < n1 || j < n2)
        {
            long num1 = 0;
            while (i < n1 && version1[i] != '.')
            {
                num1 = num1 * 10 + (version1[i] - '0');
                ++i;
            }
            ++i;
            long num2 = 0;
            while (j < n2 && version2[j] != '.')
            {
                num2 = num2 * 10 + (version2[j] - '0');
                ++j;
            }
            ++j;
            if (num1 > num2)
                return 1;
            if (num1 < num2)
                return -1;
        }
        return 0;
    }
};

















}













int main()
{
    std::vector<int> vi;

    int x = vi.size() - 1;
    std::cout << "x = " << x << std::endl;

    return 0;
}




























