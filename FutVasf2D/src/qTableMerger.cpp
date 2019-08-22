#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    double newQTable[648][10];
    for (int i = 0; i < 648; i++)
    {
        newQTable[i][0] = 0;
        newQTable[i][1] = 0;
        newQTable[i][2] = 0;
        newQTable[i][3] = 0;
        newQTable[i][4] = 0;
        newQTable[i][5] = 0;
        newQTable[i][6] = 0;
        newQTable[i][7] = 0;
    }

    double qTable[5][648][10];
    ifstream qTableFileIn0("qTable2", ios::binary);
    qTableFileIn0.read((char *)&qTable[0], sizeof(qTable[0][0]) * 648);
    qTableFileIn0.close();
    ifstream qTableFileIn1("qTable3", ios::binary);
    qTableFileIn1.read((char *)&qTable[1], sizeof(qTable[1][0]) * 648);
    qTableFileIn1.close();
    ifstream qTableFileIn2("qTable4", ios::binary);
    qTableFileIn2.read((char *)&qTable[2], sizeof(qTable[2][0]) * 648);
    qTableFileIn2.close();
    ifstream qTableFileIn3("qTable5", ios::binary);
    qTableFileIn3.read((char *)&qTable[3], sizeof(qTable[3][0]) * 648);
    qTableFileIn3.close();
    ifstream qTableFileIn4("qTable6", ios::binary);
    qTableFileIn4.read((char *)&qTable[4], sizeof(qTable[4][0]) * 648);
    qTableFileIn4.close();

    for (int i = 0; i < 648; i++)
    {
        double counters[] = {qTable[0][i][7], qTable[1][i][7], qTable[2][i][7], qTable[3][i][7], qTable[4][i][7]};
        if (
            counters[0] >= counters[1] && counters[0] >= counters[2] && counters[0] >= counters[3] && counters[0] >= counters[4])
        {
            for (int j = 0; j < 8; j++)
                newQTable[i][j] = qTable[0][i][j];
        }
        else if (
            counters[1] >= counters[0] && counters[1] >= counters[2] && counters[1] >= counters[3] && counters[1] >= counters[4])
        {
            for (int j = 0; j < 8; j++)
                newQTable[i][j] = qTable[1][i][j];
        }
        else if (
            counters[2] >= counters[1] && counters[2] >= counters[0] && counters[2] >= counters[3] && counters[2] >= counters[4])
        {
            for (int j = 0; j < 8; j++)
                newQTable[i][j] = qTable[2][i][j];
        }
        else if (
            counters[3] >= counters[1] && counters[3] >= counters[2] && counters[3] >= counters[0] && counters[3] >= counters[4])
        {
            for (int j = 0; j < 8; j++)
                newQTable[i][j] = qTable[3][i][j];
        }
        else if (
            counters[4] >= counters[1] && counters[4] >= counters[2] && counters[4] >= counters[3] && counters[4] >= counters[0])
        {
            for (int j = 0; j < 8; j++)
                newQTable[i][j] = qTable[4][i][j];
        }
    }

    ofstream qTableFileOut("qTable", ios::binary);
    qTableFileOut.write((char *)&newQTable, sizeof(newQTable));
    qTableFileOut.close();
    return 0;
}
