//api.h - header file for the interface to the hauler



#include "loader.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

vector<string> get_input(void);

void perform_action(Loader, vector<string>);

void print_help(void);
