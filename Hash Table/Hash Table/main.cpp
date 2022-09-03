#include "HashTable.h"

int main() {
	HashTable table(17);
	const int size = 100;
	for (int i = 0; i < size; ++i) {
		table.insert(i);
	}
	table.insert(13050302);
	table.insert(13050302);
	table.insert(13050302);
	table.display();
	cout << table.getSize() << endl;
	table.remove(13050302);
	table.display();
	table.removeAll(13050302);
	table.display();
	system("PAUSE");
	return 0;
}