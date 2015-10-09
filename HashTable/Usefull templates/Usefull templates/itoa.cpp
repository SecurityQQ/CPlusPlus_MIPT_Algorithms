
char* itoa(int value) {
    char* tmp = (char* ) malloc(20 * sizeof(char));
    int i = 0;
    
    while( value > 0) {
        tmp[i++] = (value % 10) + '0';
        value /= 10;
    }
    
    char* itoa = (char* ) malloc(i * sizeof(char));
    for(int j = 0; j < i; ++j) {
        itoa[j] = tmp[i - j - 1];
    }
    
    free(tmp);
    return itoa;
}
