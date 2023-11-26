#include <iostream>
#include <vector>
using namespace std;


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


class Solution1342 {
public:
  int numberOfSteps(int num) {
    int i = 0;
    while (num != 0)
    {
        if (num & 1)
        {
          num -= 1;
        } else
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
  Solution1365 solution1365;
  vector<int> nums = { 8, 1, 2, 2, 3 };
  solution1365.smallerNumbersThanCurrent(nums);
    
}