#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <numeric>

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
		ans = { values[x], i };
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

class Solution5
{
public:
  static string longestPalindrome(string s) {
	int n = s.length();
	int resLen = 0;
	string res = "";

	for (int i = 0; i < n; ++i) {
	  int l = i;
	  int r = i;

	  while (l >= 0 && r < n && s[l] == s[r]) {
		int newLen = r - l + 1;
		if (newLen > resLen) {
		  res = s.substr(l, newLen);
		  resLen = newLen;
		}
		l--;
		r++;
	  }

	  l = i;
	  r = i + 1;
	  while (l >= 0 && r < n && s[l] == s[r]) {
		int newLen = r - l + 1;
		if (newLen > resLen) {
		  res = s.substr(l, newLen);
		  resLen = newLen;
		}
		l--;
		r++;
	  }
	}
	return res;
  }
};

class Solution7
{
public:
  static int reverse(int x)
  {
	const int MAX_LIMIT = 2147483647;
	const int MIN_LIMIT = -2147483647 - 1;
	int ans = 0, pow = 1, k = x;

	while (k /= 10)
	{
	  pow *= 10;
	}

	while (pow)
	{
	  int lastN = x % 10;
	  if ((pow != 0 && lastN > MAX_LIMIT / pow) || (pow != 0 && lastN < MIN_LIMIT / pow)) return 0;
	  if ((ans > 0 && ans > MAX_LIMIT - pow * lastN) || (ans < 0 && ans < MIN_LIMIT - pow * lastN)) return 0;
	  ans += pow * lastN;
	  x /= 10;
	  pow /= 10;
	}

	return ans;
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

class Solution62 {
public:
  int uniquePaths(int m, int n) {
	vector<int> row(n, 1);

	for (int i = 0; i < m - 1; ++i) {
	  vector<int> newRow(n, 1);
	  for (int j = n - 2; j >= 0; --j) {
		newRow[j] = newRow[j + 1] + row[j];
	  }
	  row = newRow;
	}

	return row[0];
  }
};

class Solution70 {
public:
  static int climbStairs(int n) {
	int one = 1, two = 1;
	for (int i = 0; i < n - 1; ++i) {
	  int temp = one;
	  one = one + two;
	  two = temp;
	}
	return one;
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

class Solution91 {
public:
  int numDecodingsRecursion(string s) {
	unordered_map<int, int> dp;
	dp[s.length()] = 1;

	return dfs(0, s, dp);
  }

  int numDecodingsBottomUp(string s) {

	unordered_map<int, int> dp;
	dp[s.length()] = 1;

	for (int i = s.length() - 1; i >= 0; --i) {
	  if (s[i] == '0')
		dp[i] = 0;
	  else
		dp[i] = dp[i + 1];

	  if (i + 1 < s.length() && (s[i] == '1' || s[i] == '2' && s[i + 1] >= '0' && s[i + 1] < '7')) {
		dp[i] += dp[i + 2];
	  }
	}
	return dp[0];
  }

  int dfs(int i, string& s, unordered_map<int, int>& dp) {
	if (dp.count(i))
	  return dp[i];
	if (s[i] == '0')
	  return 0;

	int res = dfs(i + 1, s, dp);
	if (i + 1 < s.length() && (s[i] == '1' || s[i] == '2' && s[i + 1] >= 0 && s[i + 1] < 7)) {
	  res += dfs(i + 2, s, dp);
	}
	dp[i] = res;
	return res;
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

class Solution139 {
public:
  bool wordBreak(string s, vector<string>& wordDict) {
	vector<bool> dp(s.length() + 1, false);
	dp[s.length()] = true;
	for (int i = s.length() - 1; i >= 0; --i) {
	  for (string w : wordDict) {
		if ((i + w.length()) <= s.length() && s.substr(i, w.length()) == w) {
		  dp[i] = dp[i + w.length()];
		}
		if (dp[i]) break;
	  }
	}
	return dp[0];
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

class Solution152 {
public:
  int maxProduct(vector<int>& nums) {
	int res = *max_element(nums.begin(), nums.end());
	int curMin = 1, curMax = 1;

	for (int n : nums) {
	  if (n == 0) {
		curMin = 1;
		curMax = 1;
		continue;
	  }
	  int tmp = curMax * n;
	  curMax = max(n, max(n * curMax, n * curMin));
	  curMin = min(n, min(tmp, n * curMin));
	  res = max(res, curMax);
	}
	return res;
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

class Solution198 {
public:
  static int rob(vector<int>& nums) {
	int rob1 = 0, rob2 = 0;

	for (int n : nums) {
	  int temp = max(n + rob1, rob2);
	  rob1 = rob2;
	  rob2 = temp;
	}

	return rob2;
  }
};

class Solution213 {
public:
  int rob(vector<int>& nums) {
	vector<int> numsWithoutFirst{ nums.begin() + 1, nums.end() };
	vector<int> numsWithoutLast{ nums.begin(), nums.end() - 1 };
	return max(nums[0], max(helper(numsWithoutFirst), helper(numsWithoutLast)));
  }

  int helper(vector<int>& nums) {
	int rob1 = 0, rob2 = 0;

	for (int n : nums) {
	  int temp = max(n + rob1, rob2);
	  rob1 = rob2;
	  rob2 = temp;
	}

	return rob2;
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

class Solution300 {
public:
  int lengthOfLIS(vector<int>& nums) {
	vector<int> LIS(nums.size(), 1);

	for (int i = nums.size() - 1; i >= 0; --i) {
	  for (int j = i + 1; j < nums.size(); ++j) {
		if (nums[i] < nums[j]) {
		  LIS[i] = max(LIS[i], 1 + LIS[j]);
		}
	  }
	}
	return *max_element(LIS.begin(), LIS.end());
  }
};

class Solution322 {
public:
  int coinChange(vector<int>& coins, int amount) {
	vector<int> dp(amount + 1, amount + 1);
	dp[0] = 0;

	for (int a = 0; a < amount + 1; ++a) {
	  for (int c : coins) {
		if (a - c >= 0) {
		  dp[a] = min(dp[a], 1 + dp[a - c]);
		}
	  }
	}
	return dp[amount] != amount + 1 ? dp[amount] : -1;
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

class Solution416 {
public:
  bool canPartition(vector<int>& nums) {
	int sum = accumulate(nums.begin(), nums.end(), 0);
	if (sum & 1) return false;
	unordered_set<int> dp;
	dp.insert(0);
	int target = sum / 2;
	for (int i = nums.size() - 1; i >= 0; --i) {
	  unordered_set<int> nextDP;
	  for (int t : dp) {
		if (t + nums[i] == target) return true;
		nextDP.insert(t + nums[i]);
		nextDP.insert(t);
	  }
	  dp = nextDP;
	}
	return false;
  }
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

class Solution647 {
public:
  int countSubstrings(string s) {
	int res = 0;
	for (int i = 0; i < s.length(); ++i) {
	  res += countPolindroms(s, i, i);
	  res += countPolindroms(s, i, i + 1);
	}
	return res;
  }

  int countPolindroms(string& s, int l, int r) {
	int res = 0;
	while (l >= 0 && r < s.length() && s[l] == s[r]) {
	  ++res;
	  l--;
	  r++;
	}
	return res;
  }
};

class Solution746 {
public:
  static int minCostClimbingStairs(vector<int>& cost) {
	cost.push_back(0);
	for (int i = cost.size() - 3; i >= 0; --i) {
	  cost[i] += min(cost[i + 1], cost[i + 2]);
	}
	return min(cost[0], cost[1]);
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
  Solution62 solution62;
  cout << solution62.uniquePaths(3, 2) << endl;

}