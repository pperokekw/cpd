#include <iostream>
#include <vector>
#include <random>

using namespace std;

void selectionSort(vector<int>& nums);

int main(){
  vector<int> vetor;
  vetor.resize(10);
  random_device rd;

  mt19937 gen(rd());
  for(int i = 0; i <10; i++){
    uniform_int_distribution<> distr(0,30);
    int random_number = distr(gen);
    vetor[i] = random_number;
  }



  for(int  i = 0; i<10; i++) cout << vetor[i] << " ";
  cout << endl;
  selectionSort(vetor);
  
  for(int  x = 0; x < 10; x++) cout << vetor[x] << " ";
  cout << endl;
}


void selectionSort(vector<int>& vetor){
  int i,j, min, aux;
  for(int i = 0; i < vetor.size()-1; i++){
     min = i;
    for(j = i+1; j < vetor.size();j++){
      if(vetor[j] < vetor[min]){
        min = j;
      }
    }
    swap(vetor[i],vetor[min]);
  }

}
