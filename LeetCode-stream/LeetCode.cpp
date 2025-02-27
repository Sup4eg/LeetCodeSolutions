#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

struct ListNode
{
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Contur {
public:
  static void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited) {
	auto m = grid.size();
	auto n = grid[0].size();

	if (r < 0 || r >= m || c < 0 || c >= n) return;

	if (visited[r][c]) return;
	visited[r][c] = true;

	cout << "Visiting (" << r << ", " << c << ") val=" << grid[r][c] << endl;

	dfs(grid, r - 1, c, visited); //up
	dfs(grid, r + 1, c, visited); //down
	dfs(grid, r, c - 1, visited); //left
	dfs(grid, r, c + 1, visited); //right
  }

  static void example() {
	vector<vector<int>> grid = {
	  {1, 2, 3},
	  {4, 5, 6},
	  {7, 8, 9}
	};

	auto m = grid.size();
	auto n = grid[0].size();
	vector<vector<bool>> visited(m, vector<bool>(n, false));


	dfs(grid, 1, 1, visited);
  }
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

class Solution3 {
public:
  int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> fm;
	int ans = 0;
	int left = 0;
	for (int right = 0; right < s.size(); ++right) {
	  ++fm[s[right]];
	  while (fm[s[right]] > 1) {
		--fm[s[left]];
		++left;
	  }
	  ans = max(ans, right - left + 1);
	}
	return ans;
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

class Solution10 {
public:
  bool isMatch(string s, string p) {
	return dfs(0, 0, s, p);
  }
private:

  map<pair<int, int>, bool> cache;

