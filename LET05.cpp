#include <fstream>
#include <string>
#include <functional>
#include <array>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;



#define N_ALGOS 5 // 1 - bubblesort; 2 - combsort; 3 - shakesort; 4 - quicksort; 5 - random quicksort
#define QTD_ARRAYS 3
#define POTENCIAS 5
#define GAP_SHRINK 1.3

struct  log_info{
    int comparacoes = 0;
    int trocas = 0;
    double tempo = 0;
    int tamanho = 0;
    string sigla;
    char tipo = ' ';
};

struct  algo_info{
    string name;
    string acronym;
    std::function<void(vector<int>&, log_info&)> function;
};

struct  array_info{
    string name;
    char type = ' ';
    vector<int> contents;
};


void bubblesort(vector<int>& nums, log_info& log);
void combsort(vector<int>& nums, log_info& log);
void shakesort(vector<int> &nums, log_info& log);
void quicksort(vector<int>& nums, log_info& log);
void quicksort_aux(vector<int>& nums, int i, int f, log_info& log);
void quicksortRandom(vector<int>& nums, log_info& log);
void quicksortRandom_aux(vector<int>& nums, int i, int f, log_info& log);
int particiona(vector<int>&nums, int esq, int dir, log_info& log);




int main(){
  using namespace std::chrono;
  int info_total = N_ALGOS*4*POTENCIAS;
  int potencia, size, result;
  array<array_info, QTD_ARRAYS> arrays;
  array<algo_info, N_ALGOS> algoritmos;
  vector<log_info> results;
  srand(42);
  result  = 0;
  // Inicializando BubbleSort:
  algoritmos[0].name ="BubbleSort";
  algoritmos[0].acronym = "BBST";
  algoritmos[0].function = bubblesort;

  // Inicializando CombSort:
  algoritmos[1].name = "CombSort";
  algoritmos[1].acronym = "CMBST";
  algoritmos[1].function = combsort;

  // Inicializando ShakeSort:
  algoritmos[2].name = "ShakeSort";
  algoritmos[2].acronym = "SHKST";
  algoritmos[2].function = shakesort;

  // Inicializando QuickSort Simples:

  algoritmos[3].name ="Simple QuickSort";
  algoritmos[3].acronym = "SMQQS";
  algoritmos[3].function = quicksort;


  algoritmos[4].name ="Random QuickSort";
  algoritmos[4].acronym = "RDQQS";
  algoritmos[4].function = quicksortRandom;

  for(potencia=2;potencia<POTENCIAS;potencia++){
    size = (int)pow(10.0, (float)potencia);
    arrays[0].type = 'C';
    arrays[0].name = "Crescente";
    arrays[0].contents.resize(size);
    for(int i=0;i<size;i++){
      arrays[0].contents[i] = i+1;
    }
    arrays[1].type = 'D';
    arrays[1].name = "Decrescente";
    arrays[1].contents.resize(size);
    for(int i = 0 ; i<size;i++){
      arrays[1].contents[i] = size-i;
    }
    

    arrays[2].type ='R';
    arrays[2].name = "Randomico";
    arrays[2].contents.resize(size);
    for(int& val: arrays[2].contents) val = rand() % size+1;

    for(int arr = 0; arr<QTD_ARRAYS; arr++){
      cout << "ARRAY " << arrays[arr].name << " de tamanho " << size <<endl;
      for(int i = 0; i<size; i++) cout <<arrays[arr].contents[i] <<" ";
      cout << endl;
      for(int algo = 0; algo<N_ALGOS; algo++){
        cout << endl;
        cout << "Ordenando array por " << algoritmos[algo].name << endl;

        vector<int> tmp_array = arrays[arr].contents;

        log_info log;

        auto start = chrono::high_resolution_clock::now();
        algoritmos[algo].function(tmp_array, log);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end -start;
        log.tempo = elapsed.count();
        log.sigla = algoritmos[algo].acronym;
        log.tipo = arrays[arr].type;
        log.tamanho = size;

        results.push_back(log);
        cout <<"Quantidade de trocas: " << log.trocas <<endl;
        cout << "Quantidade de comparacoes: " <<log.comparacoes << endl;
        cout << "Tempo de processamento: " << log.tempo << "s" << endl;
      }
      cout <<endl;
    }
    cout <<endl;
  }
  ofstream outfile("results.txt");
  if (!outfile.is_open()) {
      cerr << "Erro ao abrir o arquivo para escrita!\n";
      return 1;
  }
  cout << "Algoritmo|\tTipo\t|\tTamanho\t|\tTrocas\t\t|\tComparacoes\t|\tTempo (s)\n" << endl;
  outfile << "Algoritmo,Tipo,Tamanho,Trocas,Comparacoes,Tempo (s)\n";
  for (const auto& log : results) {
      // Escreve no console
      cout << log.sigla << "\t|\t" << log.tipo << "\t|\t"
              << log.tamanho << "\t|\t" << log.trocas << "\t\t|\t"
              << log.comparacoes << "\t|\t" << log.tempo << "\n";
      
      // Escreve no arquivo
      outfile << log.sigla << "," << log.tipo << "," << log.tamanho << ","
              << log.trocas << "," << log.comparacoes << "," << log.tempo << "\n";
  }
}

