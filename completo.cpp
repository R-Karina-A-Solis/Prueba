#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>   // Para exit()
#include <algorithm> // Para std::swap
#include <ctime>     // Para medir el tiempo

using namespace std;

// Función de partición para QuickSort
int partition(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Implementación de QuickSort
void quickSort(double arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Implementación de búsqueda por interpolación
int interpolationSearch(double arr[], int size, double target) {
    int inicio = 0, fin = size - 1;

    while (inicio <= fin && target >= arr[inicio] && target <= arr[fin]) {
        // Calcular la posición estimada
        int pos = inicio + ((target - arr[inicio]) * (fin - inicio)) / (arr[fin] - arr[inicio]);

        if (arr[pos] == target) {
            return pos; // Número encontrado
        } else if (arr[pos] < target) {
            inicio = pos + 1;
        } else {
            fin = pos - 1;
        }
    }

    return -1; // Número no encontrado
}

int main() {
    // Leer el archivo
    ifstream archivo("numeros_aleatorios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al leer el archivo" << endl;
        exit(1);
    }

    // Contar cuántos números hay en el archivo
    string linea;
    int cantidad_numeros = 0;
    while (getline(archivo, linea)) {
        cantidad_numeros++;
    }

    // Reservar memoria para el arreglo dinámico
    double* numeros = new double[cantidad_numeros];

    // Volver al inicio del archivo para leer los números
    archivo.clear();
    archivo.seekg(0, ios::beg);

    int indice = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> numeros[indice++];
    }
    archivo.close();

    // Mostrar números antes de ordenar
    cout << "Numeros antes de ordenar:" << endl;
    for (int i = 0; i < cantidad_numeros; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Ordenar los números
    quickSort(numeros, 0, cantidad_numeros - 1);

    // Mostrar números después de ordenar
    cout << "Numeros despues de ordenar:" << endl;
    for (int i = 0; i < cantidad_numeros; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Pedir el número a buscar
    double numero_a_buscar;
    cout << "Ingrese el número que desea buscar: ";
    cin >> numero_a_buscar;

    // Medir el tiempo de búsqueda
    clock_t start_time = clock();
    int posicion = interpolationSearch(numeros, cantidad_numeros, numero_a_buscar);
    clock_t end_time = clock();

    // Calcular tiempo de ejecución
    double tiempo_ejecucion = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Mostrar resultados
    if (posicion != -1) {
        cout << "El número " << numero_a_buscar << " se encuentra en la posición " << posicion << "." << endl;
    } else {
        cout << "El número " << numero_a_buscar << " no se encuentra en el arreglo." << endl;
    }
    cout << "Tiempo de ejecución de la búsqueda: " << tiempo_ejecucion << " segundos." << endl;

    // Liberar memoria
    delete[] numeros;

    return 0;
}
