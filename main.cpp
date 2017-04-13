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
			}
			catch (const std::exception & e) {
				std::cout << "Exception thrown: " << e.what() << std::endl;
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

	std::cout << "Keith Miklas" << std::endl;
	std::cout << "732-233-7457" << std::endl;
	std::cout << "Hash table exercise - 12 Apr 2017" << std::endl << std::endl;

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

	// Timed
	std::wcout << "TIMED" << std::endl << std::endl;
	std::chrono::high_resolution_clock::time_point begin, end;
	std::chrono::duration<double> d;

	// Timed insertion
	begin = std::chrono::high_resolution_clock::now();
	h.insert(1024, "xi");
	end = std::chrono::high_resolution_clock::now();
	d = std::chrono::duration_cast<std::chrono::duration<double>> (end - begin) * 1000000000;
	std::cout << d.count() << "ns\t\t{1024, \"xi\"} key:value pair inserted." << std::endl;

	// Timed retrieval
	begin = std::chrono::high_resolution_clock::now();
	std::string s = h.get(1024);
	end = std::chrono::high_resolution_clock::now();
	d = std::chrono::duration_cast<std::chrono::duration<double>> (end - begin) * 1000000000;
	std::cout << d.count() << "ns\t\tKey 1024 retrieved, value: " << s << std::endl << std::endl;

	// End state
	std::cout << "END STATE" << std::endl << std::endl;

	h.print();

	std::cout << std::endl;
	std::cout << "Enter 'e' and press Enter to end: ";
	std::cin.get();
	std::cout << "\n\n";
	return 0;
}


// *******************************
// OUTPUT
// *******************************
//
// Buckets: 7

// INSERTION

// BUCKET 0 : [32767, delta] -->[0, gamma] -->[42, beta] --> NULL
// BUCKET 1: [1, theta] -->[29, epsilon] --> NULL
// BUCKET 2: [947, lambda] --> NULL
// BUCKET 3: NULL
// BUCKET 4 : [74, heta] -->[123, zeta] --> NULL
// BUCKET 5: [10225, mu] -->[33, kappa] --> NULL
// BUCKET 6: NULL

// RETRIEVAL

// Get 29 : epsilon
// Get 34 :
// Get 10225 : mu

// TIMED

// 1793ns        { 1024, "xi" } key:value pair inserted.
// 256ns         Key 947 retrieved.

// Enter 'e' and press Enter to end:
//



