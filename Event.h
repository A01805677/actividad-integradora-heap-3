#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Definiciones de estructuras
struct ip {
    int o1, o2, o3, o4;
};

struct event {
    std::tm ts;
    ip ip_o;
    std::string port_o;
    std::string domain_o;
    ip ip_d;
    std::string port_d;
    std::string domain_d;
};

//Sobrecargas
std::ostream& operator<<(std::ostream& os, const ip& i);
std::ostream& operator<<(std::ostream& os, const event& e);
bool operator<(const ip& i1, const ip& i2);
bool operator<(const event& e1, const event& e2);
bool operator==(const ip& i1, const ip& i2);

//Funcion
std::vector<event> vectorizeCSV(const std::string& iFile);
ip crearIP(const std::string& str);
