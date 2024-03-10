#include <iostream>
#include <vector>
#include <queue>

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

class Solution225 {
  public:
  class MyStack {
  public:
	vector<int> stack;
	MyStack() {
	}

	void push(int x) {
	  stack.push_back(x);
	}

	int pop() {
	  int last = stack.back();
	  stack.pop_back();
	  return last;
	}

	int top() {
	  return stack.back();
	}

	bool empty() {
	  return stack.empty();
	}
  };

};

class Solution237 {
public:
  void deleteNode(ListNode* node) {
	node->val = node->next->val;
	node->next = node->next->next;
  }
};

class Solution362 {
public:
  class HitCounter {
  public:
	queue<int> queue1;
	HitCounter() {
	}

	void hit(int timestamp) {
	  queue1.push(timestamp);
	}

	int getHits(int timestamp) {
	  int desregardTimestamp = timestamp > 300 ? timestamp - 300 : 0;
	  int counter = 0;
	  queue<int> temp = queue1;
	  while (!queue1.empty() && queue1.front() <= timestamp) {
		if (desregardTimestamp == 0 || queue1.front() > desregardTimestamp) {
		  ++counter;
		}
		queue1.pop();
	  }
	  queue1 = temp;
	  return counter;
	}
  };
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
  Solution362::HitCounter* hitCounter = new Solution362::HitCounter();
  hitCounter->hit(1);       // hit at timestamp 1.
  hitCounter->hit(2);       // hit at timestamp 2.
  hitCounter->hit(3);       // hit at timestamp 3.
  cout << hitCounter->getHits(4) << endl;   // get hits at timestamp 4, return 3.
  hitCounter->hit(300);     // hit at timestamp 300.
  cout << hitCounter->getHits(300) << endl; // get hits at timestamp 300, return 4.
  cout << hitCounter->getHits(301) << endl; // get hits at timestamp 301, return 3.


  delete hitCounter;


}