#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int k;
float molecule_coords[50][3];  // More than enough space
int num_atoms = 0;

void get_user_name(char* first_name, char* last_name);
void setup_pattern();
