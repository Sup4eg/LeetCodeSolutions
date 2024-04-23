#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <unordered_map>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution1
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<int, int> values;
        vector<int> ans;
        for (int i = 0; i < nums.size(); ++i)
        {
            int x = target - nums[i];
            if (values.count(x))
            {
                ans = {values[x], i};
                break;
            }
            else
            {
                values[nums[i]] = i;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* dummyHead = new ListNode(0);
        ListNode* tail = dummyHead;
        int carry = 0;
        while (l1 || l2 || carry != 0)
        {
            int digit1 = l1 ? l1->val : 0;
            int digit2 = l2 ? l2->val : 0;
            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            ListNode* newNode = new ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};

class Solution3
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> seen;

        int begin = 0, end = 0;
        int len = 0;

        string ans = "";

        while (end < s.length())
        {
            char current = s[end];

            if (seen.count(current) == 1 && seen[current] >= begin)
            {
                begin = seen[current] + 1;
            }
            else
            {
                seen[current] = end;
                end++;
            }

            if (end - begin > len)
            {
                len = end - begin;
                ans = s.substr(begin, end - begin);
            }
        }

        return len;
    }
};

class Solution20
{
public:
    bool isValid(string s)
    {
        vector<char> stack;
        for (char ch : s)
        {
            switch (ch)
            {
                case '(': stack.push_back(')'); break;
                case '[': stack.push_back(']'); break;
                case '{': stack.push_back('}'); break;
                case ')':
                case '}':
                case ']':
                    if (stack.empty() || stack.back() != ch) return false;
                    stack.pop_back();
                    break;
                default: break;
            }
        }
        return stack.empty();
    }
};

class Solution71
{
public:
    string simplifyPath(string path)
    {

        if (path.length() == 1) return "/";

        string formatPath;
        vector<string> words;
        string word = "";

        for (int i = 1; i <= path.length(); ++i)
        {
            char ch = path[i];
            if (ch == '/' || i == path.length())
            {
                if (word == ".." && !words.empty())
                {
                    words.pop_back();
                }
                else if (!word.empty() && word != "." && word != "..")
                {
                    words.push_back(word);
                }
                word.clear();
            }
            else
            {
                word += ch;
            }
        }

        if (words.empty())
            return "/";
        else
        {
            for (auto w : words)
                formatPath += ("/" + w);
        }
        return formatPath;
    }
};

class Solution76
{
public:
    string minWindow(string s, string t)
    {
        if (s.empty() || t.empty() || s.length() < t.length())
        {
            return "";
        }

        std::vector<int> map(128, 0);
        int count = t.length();
        int start = 0, end = 0, minLen = INT_MAX, startIndex = 0;
        for (char c : t)
        {
            map[c]++;
        }

        while (end < s.length())
        {
            if (map[s[end++]]-- > 0)
            {
                count--;
            }

            while (count == 0)
            {
                if (end - start < minLen)
                {
                    startIndex = start;
                    minLen = end - start;
                }

                if (map[s[start++]]++ == 0)
                {
                    count++;
                }
            }
        }

        return minLen == INT_MAX ? "" : s.substr(startIndex, minLen);
    }
};

class Solution159
{
public:
    int lengthOfLongestSubstringTwoDistinct(string s)
    {
        if (s.length() == 0) return 0;

        unordered_map<char, int> table;
        int begin = 0, end = 0, len = 0, counter = 0;

        while (end < s.length())
        {
            char current = s[end];

            table[current]++;
            if (table[current] == 1) counter++;

            end++;
            while (counter > 2)
            {
                char startchar = s[begin];

                if (table.count(startchar) == 1)
                {
                    table[startchar]--;
                    if (table[startchar] == 0) counter--;
                }

                begin++;
            }

            len = max(len, end - begin);
        }

        return len;
    }
};

class Solution136
{
public:
    int singleNumber(vector<int>& nums)
    {
        int sum_xor = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            sum_xor ^= nums[i];
        }
        return sum_xor;
    }
};

