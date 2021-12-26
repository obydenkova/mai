#pragma once

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

class IPAddress {
public:
    IPAddress() = default;
    IPAddress(unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4);
    IPAddress Sum(const IPAddress& other) const;
    IPAddress Subtract(const IPAddress& other) const;
    bool operator>(const IPAddress& other) const;
    bool operator<(const IPAddress& other) const;
    bool operator=(const IPAddress& other) const;
    bool BelongToSubnet(const IPAddress& subnet_address, const IPAddress& subnet_mask) const;
    friend std::ostream& operator << (std::ostream& os, const IPAddress& address);
    friend std::istream& operator >> (std::istream& is, IPAddress& address);

private:
    unsigned char part1 = 0;
    unsigned char part2 = 0;
    unsigned char part3 = 0;
    unsigned char part4 = 0;
};
 IPAddress operator""_ip(const char* str, size_t size);