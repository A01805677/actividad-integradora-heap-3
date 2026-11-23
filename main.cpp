#include <iostream>
#include <ctime>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "Event.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::pair;

// Overload of << operator for pair<ip, int>
std::ostream& operator<<(std::ostream &os, const pair<ip, int> &p) {
    os << p.first << ": " << p.second; // ip: count
    return os;
}

// Sobrecarga del operador para el objeto tipo stt::pair<ip, int>
bool operator<(const pair<ip, int> &p1, const pair<ip, int> &p2)
{
    return p1.second < p2.second;
}

void construirHeap(std::vector<std::pair<ip, int>>& accesos) {
    // Tiene el rango de inicio y del final con el que va a trabajr la ficnion
    std::make_heap(accesos.begin(), accesos.end());
}
// TODO
int main()
{
    // Declare vector of pairs of <ip, int>
    vector<pair<ip, int>> pairs;
   
    vector<event> bitacora = vectorizeCSV("Resultado2.csv");
    for (event& ev : bitacora) {
        if (pairs.size() == 0) {
            pairs.push_back(std::make_pair(ev.ip_d, 1));
            continue;
        };
        if (!(ev.ip_d == pairs.back().first)) {
            pairs.push_back(std::make_pair(ev.ip_d, 1));
        }
        else {
            pairs.back().second += 1;
        }
    }

    construirHeap(pairs);

    // Ask the user for a number N
    int i;
    cout << "Porfavor ingrese el numero de IPs mas frecuentadas que desea ver: ";
    cin >> i;
    try {
        if (i < 0) {
            cout << "El valor tiene que ser mayor a 0";
        }
        if (i > pairs.size()) {
            cout << "El valor tiene que ser menor o igual al numero de ip registradas";
        }
    }
    catch (const std::exception& e) {
        cout << "Parece que hubo un error al capturar el valor, porfavor ingrese de nuevo el valor";
    }

    // Show the N ips with the highest counter
    for (int c = 0; c < i; ++c) {
        pair<ip, int> top = pairs.front();
        pop_heap(pairs.begin(), pairs.end());
        pairs.pop_back();
        cout << c + 1 << ". IP: " << top.first << " | Accesos: " << top.second << "\n";
    }

}
