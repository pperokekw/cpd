#include <iostream>
#include <vector>
using namespace std;

void combsort(vector<int>& nums);

int main(){
  vector<int> vetor;
  vetor.resize(10);
  srand(42);
  for(int i = 0; i < 10; i++){
    vetor[i] = rand() % 10+1;
  }
  for(int i = 0; i < 10; i++){
    cout << vetor[i] << " ";
  }
  cout << endl;
  combsort(vetor);
  for(int i = 0; i < 10; i++){
    cout << vetor[i] << " ";
  }
  cout << endl;


  return 0;
}


void combsort(vector<int>& nums){
  int gap = nums.size();
  bool trocou = true;
  while(gap>1 || trocou){
    gap = gap/1.3;
    if(gap<1) gap =1;
    trocou =false;
    for(int i =0; i< nums.size() - gap; i++){
      if(nums[i] > nums[i+gap]){
        swap(nums[i],nums[i+gap]);
        trocou = true;
      }
    }

  }
}
