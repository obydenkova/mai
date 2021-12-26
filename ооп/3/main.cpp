#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>


#include "point.h"
#include "trapeze.h" 
#include "quadrate.h" 
#include "rectangle.h"
#include "figure.h"

void print_help() {

    std::cout << "'add quadrate'          - Create quadrate"   << std::endl;
    std::cout << "'add rectangle'         - Create rectangle"  << std::endl;
    std::cout << "'add trapeze'           - Create trapeze"    << std::endl;
    std::cout << "'print tops'            - Output tops"       << std::endl;
    std::cout << "'print square'          - Output square"     << std::endl;
    std::cout << "'print center'          - Output center"     << std::endl;
    std::cout << "'delete *id*'           - Delete figure"     << std::endl;
    std::cout << "'help'                  - Get help"          << std::endl;
    std::cout << "'exit'                  - Exit"              << std::endl;
}
    
void print_ERROR(int error_code){
    if(error_code == 1){
        std::cout << "Incorrect command\n";
    }
    else if(error_code == 2){
        std::cout << "incorrect coordinates for a figure\n";
    }
    else{
        std::cout << "There is no item with the given index\n";
    }
    char c;
    c = getchar();
    while(c != '\n' && c != EOF){
        c = getchar();
    }
}

int main(){ 
    print_help();
    std::vector<fig*> figs;
    for( ; ; ){
        char com1[40];
        std::cin >> com1;

        if(strcmp(com1, "add") == 0){
            char com2[40];
            std::cin >> com2;
            fig* new_fig;

            if(strcmp(com2, "trapeze") == 0){
                new_fig = new trapeze(std::cin);

            } else if(strcmp(com2, "quadrate") == 0){
                new_fig = new quadrate(std::cin);

            } else if(strcmp(com2, "rectangle") == 0){
                new_fig = new rectangle(std::cin);
                
            } else{
                print_ERROR(1);
            }
            figs.push_back(new_fig);
      
        } else if(strcmp(com1, "print") == 0){
            char com2[40];
            std::cin >> com2;
            if(strcmp(com2, "tops") == 0){
                for(fig* cur_fig: figs){
                    cur_fig -> print(std::cout);
                }
            }
            else if(strcmp(com2, "square") == 0){
                for(fig* cur_fig: figs){
                    std::cout << cur_fig -> square() << "\n";
                }
            }
            else if(strcmp(com2, "center") == 0){
                for(fig* cur_fig: figs){
                    point tmp = cur_fig -> center();
                    std::cout << "(" << tmp.x << ", " << tmp.y << ")\n";
                }
            }  
            else{
                std::cout << "Incorrect command\n";
            }
        } 
            else if(strcmp(com1, "delete") == 0){
            int id;
            std::cin >> id;
            if(id >= figs.size()){
                print_ERROR(3);
                continue;
            }
            delete figs[id];
            figs.erase(figs.begin() + id);
        } 
         else if (strcmp(com1, "help") == 0){
            print_help();
            continue;
        } else if(strcmp(com1, "exit") == 0){
            break;
        } else {
            print_ERROR(1);
        }
    }
   for(size_t i = 0; i < figs.size(); ++i){
        delete figs[i];
    }
    return 0;
    
    }