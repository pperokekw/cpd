#include <iostream>
#include <random>
using namespace std;

void insertionSort(int c[], int len){
  int i = 0, j = 0, chave = 0;
  for(j =1; j < len; j++){ // from j = 1 to n-1 
    chave = c[j]; // seleciona o elemento do array ordenado
    i = j-1;
    while((i>=0) && (c[i]>chave))
    {
      c[i+1] = c[i];
      i--;
    }
    c[i+1] = chave;
  }
}

void printArray(int arr[], int len){
  for(int i =0; i< len; i++){
    std::cout << arr[i] << " ";
  }
  cout << endl;
}
int main(){
  int array[10];
  std::random_device rd;
  std::mt19937 gen(rd());
  

  for(int i = 0; i<10; i++){
    std::uniform_int_distribution<> distr(0,30);
    int random_number = distr(gen);
    array[i] = random_number;
  }
  printArray(array, 10);
  insertionSort(array, 10);
  printArray(array, 10);
  return 0;
}
