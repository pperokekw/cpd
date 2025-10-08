#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct log_info {
    long long comparacoes = 0;
    long long trocas = 0;
    double tempo = 0;
    int tamanho = 0;
    string sigla;
    char tipo = ' ';
};

struct algo_info {
    string name;
    string acronym;
    std::function<void(vector<int>&, log_info&)> function;
};

struct array_info {
    string name;
    char type = ' ';
    vector<int> contents;
};

void counting_sort(vector<int>& arr, log_info& log) {
    if (arr.empty()) {
        return;
    }

    int max_val = *max_element(arr.begin(), arr.end());
    log.comparacoes += arr.size(); 
    vector<int> count(max_val + 1, 0);
    vector<int> output(arr.size());

    for (int x : arr) {
        count[x]++;
    }

    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
        log.trocas++;  
    }

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
        log.trocas++;
    }
}

void counting_sort_by_digit(vector<int>& arr, int exp, log_info& log) {
    if (arr.empty()) return;

    vector<int> output(arr.size());
    int count[10] = {0}; 

    for (int i = 0; i < arr.size(); i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        log.trocas++;
    }

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
        log.trocas++;
    }
}

void radix_sort_lsd(vector<int>& arr, log_info& log) {
    if (arr.empty()) return;

    int max_val = *max_element(arr.begin(), arr.end());
    log.comparacoes += arr.size();

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        counting_sort_by_digit(arr, exp, log);
    }
}

void radix_sort_msd_recursive(vector<int>& arr, int exp, log_info& log) {
    if (arr.size() <= 1 || exp <= 0) {
        if (arr.size() > 1) {
            sort(arr.begin(), arr.end());
            log.trocas += arr.size() * log2(arr.size()); 
        }
        return;
    }

    vector<vector<int>> buckets(10);

    for (int number : arr) {
        int digit = (number / exp) % 10;
        buckets[digit].push_back(number);
        log.trocas++; 
    }

    for (int i = 0; i < 10; i++) {
        if (!buckets[i].empty()) {
            radix_sort_msd_recursive(buckets[i], exp / 10, log);
        }
    }

    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (int number : buckets[i]) {
            arr[index++] = number;
            log.trocas++; 
        }
    }
}

void radix_sort_msd(vector<int>& arr, log_info& log) {
    if (arr.empty()) return;

    int max_val = *max_element(arr.begin(), arr.end());
    log.comparacoes += arr.size();
    
    int exp = 1;
    while (max_val / exp > 0) {
        exp *= 10;
    }
    exp /= 10; 

    if (exp > 0) {
        radix_sort_msd_recursive(arr, exp, log);
    }
}


int main() {
    srand(time(NULL));

    vector<algo_info> algoritmos = {
        {"Counting Sort", "CS", counting_sort},
        {"Radix Sort LSD", "RSLSD", radix_sort_lsd},
        {"Radix Sort MSD", "RSMSD", radix_sort_msd}
    };
    const int N_ALGOS = algoritmos.size();

    vector<int> SIZES = {10000, 100000, 1000000};
    vector<log_info> results;

    for (int size : SIZES) {
        vector<int> random_vec(size);
        for(int i=0; i<size; i++) random_vec[i] = rand() % 100000;

        vector<int> sorted_vec = random_vec;
        sort(sorted_vec.begin(), sorted_vec.end());

        vector<int> reversed_vec = sorted_vec;
        reverse(reversed_vec.begin(), reversed_vec.end());

        array_info arrays[] = {
            {"Aleatorio", 'A', random_vec},
            {"Ordenado", 'O', sorted_vec},
            {"Invertido", 'I', reversed_vec}
        };
        const int QTD_ARRAYS = 3;

        for(int arr = 0; arr<QTD_ARRAYS; arr++){
          cout << "========================================================" << endl;
          cout << "ARRAY " << arrays[arr].name << " de tamanho " << size <<endl;
          cout << "========================================================" << endl;
          
          for(int algo = 0; algo<N_ALGOS; algo++){
            cout << endl;
            cout << "Ordenando array por " << algoritmos[algo].name << endl;

            vector<int> tmp_array = arrays[arr].contents;

            log_info log;

            auto start = chrono::high_resolution_clock::now();
            algoritmos[algo].function(tmp_array, log);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = end - start;
            log.tempo = elapsed.count();
            log.sigla = algoritmos[algo].acronym;
            log.tipo = arrays[arr].type;
            log.tamanho = size;

            results.push_back(log);
            cout <<"Quantidade de trocas: " << log.trocas <<endl;
            cout << "Quantidade de comparacoes: " <<log.comparacoes << endl;
            cout << "Tempo de processamento: " << fixed << setprecision(6) << log.tempo << "s" << endl;
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

    cout << "\n\n=============== RESULTADOS FINAIS ===============\n";
    cout << "Algoritmo|\tTipo\t|\tTamanho\t|\tTrocas\t\t|\tComparacoes\t|\tTempo (s)\n" << endl;
    outfile << "Algoritmo,Tipo,Tamanho,Trocas,Comparacoes,Tempo (s)\n";

    for (const auto& log : results) {
        cout << log.sigla << "\t|\t" << log.tipo << "\t|\t"
             << log.tamanho << "\t|\t" << log.trocas << "\t\t|\t"
             << log.comparacoes << "\t|\t" << fixed << setprecision(6) << log.tempo << "\n";
        
        outfile << log.sigla << "," << log.tipo << "," << log.tamanho << ","
                << log.trocas << "," << log.comparacoes << "," << log.tempo << "\n";
    }
    
    outfile.close();
    return 0;
}
