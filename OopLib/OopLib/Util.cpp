#include "Util.h"

void Util::printArray(const std::vector<int>& arr) {
	for (unsigned int i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << " ";
	}
}