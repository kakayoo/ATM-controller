
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class FakeBankAPI {
private:
	vector<string> available_pin_number{"SN000", "SN123", "SN321"};

public:
	bool check_pin_number(string pin_number);

};