  bool dfs(int i, int j, string& s, string& p) {
	if (cache.count({ i, j })) return cache[{i, j}];
	if (i >= s.length() && j >= p.length()) return true;
	if (j >= p.length()) return false;

	bool match = (i < s.length()) && (s[i] == p[j] || p[j] == '.');
	if ((j + 1 < p.length()) && p[j + 1] == '*') {
	  cache[{i, j}] = (dfs(i, j + 2, s, p) ||      //don't use *
		(match && dfs(i + 1, j, s, p)));      //use *
	  return cache[{i, j}];
	}
	if (match) {
	  cache[{i, j}] = dfs(i + 1, j + 1, s, p);
	  return cache[{i, j}];
	}
	cache[{i, j}] = false;
	return false;
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

class Solution72 {
public:
  int minDistance(string word1, string word2) {
	vector<vector<int>> cache(word1.length() + 1, vector<int>(word2.length() + 1, INT_MAX));
	for (int j = 0; j < word2.length() + 1; ++j) {
	  cache[word1.length()][j] = word2.length() - j;
	}
	for (int i = 0; i < word1.length() + 1; ++i) {
	  cache[i][word2.length()] = word1.length() - i;
	}
	for (int i = word1.length() - 1; i >= 0; --i) {
	  for (int j = word2.length() - 1; j >= 0; --j) {
		if (word1[i] == word2[j]) {
		  cache[i][j] = cache[i + 1][j + 1];
		}
		else {
		  cache[i][j] = 1 + min(cache[i + 1][j + 1], min(cache[i + 1][j], cache[i][j + 1]));
		}
	  }
	}
	return cache[0][0];
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

class Solution97 {
public:
  bool isInterleave(string s1, string s2, string s3) {
	if (s3.length() != s1.length() + s2.length()) return false;

	vector<vector<bool>> dp(s1.length() + 1, vector<bool>(s2.length() + 1, false));
	dp[s1.length()][s2.length()] = true;
	for (int i = s1.length(); i >= 0; --i) {
	  for (int j = s2.length(); j >= 0; --j) {
		if (i < s1.length() && s1[i] == s3[i + j] && dp[i + 1][j]) dp[i][j] = true;
		if (j < s2.length() && s2[j] == s3[i + j] && dp[i][j + 1]) dp[i][j] = true;
	  }
	}
	return dp[0][0];

	//dfs solution
	//return dfs(s1, s2, s3, 0, 0);
  }

private:
  map<pair<int, int>, bool> dp;

  //k = i + j
  bool dfs(string& s1, string& s2, string& s3, int i, int j) {
	if (i == s1.length() && j == s2.length()) return true;
	if (dp.find({ i, j }) != dp.end()) return dp[{i, j}];

	if (i < s1.length() && s1[i] == s3[i + j] && dfs(s1, s2, s3, i + 1, j)) return true;
	if (j < s2.length() && s2[j] == s3[i + j] && dfs(s1, s2, s3, i, j + 1)) return true;
	dp[{i, j}] = false;
	return false;
  }

};

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution103 {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> ans;
	if (root == nullptr) return ans;
	bool lvlFlag = true;

	queue<TreeNode*> queue;
	queue.push(root);

	while (!queue.empty()) {
	  int nodesInCurrentLevel = queue.size();
	  vector<int> lvlValues;
	  lvlValues.reserve(nodesInCurrentLevel);

	  for (int i = 0; i < nodesInCurrentLevel; ++i) {
		TreeNode* node = queue.front();
		queue.pop();
		lvlValues.push_back(node->val);

		if (node->left) {
		  queue.push(node->left);
		}

		if (node->right) {
		  queue.push(node->right);
		}
	  }
	  if (!lvlFlag) {
		reverse(lvlValues.begin(), lvlValues.end());
	  }
	  lvlFlag = !lvlFlag;
	  ans.push_back(lvlValues);
	}
	return ans;
  }
};

class Solution111 {
public:
  int minDepth(TreeNode* root) {
	if (root == nullptr) return 0;

	if (!root->left) {
	  return 1 + minDepth(root->right);
	}
	else if (!root->right) {
	  return 1 + minDepth(root->left);
	}

	int left = minDepth(root->left);
	int right = minDepth(root->right);
	return min(left, right) + 1;
  }
};

class Solution543 {
public:
  int diameterOfBinaryTree(TreeNode* root) {
	int diameter = 0;
	dfs(root, diameter);
	return diameter;
  }

private:
  int dfs(TreeNode* root, int& diameter) {
	if (!root) return 0;
	int leftHeight = dfs(root->left, diameter);
	int rightHeight = dfs(root->right, diameter);
	diameter = max(diameter, leftHeight + rightHeight);
	return max(leftHeight, rightHeight) + 1;
  }
};

class Solution115 {
public:
  int numDistinct(string s, string t) {
	return dfs(0, 0, s, t);
  }

private:
  map<pair<int, int>, int> dp;

  int dfs(int i, int j, string& s, string& t) {
	if (j == t.length()) return 1;
	if (i == s.length()) return 0;
	if (dp.count({ i, j })) return dp[{i, j}];
	if (s[i] == t[j]) {
	  dp[{i, j}] = dfs(i + 1, j + 1, s, t) + dfs(i + 1, j, s, t);
	}
	else {
	  dp[{i, j}] = dfs(i + 1, j, s, t);
	}
	return dp[{i, j}];
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

class Solution206 {
public:
  struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
  };
  ListNode* reverseList(ListNode* head) {
	ListNode* curr = head;
	ListNode* prev = nullptr;
	while (curr != nullptr) {
	  ListNode* nextNode = curr->next;
	  curr->next = prev;
	  prev = curr;
	  curr = nextNode;
	}
	return prev;
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

class Solution268 {
public:
  int missingNumber(vector<int>& nums) {
	int target = nums.size() * (nums.size() + 1) / 2;
	int total = 0;
	for (auto& n : nums) {
	  total += n;
	}
	return target - total;
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

class Solution309 {
public:

  // int maxProfit(vector<int>& prices) {
	 //int sold = 0;
	 //int hold = INT_MIN;
	 //int rest = 0;

	 //for (int i = 0; i < prices.size(); i++) {
	 //  int prevSold = sold;
	 //  sold = hold + prices[i];
	 //  hold = max(hold, rest - prices[i]);
	 //  rest = max(rest, prevSold);
	 //}

	 //return max(sold, rest);
  // }


  int maxProfit(vector<int>& prices) {

	vector<vector<int>> dp(100005, vector<int>(2, -1));

	//State: buying of selling
	//if buy --> i + 1;
	// if sell --> i + 2
	int n = prices.size();

	return dfs(0, 1, prices, dp);

  }

  int dfs(int i, int buying, vector<int>& prices, vector<vector<int>>& dp) {
	if (i >= prices.size()) return 0;
	if (dp[i][buying] != -1) {
	  return dp[i][buying];
	};

	if (buying) {
	  int buy = dfs(i + 1, buying - 1, prices, dp) - prices[i];
	  int cooldown = dfs(i + 1, buying, prices, dp);
	  dp[i][buying] = max(buy, cooldown);
	}
	else {
	  int sell = dfs(i + 2, buying + 1, prices, dp) + prices[i];
	  int cooldown = dfs(i + 1, buying, prices, dp);
	  dp[i][buying] = max(sell, cooldown);
	}
	return dp[i][buying];
  }
};

class Solution312 {
public:
  int maxCoins(vector<int>& nums) {
	nums.insert(nums.begin(), 1);
	nums.insert(nums.end(), 1);
	int n = nums.size();

	vector<vector<int>> dp(n, vector<int>(n, 0));
	return dfs(1, nums.size() - 2, nums, dp);
  }


private:
  int dfs(int l, int r, vector<int>& nums, vector<vector<int>>& dp) {
	if (l > r) {
	  return 0;
	}
	if (dp[l][r] > 0) {
	  return dp[l][r];
	}
	dp[l][r] = 0;
	for (int i = l; i < r + 1; ++i) {
	  int coins = nums[l - 1] * nums[i] * nums[r + 1];
	  coins += dfs(l, i - 1, nums, dp) + dfs(i + 1, r, nums, dp);
	  dp[l][r] = max(dp[l][r], coins);
	}
	return dp[l][r];
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

class Solution329 {
private:
  int ROWS = 0;
  int COLS = 0;
  map<pair<int, int>, int> dp;

public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
	ROWS = matrix.size();
	COLS = matrix[0].size();
	int LIP = -1;
	for (int r = 0; r < ROWS; ++r) {
	  for (int c = 0; c < COLS; ++c) {
		LIP = max(LIP, dfs(r, c, -1, matrix));
	  }
	}
	return LIP;
  }

  int dfs(int r, int c, int prevVal, vector<vector<int>>& matrix) {
	if (r < 0 || r == ROWS || c < 0 || c == COLS || matrix[r][c] <= prevVal) return 0;
	if (dp.find({ r, c }) != dp.end()) return dp[{r, c}];
	int res = 1;
	res = max(res, 1 + dfs(r + 1, c, matrix[r][c], matrix));
	res = max(res, 1 + dfs(r - 1, c, matrix[r][c], matrix));
	res = max(res, 1 + dfs(r, c + 1, matrix[r][c], matrix));
	res = max(res, 1 + dfs(r, c - 1, matrix[r][c], matrix));
	dp[{r, c}] = res;
	return res;
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

class Solution383 {
public:
  bool canConstruct(string ransomNote, string magazine) {
	map<char, int> fm;
	for (char& s : magazine) {
	  ++fm[s];
	}
	for (char& s : ransomNote) {
	  if (--fm[s] < 0) return false;
	}
	return true;
  }
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

class Solution494 {

private:
  // {(index, total) -> # of ways}
  map<pair<int, int>, int> dp;

  int backtrack(vector<int>& nums, int target, int i, int total) {
	if (i == nums.size()) return total == target ? 1 : 0;
	if (dp.find({ i, total }) != dp.end()) return dp[{i, total}];
	dp[{i, total}] = backtrack(nums, target, i + 1, total + nums[i]) + backtrack(nums, target, i + 1, total - nums[i]);
	return dp[{i, total}];
  }

public:
  int findTargetSumWays(vector<int>& nums, int target) {
	int res = backtrack(nums, target, 0, 0);

	return res;
  }
};

class Solution518 {
public:

  //O(n*m)

  int change(int amount, vector<int>& coins) {
	//2d solution with O(n * m), memory O(n * m)
	//vector<vector<int>> dp(amount + 1, vector<int>(coins.size() + 1, 0));
	//dp[0] = vector<int>(coins.size() + 1, 1);

	//
	//for (int a = 1; a < amount + 1; ++a) {
	//  for (int i = coins.size() - 1; i >= 0; --i) {
	//	dp[a][i] = dp[a][i + 1];
	//	if (a - coins[i] >= 0) {
	//	  dp[a][i] += dp[a - coins[i]][i];
	//	}
	//  }
	//}
	//return dp[amount][0];


	//2d solution with O(n * m), memory O (n)
	vector<int> dp(amount + 1, 0);
	dp[0] = 1;

	for (int i = coins.size() - 1; i >= 0; --i) {
	  vector<int> nextDP(amount + 1, 0);
	  nextDP[0] = 1;
	  for (int a = 1; a < amount + 1; ++a) {
		nextDP[a] = dp[a];
		if (a - coins[i] >= 0) {
		  nextDP[a] += nextDP[a - coins[i]];
		}
	  }
	  dp = nextDP;
	}
	return dp[amount];

	//recursion solution
	//return dfs(amount, coins, 0, 0);
  }

private:
  map<pair<int, int>, int> dp;
  //O(n * m), memory O(n * m)
  int dfs(int amount, vector<int>& coins, int i, int sum) {
	if (sum == amount) {
	  return 1;
	}
	if (sum > amount) {
	  return 0;
	}
	if (i == coins.size()) {
	  return 0;
	}
	if (dp.find({ i, sum }) != dp.end()) {
	  return dp[{i, sum}];
	}

	dp[{i, sum}] = dfs(amount, coins, i, sum + coins[i])
	  + dfs(amount, coins, i + 1, sum);

	return dp[{i, sum}];
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

class Solution643 {
public:
  double findMaxAverage(vector<int>& nums, int k) {
	int cur = 0.f;
	for (int i = 0; i < k; ++i) {
	  cur += nums[i];
	}
	int ans = cur;
	for (int i = k; i < nums.size(); ++i) {
	  cur += nums[i] - nums[i - k];
	  ans = max(ans, cur);
	}
	return (double)ans / k;
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

class Solution771 {
public:
  int numJewelsInStones(string jewels, string stones) {
	unordered_map<char, int> fm;
	int ans = 0;
	for (char& s : stones) {
	  ++fm[s];
	}
	for (char& j : jewels) {
	  ans += fm[j];
	}
	return ans;
  }
};

class Solution1143 {
public:
  int longestCommonSubsequence(string text1, string text2) {
	vector<vector<int>>dp(text1.length() + 1, vector<int>(text2.length() + 1));
	for (int i = text1.length() - 1; i >= 0; --i) {
	  for (int j = text2.length() - 1; j >= 0; --j) {
		if (text1[i] == text2[j]) {
		  dp[i][j] = 1 + dp[i + 1][j + 1];
		}
		else {
		  dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	  }
	}
	return dp[0][0];
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

class Solution1004 {
public:
  int longestOnes(vector<int>& nums, int k) {
	int left = 0, curr = 0, ans = 0;
	for (int right = 0; right < nums.size(); ++right) {
	  if (nums[right] == 0) {
		++curr;
	  }
	  while (curr > k) {
		if (nums[left] == 0) {
		  --curr;
		}
		++left;
	  }
	  ans = max(ans, right - left + 1);
	}
	return ans;
  }
};

class Solution1133 {
public:
  int largestUniqueNumber(vector<int>& nums) {
	unordered_map<int, int> fm;
	for (auto& n : nums) {
	  ++fm[n];
	}
	int largestUnique = -1;
	for (auto& pair : fm) {
	  if (pair.second == 1 && pair.first > largestUnique) {
		largestUnique = pair.first;
	  }
	}
	return largestUnique;
  }
};

class Solution1189 {
public:
  int maxNumberOfBalloons(string text) {
	int ans = text.size();
	unordered_map<char, int> fm{
	  {'b', 0}, //1 2 3
	  {'a', 0}, //1 2 3
	  {'l', 0}, //2 4 6
	  {'o', 0}, //2 4 6
	  {'n', 0}  //1 2 3
	};
	for (auto& s : text) {
	  if (fm.find(s) != fm.end()) {
		++fm[s];
	  }
	}
	fm['l'] /= 2;
	fm['o'] /= 2;
	for (auto& n : fm) {
	  if (n.second < ans) ans = n.second;
	}
	return ans;
  }
};

class Solution1302 {
public:
  int deepestLeavesSum(TreeNode* root) {
	queue<TreeNode*> queue;
	queue.push(root);
	int sum = 0;

	while (!queue.empty()) {
	  int nodesInCurrentLevel = queue.size();

	  for (int i = 0; i < nodesInCurrentLevel; ++i) {
		TreeNode* node = queue.front();
		sum += node->val;
		queue.pop();


		if (node->left) {
		  queue.push(node->left);
		}

		if (node->right) {
		  queue.push(node->right);
		}
	  }
	  if (!queue.empty()) {
		sum = 0;
	  }
	}
	return sum;
  }
};

class Solution1426 {
public:
  int countElements(vector<int>& arr) {
	unordered_set<int> nums(arr.begin(), arr.end());
	int count = 0;
	for (auto& n : arr) {
	  if (nums.find(n + 1) != nums.end()) {
		++count;
	  }
	}
	return count;
  }
};

class Solution1480 {
public:
  vector<int> runningSum(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans(n);
	ans[0] = nums[0];
	for (int i = 1; i < n; ++i) {
	  ans[i] = nums[i] + ans[i - 1];
	}
	return ans;
  }
};

class Solution1413 {
public:
  int minStartValue(vector<int>& nums) {
	int total = nums[0];
	int minn = nums[0];
	for (int i = 1; i < nums.size(); ++i) {
	  total += nums[i];
	  minn = min(minn, total);
	}
	return minn < 0 ? abs(minn) + 1 : minn;
  }
};

class Solution1832 {
public:
  bool checkIfPangram(string sentence) {
	unordered_set<char> alpha(sentence.begin(), sentence.end());
	return alpha.size() == 26;
  }
};

class Solution2090 {
public:
  vector<long> runningSum(vector<int>& nums) {
	int n = nums.size();
	vector<long> ans(n);
	ans[0] = nums[0];
	for (int i = 1; i < n; ++i) {
	  ans[i] = nums[i] + ans[i - 1];
	}
	return ans;
  }

  vector<int> getAverages(vector<int>& nums, int k) {
	vector<long> sums = runningSum(nums);
	vector<int> ans(nums.size());
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
	  if (i - k < 0 || i + k > n - 1) {
		ans[i] = -1;
	  }
	  else {
		long left = sums[i] - sums[i - k] + nums[i - k];
		long right = sums[k + i] - sums[i];
		ans[i] = (left + right) / (k * 2 + 1);
	  }
	}
	return ans;
  }
};

class Solution2225 {
public:
  vector<vector<int>> findWinners(vector<vector<int>>& matches) {
	unordered_map<int, int> m;
	vector<vector<int>> ans;
	ans.reserve(2);
	vector<int> no_lose;
	vector<int> lose1;
	for (auto& stat : matches) {
	  if (m.find(stat[0]) == m.end()) {
		m[stat[0]] = 0;
	  }
	  ++m[stat[1]];
	}
	for (auto& n : m) {
	  if (n.second == 0) {
		no_lose.push_back(n.first);
	  }
	  else if (n.second == 1) {
		lose1.push_back(n.first);
	  }
	}
	sort(no_lose.begin(), no_lose.end());
	sort(lose1.begin(), lose1.end());
	ans.push_back(no_lose);
	ans.push_back(lose1);
	return ans;
  }
};


int main()
{
  Solution103 solution;
  solution.zigzagLevelOrder(nullptr);
}