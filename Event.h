#include "Event.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {
    std::tm crearFechaHora(const std::string& fstr, const std::string& hstr) {
        std::tm t{};
        char sep;
        int d, m, y, h, min, s;
        std::stringstream ssf(fstr);
        ssf >> d >> sep >> m >> sep >> y;
        t.tm_mday = d;
        t.tm_mon = m - 1; //Corrige el mes
        t.tm_year = y - 1900; //Corrige el año P.D. QUE LE IMPORTA

        std::stringstream ssh(hstr);
        ssh >> h >> sep >> min >> sep >> s;
        t.tm_hour = h;
        t.tm_min = min;
        t.tm_sec = s;
        return t;
    }
}

ip crearIP(const std::string& str) {
    if (str == "-") return { 0, 0, 0, 0 }; //NO BORRAR
    std::stringstream ss(str);
    std::string part;
    ip f;
    std::getline(ss, part, '.'); f.o1 = std::stoi(part);
    std::getline(ss, part, '.'); f.o2 = std::stoi(part);
    std::getline(ss, part, '.'); f.o3 = std::stoi(part);
    std::getline(ss, part, '.'); f.o4 = std::stoi(part);

    return f;
}

std::ostream& operator<<(std::ostream& os, const ip& i) {
    if (i.o1 == 0) {
        os << "-";
    }
    else {
        os << i.o1 << "." << i.o2 << "." << i.o3 << "." << i.o4;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const event& e) {
    char date_output[20];
    strftime(date_output, 20, "%d-%m-%Y,%T", &e.ts);
    os << date_output << "," << e.ip_o << "," << e.port_o << ","
        << e.domain_o << "," << e.ip_d << "," << e.port_d << ","
        << e.domain_d;
    return os;
}

std::vector<event> vectorizeCSV(const std::string& iFile) {
    std::vector<event> vecReg;
    std::ifstream file(iFile);
    std::string linea;

    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string fecha, hora, ip_o, port_o, domain_o,
            ip_d, port_d, domain_d;

        std::getline(ss, fecha, ',');
        std::getline(ss, hora, ',');
        std::getline(ss, ip_o, ',');
        std::getline(ss, port_o, ',');
        std::getline(ss, domain_o, ',');
        std::getline(ss, ip_d, ',');
        std::getline(ss, port_d, ',');
        std::getline(ss, domain_d, ',');

        if (!domain_d.empty() && domain_d.back() == '\r') {
            //Inompativilidad Windows vs Linux
            //Maten a C++
            domain_d.pop_back();
        }

        event e;
        e.ts = crearFechaHora(fecha, hora);
        e.ip_o = crearIP(ip_o);
        e.port_o = port_o;
        e.domain_o = domain_o;
        e.ip_d = crearIP(ip_d);
        e.port_d = port_d;
        e.domain_d = domain_d;

        vecReg.push_back(e);
    }
    return vecReg;
}

bool operator<(const ip& ip1, const ip& ip2) {
    if (ip1.o1 != ip2.o1) return ip1.o1 < ip2.o1;
    if (ip1.o2 != ip2.o2) return ip1.o2 < ip2.o2;
    if (ip1.o3 != ip2.o3) return ip1.o3 < ip2.o3;
    return ip1.o4 < ip2.o4;
}

bool operator==(const ip& ip1, const ip& ip2) {
    if (ip1.o1 != ip2.o1 ||
        ip1.o2 != ip2.o2 ||
        ip1.o3 != ip2.o3 ||
        ip1.o4 != ip2.o4) {
        return false;
    }
    return true;
};

// Sobrecarga del operador < para struct event (compara por IP de destino)
bool operator<(const event& e1, const event& e2) {
    return e1.ip_d < e2.ip_d;
}

