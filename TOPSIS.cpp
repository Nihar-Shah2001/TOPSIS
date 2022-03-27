// TOPSIS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
using namespace std;
int main()
{
    cout << "This is a code for TOPSIS. Before running this code you need to set two values in the code. This code then requires three files as input, Data.txt,Quality.txt, and Weights.txt with their values in it, and you need to configure the path of this three files(Please try specifying absolute path) in the code and also the Path of the output file Result.txt if needed. If not done so then the program will by default search only in the same directory and if not found will give an error as Error:file not found. Please see to it that the file path has been properly specified!.\n";
    cout << "If all of this has been done properly then a file will be created with the name Results.txt in the same directory or at the path specified or else you will recieve an error message below.\n";
    unsigned short int Criterias, Decision_makers, p;
    cout << "Please enter the number of Criteias: ";
    cin >> Criterias;
    cout << "Please Enter the Number of Decision_makers: ";
    cin >> Decision_makers;
    p = Decision_makers * Criterias;
    long double* Decision_Matrix = new long double[p];
    long double* root = new long double[Criterias];
    long double* max = new long double[Criterias];
    long double* min = new long double[Criterias];
    long double* ideal_solution = new long double[p];
    long double* negative_solution = new long double[p];
    long double* ideal = new long double[Decision_makers];
    long double* negative_sol = new long double[Decision_makers];
    long double* ideal_sol = new long double[Decision_makers];
    long double* weights = new long double[Criterias];
    unsigned short int* quality = new unsigned short int[Criterias];
    long double values, rms = 0, sum1 = 0, sum2 = 0, best_sol = 0;
    long double weight1;
    unsigned short int i = 0, j = 0, k = 0, quality1;
    ifstream indata, inquality, inweights;
    ofstream Results;
    indata.open("D://GitHub/TOPSIS/TOPSIS Code/Data.txt");
    inquality.open("D://GitHub/TOPSIS/TOPSIS Code/Quality.txt");
    inweights.open("D://GitHub/TOPSIS/TOPSIS Code/Weights.txt");
    indata >> values;
    inquality >> quality1;
    inweights >> weight1;
    for (i = 0; i < Criterias; i++)
    {
        for (j = 0; j < Decision_makers; j++)
        {
            Decision_Matrix[i * Decision_makers + j] = values;
            indata >> values;
        }
        weights[i] = weight1;
        inweights >> weight1;
        quality[i] = quality1;
        inquality >> quality1;

    }
    indata.close();
    inquality.close();
    inweights.close();
    for (i = 0; i < Criterias; i++)
    {
        rms = 0;
        for (j = 0; j < Decision_makers; j++)
        {
            rms += pow(Decision_Matrix[i * Decision_makers + j], 2);
        }
        rms = sqrt(rms);
        root[i] = rms;
    }
    for (i = 0; i < Criterias; i++)
    {
        for (j = 0; j < Decision_makers; j++)
        {
            Decision_Matrix[i * Decision_makers + j] = ((weights[i]) * (Decision_Matrix[i * Decision_makers + j])) / (root[i]);
        }
    }
    for (i = 0; i < Criterias; i++)
    {
        max[i] = Decision_Matrix[i * Decision_makers + 0];
        min[i] = Decision_Matrix[i * Decision_makers + 0];
        for (j = 0; j < Decision_makers; j++)
        {
            if (max[i] < Decision_Matrix[i * Decision_makers + j])
            {
                max[i] = Decision_Matrix[i * Decision_makers + j];
            }
            if (min[i] > Decision_Matrix[i * Decision_makers + j])
            {
                min[i] = Decision_Matrix[i * Decision_makers + j];
            }
        }
    }
    for (i = 0; i < Criterias; i++)
    {
        for (j = 0; j < Decision_makers; j++)
        {
            if (quality[i] == 1)
            {
                ideal_solution[i * Decision_makers + j] = pow((Decision_Matrix[i * Decision_makers + j] - max[i]), 2);
                negative_solution[i * Decision_makers + j] = pow(Decision_Matrix[i * Decision_makers + j] - min[i], 2);
            }
            else
            {
                ideal_solution[i * Decision_makers + j] = pow(Decision_Matrix[i * Decision_makers + j] - min[i], 2);
                negative_solution[i * Decision_makers + j] = pow(Decision_Matrix[i * Decision_makers + j] - max[i], 2);
            }
        }
    }
    for (i = 0; i < Decision_makers; i++)
    {
        sum1 = 0;
        sum2 = 0;
        for (j = 0; j < Criterias; j++)
        {
            sum1 += ideal_solution[j * Decision_makers + i];
            sum2 += negative_solution[j * Decision_makers + i];
        }
        sum1 = sqrt(sum1);
        sum2 = sqrt(sum2);
        ideal[i] = sum1;
        negative_sol[i] = sum2;
    }
    k = 0;
    for (i = 0; i < Decision_makers; i++)
    {
        if (best_sol < ((negative_sol[i]) / (ideal[i] + negative_sol[i])))
        {
            best_sol = (negative_sol[i] / (ideal[i] + negative_sol[i]));
            k = i + 1;
        }
        ideal_sol[i] = ((negative_sol[i]) / (ideal[i] + negative_sol[i]));
    }
    Results.open("D://GitHub/TOPSIS/TOPSIS Code/Results.txt");
    for (i = 0; i < Decision_makers; i++)
    {
        Results << "The Result for Criteria no. " << i + 1 << " is: ";
        Results << ideal_sol[i];
        Results << "\n";
    }
    Results << "The best solution is of Alternative no. ";
    Results << k;
    Results << " and the values is: ";
    Results << best_sol;
    Results.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