void bubblesort(vector<int>& nums, log_info& log){
  log.tamanho = nums.size();
  for(int i = 0; i < nums.size()-1; i++){
    bool trocou = false;
    for(int j = 0; j< nums.size() -i -1; j++){
      log.comparacoes++;
      if(nums[j]>nums[j+1]){
        log.trocas++;
        swap(nums[j],nums[j+1]);
        trocou = true;
      }
    }
    if(!trocou){
      break;
    }
  }

}


void combsort(vector<int>& nums, log_info& log){
  log.tamanho = nums.size();
  int gap = nums.size();
  bool trocou = true;
  while (gap > 1 || trocou){
    gap = gap/GAP_SHRINK;
    if (gap < 1) gap = 1;
    trocou = false;
    for(int i = 0; i < nums.size()-gap; i++){
      log.comparacoes++;
      if(nums[i] > nums[i+gap]){
        log.trocas++;
        swap(nums[i], nums[i+gap]);
        trocou = true;
      }
    }
    if(gap> 1 && !trocou) gap =1;
  }
}


void shakesort(vector<int>& nums, log_info& log){
  log.tamanho = nums.size();
  int comeco = 0;
  int j = nums.size() - 1;
  bool trocou = true;
  while(trocou){
    trocou = false;
    for(int i = comeco; i< j; i++){
      log.comparacoes++;
      if(nums[i] > nums[i+1]){
        swap(nums[i],nums[i+1]);
        trocou = true;
        log.trocas++;
      }
    }
    if(!trocou) break;
    trocou = false;
    --j;
    for(int i = j-1; i>=comeco; i--){
      log.comparacoes++;
      if(nums[i]>nums[i+1]){
        log.trocas++;
        swap(nums[i], nums[i+1]);
        trocou = true;
      }
    }
    comeco++;
  }
}

// Fiz uma implementação pra ver se o array está ordenado, no melhor caso fica O(n)
// Não ocorrem trocas, mas durante a verificação da ordenação são executadas n comparações, por isso O(n) no melhor caso (array já ordenado)
// Também não cairia na condição para ordenação em caso de todos os elementos serem iguais

void quicksort(vector<int>& nums, log_info& log){
  bool ordenado = true;
  log.comparacoes=0;
  log.trocas = 0;
  for(int i = 0; i < nums.size()-1; i++){
    log.comparacoes++;
    if(nums[i]>nums[i+1]){
      ordenado = false;
      break;
    } 
  }
  if(!ordenado){
    quicksort_aux(nums, 0, nums.size()-1, log);
  }
}

void quicksort_aux(vector<int>& nums, int i, int f, log_info& log){
  int p;
  if(f>i){
    p = particiona(nums, i, f, log);
    quicksort_aux(nums, i, p-1, log);
    quicksort_aux(nums, p+1, f, log);
  }
}

int particiona(vector<int>& nums, int esq, int dir, log_info& log){
  int i = esq+1;
  int j = dir;
  int pivo = esq;
  while(j>i){
    while(nums[i]<nums[pivo] && i <dir){
      i++;
      log.comparacoes++;
    }
    while(nums[j]>=nums[pivo] && j>esq){
      j--;
      log.comparacoes++;
    }
    if(i<j && nums[i]>nums[j]){
      swap(nums[i],nums[j]);
      log.comparacoes++;
      log.trocas++;
    }
  }
  if(nums[j]<nums[pivo]){
    swap(nums[pivo],nums[j]);
    log.comparacoes++;
    log.trocas++;
  }
  return j;
}

// Para a implementação de um quicksort melhor, escolhi a opção do pivô randomico, achei mais legal


void quicksortRandom(vector<int>& nums, log_info& log){
  srand(time(nullptr));
  bool ordenado = true;
  log.comparacoes=0;
  log.trocas = 0;
  for(int i = 0; i < nums.size()-1; i++){
    log.comparacoes++;
    if(nums[i]>nums[i+1]){
      ordenado = false;
      break;
    } 
  }
  if(!ordenado){
    quicksortRandom_aux(nums, 0, nums.size()-1, log);
  }
}

void quicksortRandom_aux(vector<int>& nums, int i, int f, log_info& log){
  int p;
  if(f>i){
    int randomPivot = i + rand()%(f-i+1);
    swap(nums[i],nums[randomPivot]);
    p = particiona(nums, i, f, log);
    quicksortRandom_aux(nums, i, p-1, log);
    quicksortRandom_aux(nums, p+1, f, log);
  }
}
