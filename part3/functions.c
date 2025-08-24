void get_user_name(char* first_name, char* last_name) {
    char* username = getlogin();
    if(username == NULL) {
        strcpy(first_name, "Student");
        strcpy(last_name, "");
        return;
    }
    
    char* dot_pos = strchr(username, '.');
    if(dot_pos == NULL) {
        strcpy(first_name, username);
        strcpy(last_name, "");
        return;
    }
    
    int first_len = dot_pos - username;
    strncpy(first_name, username, first_len);
    first_name[first_len] = '\0';
    
    char* at_pos = strchr(dot_pos + 1, '@');
    if(at_pos != NULL) {
        int last_len = at_pos - (dot_pos + 1);
        strncpy(last_name, dot_pos + 1, last_len);
        last_name[last_len] = '\0';
    } else {
        strcpy(last_name, dot_pos + 1);
    }
    
    if(first_name[0] >= 'a' && first_name[0] <= 'z') {
        first_name[0] = first_name[0] - 'a' + 'A';
    }
    if(last_name[0] >= 'a' && last_name[0] <= 'z') {
        last_name[0] = last_name[0] - 'a' + 'A';
    }
}

void setup_pattern() {
    num_atoms = 0;
    float spacing = 3.5;
    
    for(int row = 0; row < 6; row++) {
        for(int col = 0; col < 7; col++) {
            if(pattern[row][col] == 1) {
                float x = (col - 3.0) * spacing;
                float y = (2.5 - row) * spacing;
                float z = 0.0;
                
                float angle = -45.0 * 3.14159 / 180.0;
                float cos_a = cos(angle);
                float sin_a = sin(angle);
                
                float rotated_x = x * cos_a - y * sin_a;
                float rotated_y = x * sin_a + y * cos_a;
                float rotated_z = z;
                
                molecule_coords[num_atoms][0] = rotated_x;
                molecule_coords[num_atoms][1] = rotated_y;
                molecule_coords[num_atoms][2] = rotated_z;
                num_atoms++;
            }
        }
    }
}
