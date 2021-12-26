#include <algorithm>
#include <iostream>

#include "queue.hpp"
#include "square.hpp"

int main()
{
	int posision;
	containers::queue<Square<int>> q;

	std::cout << "1 - push\n"
			  << "2 - top\n"
			  << "3 - pop\n"
			  << "4 - erase_to_num\n"
			  << "5 - insert_to_num\n"
			  << "6 - for_each\n"
			  << "7 - count_if\n"
			  << "0 - exit\n";

	for (;;) {
		int command;
		std::cin >> command;

		if (command == 1) {
			Square<int> Square(std::cin);
			q.push(Square);
			std::cout << std::endl;
		} else if (command == 2) {
			q.top().print();
		} else if (command == 4) {
			std::cin >> posision;
			q.erase_to_num(posision);
		} else if (command == 0) {
			break;
		} else if (command == 5) {
			std::cin >> posision;
			Square<int> f(std::cin);
			q.insert_to_num(posision, f);
		} else if (command == 3) {
			q.pop();
		} else if (command == 6) {
			std::for_each(q.begin(), q.end(), [] (Square<int> Square) {return Square.print();});
		} else if (command == 7) {
			int are;
            std::cin >> are;
                std::cout << std::count_if(q.begin(), q.end(), [are](Square<int> r){return r.area() < are;}) << std::endl;
		} else {
			std::cout << "ERROR" << std::endl;
			break;
		}
	}

	return 0;
}