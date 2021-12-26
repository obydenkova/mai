#include "IPAddress.h"

IPAddress::IPAddress(unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4)
: part1(p1), part2(p2), part3(p3), part4(p4) {

}

IPAddress IPAddress::Sum(const IPAddress &other) const {
    unsigned char new_part1;
    unsigned char new_part2;
    unsigned char new_part3;
    unsigned char new_part4;
    if ((int)part1 + (int)other.part1 > 255) {
        new_part1 = 255;
    } else {
        new_part1 = part1 + other.part1;
    }
    if ((int)part2 + (int)other.part2 > 255) {
        new_part2 = 255;
    } else {
        new_part2 = part2 + other.part2;
    }
    if ((int)part3 + (int)other.part3 > 255) {
        new_part3 = 255;
    } else {
        new_part3 = part3 + other.part3;
    }
    if ((int)part4 + (int)other.part4 > 255) {
        new_part4 = 255;
    } else {
        new_part4 = part4 + other.part4;
    }
    return {new_part1, new_part2, new_part3, new_part4};
}

IPAddress IPAddress::Subtract(const IPAddress &other) const {
    unsigned char new_part1;
    unsigned char new_part2;
    unsigned char new_part3;
    unsigned char new_part4;
    if ((int)part1 - (int)other.part1 < 0) {
        new_part1 = 0;
    } else {
        new_part1 = part1 - other.part1;
    }
    if ((int)part2 - (int)other.part2 < 0) {
        new_part2 = 0;
    } else {
        new_part2 = part2 - other.part2;
    }
    if ((int)part3 - (int)other.part3 < 0) {
        new_part3 = 0;
    } else {
        new_part3 = part3 - other.part3;
    }
    if ((int)part4 - (int)other.part4 < 0) {
        new_part4 = 0;
    } else {
        new_part4 = part4 - other.part4;
    }
    return {new_part1, new_part2, new_part3, new_part4};
}

bool IPAddress::operator=(const IPAddress &other) const {
    return std::tie(part1, part2, part3, part4) == std::tie(other.part1, other.part2, other.part3, other.part4);
}

bool IPAddress::operator>(const IPAddress &other) const {
    return std::tie(part1, part2, part3, part4) > std::tie(other.part1, other.part2, other.part3, other.part4);
}

bool IPAddress::operator<(const IPAddress &other) const {
    return std::tie(part1, part2, part3, part4) < std::tie(other.part1, other.part2, other.part3, other.part4);
}

bool IPAddress::BelongToSubnet(const IPAddress& subnet_address, const IPAddress& subnet_mask) const {
    IPAddress conj = IPAddress(part1 & subnet_mask.part1, part2 & subnet_mask.part2, part3 & subnet_mask.part3, part4 & subnet_mask.part4);
    return conj.operator=(subnet_address);
}

std::ostream& operator << (std::ostream& os, const IPAddress& address) {
    return os << (int)address.part1 << "." << (int)address.part2 << "." << (int)address.part3 << "." << (int)address.part4;
}

std::istream& operator >> (std::istream& is, IPAddress& address) {
    unsigned char part1;
    unsigned char part2;
    unsigned char part3;
    unsigned char part4;
    std::string str_address;
    is >> str_address;
    std::stringstream ss(str_address);
    getline(ss, str_address,'.');
    address.part1 = std::stoi(str_address);
    getline(ss, str_address,'.');
    address.part2 = std::stoi(str_address);
    getline(ss, str_address,'.');
    address.part3 = std::stoi(str_address);
    getline(ss, str_address);
    address.part4 = std::stoi(str_address);
    return is;
}
 IPAddress operator""_ip(const char* str, size_t size) {//  1.1.1.1
     std::istringstream is(str);
     char tmp;
     int p1,p2,p3,p4;
    is >> p1 >> tmp >> p2 >> tmp >> p3 >> tmp >> p4;
    return{p1,p2,p3,p4};
 }