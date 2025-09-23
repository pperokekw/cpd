#include <iostream>
#include <vector>

using namespace std;


void shakesort(vector<int>& nums);

int main(){
  vector<int> nums;
  srand(22);
  nums.resize(10);
  for(int i = 0; i< 10; i++) nums[i] = rand()%10+1;
  for(int i = 0; i < 10; i++) cout <<nums[i] << " ";
  cout << endl;
  shakesort(nums);
  for(int i = 0; i < 10; i++) cout <<nums[i] << " ";
  cout<<endl;
  return 0;
}

void shakesort(vector<int>& nums){
  bool trocou = true;
  int comeco = 0;
  int j = nums.size() - 1;


  while(trocou){
    trocou = false;
    for(int i = comeco; i < j; i++){
      if(nums[i] > nums[i+1]){
        swap(nums[i],nums[i+1]);
        trocou = true;
      }
    }
    if(!trocou)
      break;
    trocou = false;
    --j;
    for(int i = j-1; i>=comeco; i--){
      if(nums[i] > nums[i+1]){
        swap(nums[i],nums[i+1]);
        trocou = true;
      }
    }
    comeco++;
  }
}
