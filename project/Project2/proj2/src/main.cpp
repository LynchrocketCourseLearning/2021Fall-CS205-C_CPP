
#include "../inc/IO.hpp"
#include "../inc/matrix.hpp"
#include <ctime>

using namespace std;

clock_t startTime, endTime;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int rowA, colA, rowB, colB;
    string ma ="../proj2/matrices/in/";
    ma += argv[1];
    string mb = "../proj2/matrices/in/";
    mb += argv[2];
    rowA = getRow(ma);
    colA = getCol(ma);
    rowB = getRow(mb);
    colB = getCol(mb);

    if (colA != rowB) {
        cout << "The matrix dimension of A and B is unmatched" << endl;
        cout << "The program is terminated." << endl;
        exit(EXIT_FAILURE);
    }

    string out = "../proj2/matrices/out/";
    string outdo = out + "do-";
    outdo += argv[3];

    doMatrix doma(rowA, colA, rowB, colB);

    //input time used by double
    startTime = clock();
    inputdo(doma.matrixA, doma.rowA, doma.colA, ma);
    inputdo(doma.matrixB, doma.rowB, doma.colB, mb);
    endTime = clock();
    cout << "IN-double: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
   
    //cal time used by double
    startTime = clock();
    doma.doMul(doma.matrixA, doma.rowA, doma.colA, doma.matrixB, doma.rowB, doma.colB, doma.matrixRes);
    endTime = clock();
    cout << "CAL-double: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    //output time used by double
    startTime = clock();
    outputdo(doma.matrixRes, doma.rowA, doma.colB, outdo);
    endTime = clock();
    cout << "OUT-double: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
   

    cout << " " << endl;


    string outfl = out + "fl-";
    outfl += argv[3];

    flMatrix fma(rowA, colA, rowB, colB);

    //input time used by float
    startTime = clock();
    inputfl(fma.matrixA, fma.rowA, fma.colA, ma);
    inputfl(fma.matrixB, fma.rowB, fma.colB, mb);
    endTime = clock();
    cout << "IN-float: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
   
    //cal time used by float
    startTime = clock();
    fma.flMul(fma.matrixA, fma.rowA, fma.colA, fma.matrixB, fma.rowB, fma.colB, fma.matrixRes);
    endTime = clock();
    cout << "CAL-float: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    //output time used by float
    startTime = clock();
    outputfl(fma.matrixRes, fma.rowA, fma.colB, outfl);
    endTime = clock();
    cout << "OUT-float: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
   
}

