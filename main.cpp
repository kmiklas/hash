#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <forward_list>
#include <utility>
#include <chrono>

namespace qb {

	const int HASHSIZE{ 7 };

	class HashTable {
	public:
		HashTable() {
			table_ = std::vector<std::forward_list<std::pair<int, std::string>>>(HASHSIZE);
		}
		bool insert(int key, std::string value) {
			try {
				if (get(key) == "") { // If identical key exists, do not overwrite
					std::pair<int, std::string> myPair(key, value);
					int hashedKey = hash_(key);
					it_ = table_[hashedKey].before_begin();
					table_[hashedKey].emplace_after(it_, myPair);
				}				
			} catch(const std::exception & e) {
				return false;
			}
			return true;
		}
		std::string get(int key) {
			for (it_ = table_[hash_(key)].begin(); it_ != table_[hash_(key)].end(); ++it_)
				if (it_->first == key)
					return it_->second;
			return "";
		};
		void print() {
			for (int i = 0; i < HASHSIZE; ++i) {
				std::cout << "BUCKET " << i << ": ";
				for (it_ = table_[i].begin(); it_ != table_[i].end(); ++it_)
					std::cout << "[" << it_->first << ", " << it_->second << "]" << " --> ";
				std::cout << "NULL" << std::endl;
			}
		}
	private:
		std::vector<std::forward_list<std::pair<int, std::string>>> table_;
		std::forward_list<std::pair<int, std::string>>::iterator it_;

		// Hashing function
		int hash_(int key) {
			return (key % HASHSIZE);
		}
	};
}

int main() {
	qb::HashTable h;

	std::cout << "Buckets: " << qb::HASHSIZE << std::endl << std::endl;

	// Insertion
	std::wcout << "INSERTION" << std::endl << std::endl;
	h.insert(42, "beta");
	h.insert(0, "gamma");
	h.insert(32767, "delta");
	h.insert(29, "epsilon");
	h.insert(123, "zeta");
	h.insert(74, "heta");
	h.insert(1, "theta");
	h.insert(42, "iota");
	h.insert(33, "kappa");
	h.insert(947, "lambda");
	h.insert(10225, "mu");
	h.print();
	std::cout << std::endl;

	// Retrieval
	std::wcout << "RETRIEVAL" << std::endl << std::endl;
	std::cout << "Get 29: " << h.get(29) << std::endl;
	std::cout << "Get 34: " << h.get(34) << std::endl;
	std::cout << "Get 10225: " << h.get(10225) << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Enter 'e' and press Enter to end: ";
	std::cin.get();
	std::cout << "\n\n";
	return 0;
}