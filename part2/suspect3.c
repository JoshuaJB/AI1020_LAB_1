struct point {
    float x, y, z;
};

int numbers[] = {10, 20, 30, 40, 50};

void process_data() {
    for(int i = 0; i < 5; i++) {
        numbers[i] = numbers[i] + 1;
    }
}
