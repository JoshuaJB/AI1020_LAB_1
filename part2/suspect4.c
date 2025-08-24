char letters[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

void sort_array() {
    int temp;
    for(int i = 0; i < 9; i++) {
        temp = letters[i];
        letters[i] = letters[i+1];
        letters[i+1] = temp;
    }
}
