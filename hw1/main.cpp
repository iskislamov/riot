#include "Binarization.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Error: Number of arguments" << endl;
    }

    Binarization object;
    size_t numberOfMegaPixels = object.readImage(argv[1], false);

    clock_t start_time =  clock();
    object.bradleyAlgo();
    clock_t end_time = clock();

    object.getResult(false);
    double total_time_sec = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    cout << "Time/pixels (Sec/MegaPixels): " << total_time_sec / numberOfMegaPixels << endl;
    return 0;
}
