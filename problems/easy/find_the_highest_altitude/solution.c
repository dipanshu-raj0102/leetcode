int largestAltitude(int* gain, int gainSize) {
    int current_altitude = 0;
    int max_altitude = 0;
    
    for (int i = 0; i < gainSize; i++) {
        current_altitude += gain[i];
        if (current_altitude > max_altitude) {
            max_altitude = current_altitude;
        }
    }
    
    return max_altitude;
}