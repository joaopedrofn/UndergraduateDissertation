#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    double qTable[1000][10];
    for (int i = 0; i < 1000; i++)
    {
        qTable[i][0] = 0;
        qTable[i][1] = 0;
        qTable[i][2] = 0;
        qTable[i][3] = 0;
        qTable[i][4] = 0;
        qTable[i][5] = 0;
        qTable[i][6] = 0;
        qTable[i][7] = 0;
        qTable[i][8] = 0;
        qTable[i][8] = 0;
    }

    ofstream qTableFileOut("qTable1", ios::binary);
    qTableFileOut.write((char *)&qTable, sizeof(qTable));
    qTableFileOut.close();

    ofstream qTableFileOut2("qTable2", ios::binary);
    qTableFileOut2.write((char *)&qTable, sizeof(qTable));
    qTableFileOut2.close();
    ofstream qTableFileOut3("qTable3", ios::binary);
    qTableFileOut3.write((char *)&qTable, sizeof(qTable));
    qTableFileOut3.close();
    ofstream qTableFileOut4("qTable4", ios::binary);
    qTableFileOut4.write((char *)&qTable, sizeof(qTable));
    qTableFileOut4.close();
    ofstream qTableFileOut5("qTable5", ios::binary);
    qTableFileOut5.write((char *)&qTable, sizeof(qTable));
    qTableFileOut5.close();
    ofstream qTableFileOut6("qTable6", ios::binary);
    qTableFileOut6.write((char *)&qTable, sizeof(qTable));
    qTableFileOut6.close();
    ofstream qTableFileOut7("qTable7", ios::binary);
    qTableFileOut7.write((char *)&qTable, sizeof(qTable));
    qTableFileOut7.close();
    ofstream qTableFileOut8("qTable8", ios::binary);
    qTableFileOut8.write((char *)&qTable, sizeof(qTable));
    qTableFileOut8.close();
    ofstream qTableFileOut9("qTable9", ios::binary);
    qTableFileOut9.write((char *)&qTable, sizeof(qTable));
    qTableFileOut9.close();
    ofstream qTableFileOut10("qTable10", ios::binary);
    qTableFileOut10.write((char *)&qTable, sizeof(qTable));
    qTableFileOut10.close();
    ofstream qTableFileOut11("qTable11", ios::binary);
    qTableFileOut11.write((char *)&qTable, sizeof(qTable));
    qTableFileOut11.close();

    ifstream qTableFileIn("qTable2", ios::binary);
    double newQTable[648][10];

    // cout << qTableFileIn.good();

    // cout << sizeof(newQTable);
    qTableFileIn.read((char *)&newQTable, sizeof(newQTable[0]) * 648);
    // cout << newQTable[645][0] << ' ' << newQTable[645][1] << ' '  << newQTable[645][2] << ' '  << newQTable[645][3] << ' '  << newQTable[645][4] << ' '  << newQTable[645][5] << ' '  << newQTable[645][6] << '\n';
    for (int i = 0; i < 648; i++)
    {
        cout << newQTable[i][0] << ' ' << newQTable[i][1] << ' ' << newQTable[i][2] << ' ' << newQTable[i][3] << ' ' << newQTable[i][4] << ' ' << newQTable[i][5] << ' ' << newQTable[i][6] << ' ' << newQTable[i][7] << ' ' << newQTable[i][8] << ' ' << newQTable[i][9] << '\n';
    }
    return 0;
}
