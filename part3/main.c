int main() {
    char first_name[50], last_name[50];
    get_user_name(first_name, last_name);
    
    setup_pattern();
    
    float A = 0, B = 0, bounce_time = 0, theta, phi, z[3200];
    char b[3200];
    printf("\x1b[2J");
    
    for(;;) {
        memset(b, 32, 3200);
        memset(z, 0, 12800);
        
        for(int atom = 0; atom < num_atoms; atom++) {
            float sphere_center_x = molecule_coords[atom][0];
            float sphere_center_y = molecule_coords[atom][1];
            float sphere_center_z = molecule_coords[atom][2];
            
            for(theta = 0; theta < 3.14159; theta += 0.15) {
                for(phi = 0; phi < 6.28318; phi += 0.15) {
                    
                    float sphere_x = sphere_center_x + 0.8 * sin(theta) * cos(phi);
                    float sphere_y = sphere_center_y + 0.8 * sin(theta) * sin(phi);
                    float sphere_z = sphere_center_z + 0.8 * cos(theta);
                    
                    float cos_A = cos(A), sin_A = sin(A);
                    float cos_B = cos(B), sin_B = sin(B);
                    
                    float x1 = sphere_x * cos_A - sphere_z * sin_A;
                    float z1 = sphere_x * sin_A + sphere_z * cos_A;
                    float y1 = sphere_y;
                    
                    float x2 = x1;
                    float y2 = y1 * cos_B - z1 * sin_B;
                    float z2 = y1 * sin_B + z1 * cos_B;
                    
                    float bounce_offset = 2 * sin(bounce_time);
                    float ooz = 1 / (z2 + 12);
                    int screen_x = 35 + 15 * x2 * ooz;
                    int screen_y = 16 + 8 * y2 * ooz + bounce_offset;
                    
                    if(screen_y >= 0 && screen_y < 32 && screen_x >= 0 && screen_x < 80) {
                        int o = screen_x + 80 * screen_y;
                        
                        if(o >= 0 && o < 3200 && ooz > z[o]) {
                            
                            float normal_x = (sphere_x - sphere_center_x) / 0.8;
                            float normal_y = (sphere_y - sphere_center_y) / 0.8;
                            float normal_z = (sphere_z - sphere_center_z) / 0.8;
                            
                            float nx1 = normal_x * cos_A - normal_z * sin_A;
                            float nz1 = normal_x * sin_A + normal_z * cos_A;
                            float ny1 = normal_y;
                            
                            float nx2 = nx1;
                            float ny2 = ny1 * cos_B - nz1 * sin_B;
                            float nz2 = ny1 * sin_B + nz1 * cos_B;
                            
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
        for(k = 0; k < 2560; k++) {
            putchar(k % 80 ? b[k] : 10);
        }
        
        printf("\nCongratulations %s %s! You've completed Lab 1!\n", first_name, last_name);
        printf("Your submission ID is: \"%X\". ", *(int*)first_name);
        printf("Press Control+C to exit.\n");
        usleep(50000);
        A += 0.04;
        B += 0.02;
        bounce_time += 0.1;
    }
    return 0;
}
