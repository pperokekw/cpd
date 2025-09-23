#include <iostream>
#include <random>

using namespace std;

void printArray(int arr[], int len){
  for (int i = 0; i < len; i++){
    cout << arr[i] << " ";
  }
  cout << endl;
}

void bubbleSort(int arr[], int len){
  int i, temp, k = 0, trocou = 1, m = len-1; 
  while(trocou){
    trocou = 0;
    for(i = 0; i < m; i++){ //cada varredura
      if(arr[i] > arr[i+1]){ //checa se o atual eh maior q o prox para trocar
        temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
        trocou = 1;
        k = i;
      }
    }
    m = k;
  }
}

int main(){
  int array[10];
  random_device rd;
  mt19937 gen(rd());

  for(int i = 0; i <10; i++){
    uniform_int_distribution<> distr(0,30);
    int random_number = distr(gen);
    array[i] = random_number;
  }

  printArray(array,10);
  bubbleSort(array,10);
  printArray(array,10);

  return 0;


}
