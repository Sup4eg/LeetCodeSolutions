#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};


class Solution1 {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> ans(2);
	if (nums.size() > 1) {
	  for (int i = 0; i < nums.size(); ++i) {
		for (int k = 0; k < nums.size(); ++k) {
		  if (i != k) {
			int num1 = nums[i];
			int num2 = nums[k];
			if (num1 + num2 == target) {
			  ans = { i, k };
			  return ans;
			}
		  }
		}
	  }
	}
	return ans;
  }
};

class Solution20 {
public:
  bool isValid(string s) {
	vector<char> stack;
	for (char ch : s)
	{
	  switch (ch)
	  {
	  case '(':
		stack.push_back(')');
		break;
	  case '[':
		stack.push_back(']');
		break;
	  case '{':
		stack.push_back('}');
		break;
	  case ')':
	  case '}':
	  case ']':
		if (stack.empty() || stack.back() != ch) return false;
		stack.pop_back();
		break;
	  default:
		break;
	  }
	}
	return stack.empty();
  }
};

class Solution71 {
public:
  string simplifyPath(string path) {

	if (path.length() == 1) return "/";

	string formatPath;
	vector<string> words;
	string word = "";

	for (int i = 1; i <= path.length(); ++i) {
	  char ch = path[i];
	  if (ch == '/' || i == path.length()) {
		if (word == ".." && !words.empty()) {
		  words.pop_back();
		}
		else if (!word.empty() && word != "." && word != "..") {
		  words.push_back(word);
		}
		word.clear();
	  }
	  else {
		word += ch;
	  }
	}

	if (words.empty()) return "/";
	else {
	  for (auto w : words) formatPath += ("/" + w);
	}
	return formatPath;
  }
};


class Solution136 {
public:
  int singleNumber(vector<int>& nums) {
	int sum_xor = 0;
	for (int i = 0; i < nums.size(); ++i)
	{
	  sum_xor ^= nums[i];
	}
	return sum_xor;
  }
};


class Solution141 {

public:
  bool hasCycle(ListNode* head) {

	ListNode* ptr1 = head;
	ListNode* ptr2 = head;
	while (true) {
	  if (head == nullptr
		|| ptr1->next == nullptr
		|| ptr2->next == nullptr
		|| ptr2->next->next == nullptr) {
		return false;
	  }
	  ptr1 = ptr1->next;
	  ptr2 = ptr2->next->next;
	  if (ptr1 == ptr2) {
		return true;
	  }
	}
  }
};


class Solution203 {
public:
  ListNode* removeElements(ListNode* head, int val)
  {
	ListNode* temp = head;
	while (temp) {
	  if (temp->next && temp->next->val == val) {
		temp->next = temp->next->next;
	  }
	  else {
		temp = temp->next;
	  }
	}
	if (head && head->val == val) {
	  return head->next;
	}
	return head;
  }
};


class Solution237 {
public:
  void deleteNode(ListNode* node) {
	node->val = node->next->val;
	node->next = node->next->next;
  }
};



class Solution1342 {
public:
  int numberOfSteps(int num) {
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


class Solution1365 {
public:
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
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



int main() {
  Solution71 solution71;
  //cout << solution71.simplifyPath("/home/") << endl;
  //cout << solution71.simplifyPath("/../") << endl;
  //cout << solution71.simplifyPath("/home//foo/") << endl;
  //cout << solution71.simplifyPath("/a/./b/../../c/") << endl;
  cout << solution71.simplifyPath("/a//b////c/d//././/..") << endl;


}