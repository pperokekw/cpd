#include <iostream>
#include <vector>

using namespace std;

void quicksort(vector<int>& nums);
void quicksort_aux(vector<int>& nums, int i, int f);
int particiona(vector<int>&nums, int esq, int dir);

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
  quicksort(vetor);
  for(int i = 0; i < 10; i++){
    cout << vetor[i] << " ";
  }
  cout << endl;


  return 0;

}


void quicksort(vector<int>& nums){
  quicksort_aux(nums, 0, nums.size()-1);
}

void quicksort_aux(vector<int>& nums, int i, int f){
  int p;
  if(f>i){
    p = particiona(nums, i, f);
    quicksort_aux(nums, i, p-1);
    quicksort_aux(nums, p+1, f);
  }
}

int particiona(vector<int>& nums, int esq, int dir){
  int i = esq+1;
  int j = dir;
  int pivo = esq;
  while(j>i){
    while(nums[i]<nums[pivo] && i <dir){
      i++;
      //comparacoes++
    }
    while(nums[j]>=nums[pivo] && j>esq){
      j--;
      //comparacoes++;
    }
    if(i<j && nums[i]>nums[j]){
      swap(nums[i],nums[j]);
      //comparacoes++;
      //trocas++;
    }
  }
  if(nums[j]<nums[pivo]){
    swap(nums[pivo],nums[j]);
    //comparacoes++;
    //trocas++;
  }
  return j;
}
