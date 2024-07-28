
#include <iostream>
#include <string>
#include "fakebankAPI.h"
#include <vector>
using namespace std;


bool FakeBankAPI::check_pin_number(string pin_number) {
	for (int i = 0; i < available_pin_number.size(); i++) {
		if (pin_number == available_pin_number[i]) {
			return true;
		}
	}

	return false;
}