class Solution141
{

public:
    bool hasCycle(ListNode* head)
    {

        ListNode* ptr1 = head;
        ListNode* ptr2 = head;
        while (true)
        {
            if (head == nullptr || ptr1->next == nullptr || ptr2->next == nullptr || ptr2->next->next == nullptr)
            {
                return false;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            if (ptr1 == ptr2)
            {
                return true;
            }
        }
    }
};

class Solution203
{
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        ListNode* temp = head;
        while (temp)
        {
            if (temp->next && temp->next->val == val)
            {
                temp->next = temp->next->next;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (head && head->val == val)
        {
            return head->next;
        }
        return head;
    }
};

class Solution225
{
public:
    class MyStack
    {
    public:
        vector<int> stack;
        MyStack() {}

        void push(int x) { stack.push_back(x); }

        int pop()
        {
            int last = stack.back();
            stack.pop_back();
            return last;
        }

        int top() { return stack.back(); }

        bool empty() { return stack.empty(); }
    };
};

class Solution237
{
public:
    void deleteNode(ListNode* node)
    {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};

class Solution362
{
public:
    class HitCounter
    {
    public:
        queue<int> queue1;
        HitCounter() {}

        void hit(int timestamp) { queue1.push(timestamp); }

        int getHits(int timestamp)
        {
            int desregardTimestamp = timestamp > 300 ? timestamp - 300 : 0;
            int counter = 0;
            queue<int> temp = queue1;
            while (!queue1.empty() && queue1.front() <= timestamp)
            {
                if (desregardTimestamp == 0 || queue1.front() > desregardTimestamp)
                {
                    ++counter;
                }
                queue1.pop();
            }
            queue1 = move(temp);
            return counter;
        }
    };
};

class Solution438
{
public:
    vector<int> findAnagrams(string s, string p)
    {

        vector<int> ans;

        if (s.empty() || p.empty() || s.length() < p.length())
        {
            return ans;
        }

        std::vector<int> map(128, 0);
        int count = p.length();
        int wordSize = p.length();
        int start = 0, end = 0, startIndex = 0;
        for (char c : p)
        {
            map[c]++;
        }

        while (end < s.length())
        {
            if (map[s[end++]]-- > 0)
            {
                count--;
            }

            while (count == 0)
            {
                if (end - start == wordSize)
                {
                    startIndex = start;
                    ans.push_back(startIndex);
                }

                if (map[s[start++]]++ == 0)
                {
                    count++;
                }
            }
        }

        return ans;
    }
};

class Solution567
{
public:
    bool checkInclusion(string s1, string s2)
    {
        unordered_map<char, int> table;

        for (char c : s1)
        {
            table[c]++;
        }

        int begin = 0, end = 0, counter = table.size();

        while (end < s2.length())
        {
            char endchar = s2[end];

            if (table.count(endchar) == 1)
            {
                table[endchar]--;
                if (table[endchar] == 0) counter--;
            }

            end++;

            while (counter == 0)
            {
                if (end - begin == s1.length()) return true;

                char startchar = s2[begin];

                if (table.count(startchar) == 1)
                {
                    table[startchar]++;
                    if (table[startchar] > 0) counter++;
                }

                begin++;
            }
        }

        return false;
    }
};

class Solution1342
{
public:
    int numberOfSteps(int num)
    {
        int i = 0;
        while (num != 0)
        {
            if (num & 1)
            {
                num -= 1;
            }
            else
            {
                num /= 2;
            }
            ++i;
        }
        return i;
    }
};

class Solution1365
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums)
    {
        vector<int> count(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int k = 0; k < nums.size(); ++k)
            {
                if (nums[k] < nums[i])
                {
                    count[i]++;
                }
            }
        }
        return count;
    }
};

int main()
{
    Solution1 solution1;
    vector<int> nums{2, 7, 11, 15};
    vector<int> nums2{3, 2, 4};
    vector<int> nums3{3, 2, 3};

    auto res = solution1.twoSum(nums, 9);
    auto res2 = solution1.twoSum(nums2, 6);
    auto res3 = solution1.twoSum(nums3, 6);

    cout << res[0] << endl;
    cout << res[1] << endl;
    cout << "===============" << endl;

    cout << res2[0] << endl;
    cout << res2[1] << endl;

    cout << "============" << endl;
    cout << res3[0] << endl;
    cout << res3[1] << endl;
}