//
// Created by saeed on 12/26/19.
//

#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Requires number of list !!" << endl;
        cout << "Requires maximum value can be generate !!" << endl;
        cout<< "Requires ouput file path and name !!"<<endl;
        return 0;
    }

    //random list size:
    long randomListSize=atol(argv[1]);

    // maximum value can be generate:
    long  maximum=atol(argv[2]);


    // random list file name:
    string fileName=argv[3];

    ofstream randomFile;
    randomFile.open (fileName, ios::out | ios::trunc );


    // Make sure different runs of the same experiment reads different objects.
    long time_ui = long(time(NULL));
    srand(time_ui);

    for (long i = 0; i < randomListSize; ++i) {
        long randvalue = rand() % maximum;
        randomFile<<randvalue<<"\n";
    }
    randomFile.close();

    return 0;

}
