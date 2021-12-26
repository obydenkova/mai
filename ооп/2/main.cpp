#include <iostream>
#include "IPAddress.h"
#include <vector>
#include <string>

void print_help() {
    std::cout << "'create'              - Create IpAddress"  << std::endl;
    std::cout << "'operation +/-'       - Perform + or -"   << std::endl;
    std::cout << "'compare =/>/<'       - Perform = or > or <"  << std::endl;
    std::cout << "'check_subnet'        - Check subnet"    << std::endl;
    std::cout << "'exit'                - Exit"    << std::endl;
    std::cout << "'help'                - Help"    << std::endl;
}

int main() {
IPAddress adr0 = "1.1.1.1"_ip;

     print_help();

    std::vector<IPAddress> Addresses;
    std::string command;
    while (std::cin >> command) {
        if (command == "create") {
            IPAddress new_address;
            std::cin >> new_address;
            Addresses.push_back(new_address);
            std::cout << "literal is " << adr0 << "\n"
                      << "Address number " << Addresses.size() << "\n"
                      << "Address: " << Addresses.back() << "\n";
        } else if (command == "compare") {
            std::string compare_string;
            size_t lhs, rhs;
            std::cin >> compare_string >> lhs >> rhs;
            lhs--;
            rhs--;
            if (lhs >= Addresses.size() || rhs >= Addresses.size() || compare_string.size() != 1
                 || (compare_string[0] != '=' && compare_string[0] != '>' && compare_string[0] != '<')) {
                std::cout << "Incorrect parameters" << "\n";
                continue;
            }

            char compare = compare_string[0];

            std::cout << lhs + 1 << " " << rhs + 1 << " " << compare << " ";


            if (compare == '<') {
                std::cout << std::boolalpha << (Addresses[lhs] < Addresses[rhs]) << "\n";
            } else if (compare == '=') {
                std::cout << std::boolalpha << (Addresses[lhs] = Addresses[rhs]) << "\n";
            } else if (compare == '>') {
                std::cout << std::boolalpha << (Addresses[lhs] > Addresses[rhs]) << "\n";
            }
        } else if (command == "operation") {
            std::string operation_string;
            int lhs, rhs;
            std::cin >> operation_string >> lhs >> rhs;
            rhs--;
            lhs--;
            if (lhs >= Addresses.size() || rhs >= Addresses.size() || operation_string.size() != 1
                 || (operation_string[0] != '-' && operation_string[0] != '+')) {
                std::cout << "Incorrect parameters" << "\n";
                continue;
            }

            char operation = operation_string[0];

            std::cout << lhs + 1 << " " << operation << " " << rhs + 1 << "\n";


            if (operation == '+') {
                std::cout << Addresses[lhs].Sum(Addresses[rhs]) << "\n";
            } else if (operation == '-') {
                std::cout << Addresses[lhs].Subtract(Addresses[rhs]) << "\n";
            }
        } else if (command == "check_subnet") {
            std::cout << "Enter number of created address, subnet address and subnet mask" << "\n";
            IPAddress subnet_address;
            IPAddress subnet_mask;
            size_t number;
            std::cin >> number >> subnet_address >> subnet_mask;
            number--;
            if (number >= Addresses.size()) {
                std::cout << "Incorrect parameters" << "\n";
                continue;
            }
               std::cout << "Address is " << Addresses[number] << "\n"
                         << "Address is " << (Addresses[number].BelongToSubnet(subnet_address, subnet_mask) ? "" : "not ")
                         << "belong to subnet " << subnet_address << " with mask " << subnet_mask << "\n";
        }
        else if (command == "help") {
            print_help ();
        }
        else if (command == "exit") {
            break;
        } else {
            std::cin.ignore(32767,'\n');
            std::cout << "Unknown command\n";
        }
    }
    return 0;
}