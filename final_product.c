#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int k;

// Your pattern: 1's are spheres, 0's are empty
// Row 0: 0000100
// Row 1: 0000110  
// Row 2: 1111111
// Row 3: 1111111
// Row 4: 1110100
// Row 5: 0110000

int pattern[6][7] = {
    {0, 0, 0, 0, 1, 0, 0},  // Row 0
    {0, 0, 0, 0, 1, 1, 0},  // Row 1
    {1, 1, 1, 1, 1, 1, 1},  // Row 2
    {1, 1, 1, 1, 1, 1, 1},  // Row 3
    {1, 1, 1, 0, 1, 0, 0},  // Row 4
    {0, 1, 1, 0, 0, 0, 0}   // Row 5
};

float molecule_coords[50][3];  // More than enough space
int num_atoms = 0;

void get_user_name(char* first_name, char* last_name) {
    char* username = getlogin();
    if(username == NULL) {
        strcpy(first_name, "Student");
        strcpy(last_name, "");
        return;
    }
    
    // Find the dot separator
    char* dot_pos = strchr(username, '.');
    if(dot_pos == NULL) {
        // No dot found, use whole username as first name
        strcpy(first_name, username);
        strcpy(last_name, "");
        return;
    }
    
    // Copy first name (before dot)
    int first_len = dot_pos - username;
    strncpy(first_name, username, first_len);
    first_name[first_len] = '\0';
    
    // Copy last name (after dot, before @ if present)
    char* at_pos = strchr(dot_pos + 1, '@');
    if(at_pos != NULL) {
        int last_len = at_pos - (dot_pos + 1);
        strncpy(last_name, dot_pos + 1, last_len);
        last_name[last_len] = '\0';
    } else {
        strcpy(last_name, dot_pos + 1);
    }
    
    // Capitalize first letter of each name
    if(first_name[0] >= 'a' && first_name[0] <= 'z') {
        first_name[0] = first_name[0] - 'a' + 'A';
    }
    if(last_name[0] >= 'a' && last_name[0] <= 'z') {
        last_name[0] = last_name[0] - 'a' + 'A';
    }
}

void setup_pattern() {
    num_atoms = 0;
    float spacing = 3.5;  // Increased spacing between spheres
    
    // Convert pattern to 3D coordinates
    for(int row = 0; row < 6; row++) {
        for(int col = 0; col < 7; col++) {
            if(pattern[row][col] == 1) {
                // Place sphere at this grid position
                // Center the pattern: offset by half the dimensions
                float x = (col - 3.0) * spacing;  // Center horizontally 
                float y = (2.5 - row) * spacing;  // Center vertically, flip Y
                float z = 0.0;  // All in same plane initially
                
                // Rotate 45 degrees clockwise around Z-axis
                float angle = -45.0 * 3.14159 / 180.0;  // Convert to radians, negative for clockwise
                float cos_a = cos(angle);
                float sin_a = sin(angle);
                
                // Apply rotation
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

int main() {
    // Get user's first and last name
    char first_name[50], last_name[50];
    get_user_name(first_name, last_name);
    
    setup_pattern();
    
    float A = 0, B = 0, bounce_time = 0, theta, phi, z[3200];
    char b[3200];
    printf("\x1b[2J");
    
    for(;;) {
        memset(b, 32, 3200);
        memset(z, 0, 12800);
        
        // Render each atom in the pattern
        for(int atom = 0; atom < num_atoms; atom++) {
            float sphere_center_x = molecule_coords[atom][0];
            float sphere_center_y = molecule_coords[atom][1];
            float sphere_center_z = molecule_coords[atom][2];
            
            for(theta = 0; theta < 3.14159; theta += 0.15) {
                for(phi = 0; phi < 6.28318; phi += 0.15) {
                    
                    // Point on sphere surface
                    float sphere_x = sphere_center_x + 0.8 * sin(theta) * cos(phi);
                    float sphere_y = sphere_center_y + 0.8 * sin(theta) * sin(phi);
                    float sphere_z = sphere_center_z + 0.8 * cos(theta);
                    
                    // Rotation around Y-axis (A) and X-axis (B) - applied to entire object
                    float cos_A = cos(A), sin_A = sin(A);
                    float cos_B = cos(B), sin_B = sin(B);
                    
                    // Rotate around Y-axis
                    float x1 = sphere_x * cos_A - sphere_z * sin_A;
                    float z1 = sphere_x * sin_A + sphere_z * cos_A;
                    float y1 = sphere_y;
                    
                    // Rotate around X-axis
                    float x2 = x1;
                    float y2 = y1 * cos_B - z1 * sin_B;
                    float z2 = y1 * sin_B + z1 * cos_B;
                    
                    // Project to 2D screen with bouncing effect
                    float bounce_offset = 2 * sin(bounce_time);
                    float ooz = 1 / (z2 + 12);
                    int screen_x = 35 + 15 * x2 * ooz;  // Moved further left for better centering
                    int screen_y = 16 + 8 * y2 * ooz + bounce_offset;
                    
                    // Fixed bounds checking - check screen coordinates first
                    if(screen_y >= 0 && screen_y < 32 && screen_x >= 0 && screen_x < 100) {
                        int o = screen_x + 100 * screen_y;
                        
                        // Additional safety check for array bounds
                        if(o >= 0 && o < 3200 && ooz > z[o]) {
                            
                            // Simple lighting based on surface normal
                            float normal_x = (sphere_x - sphere_center_x) / 0.8;
                            float normal_y = (sphere_y - sphere_center_y) / 0.8;
                            float normal_z = (sphere_z - sphere_center_z) / 0.8;
                            
                            // Rotate normal same as surface
                            float nx1 = normal_x * cos_A - normal_z * sin_A;
                            float nz1 = normal_x * sin_A + normal_z * cos_A;
                            float ny1 = normal_y;
                            
                            float nx2 = nx1;
                            float ny2 = ny1 * cos_B - nz1 * sin_B;
                            float nz2 = ny1 * sin_B + nz1 * cos_B;
                            
                            // Light from upper-left-front
                            float light_x = 0.577, light_y = 0.577, light_z = -0.577;
                            int luminance = 8 * (nx2 * light_x + ny2 * light_y + nz2 * light_z);
                            if(luminance < 0) luminance = 0;
                            if(luminance > 11) luminance = 11;
                            
                            z[o] = ooz;
                            b[o] = ".,-~:;=!*#$@"[luminance];
                        }
                    }
                }
            }
        }
        
        printf("\x1b[H");
        for(k = 0; k < 3200; k++) {
            putchar(k % 100 ? b[k] : 10);
        }
        
        // Print congratulations message below the animation
        printf("\nCongratulations %s %s! You've completed Lab 1!\n", first_name, last_name);
        printf("Press control c to exit.\n");
        usleep(50000);
        A += 0.04;
        B += 0.02;
        bounce_time += 0.1;
    }
    return 0;
}
