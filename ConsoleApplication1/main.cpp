#include "Graph.h"

Graph buildRandomGraph(int v, float p)
{
	return Graph(v, p);
}

int main()
{
	int i;
	int graph;
	float count1 = 0, count2 = 0, count3 = 0;
	int v = 500;

	Graph G;

	/*define treshold values and set probabilities arrays according to each value,
	declaration of array to save each result of the test*/
	float Treshold1 = 0.0124292;
	float arrForTreshold1[10] = { 0.0017856, 0.0098756, 0.0106854, 0.0113598 ,0.011999, 0.0129639, 0.0139874, 0.0145687, 0.0169587, 0.0176548 };
	float probArrForTreshold1[10];

	float Treshold2 = 0.1576655;
	float arrForTreshold2[10] = { 0.0168713,0.0197854,0.0935874,0.0984678,0.1498745, 0.1954783, 0.2068457, 0.2563127, 0.3153799, 0.4066881	 };
	float probArrForTreshold2[10];

	float Treshold3 = 0.0124292;
	float arrForTreshold3[10] = { 0.0015874, 0.0093257, 0.0101587, 0.0116321,0.0119963, 0.0125321, 0.0134785, 0.0141598, 0.0164329, 0.0174982 };
	float probArrForTreshold3[10];

	for (i = 0; i < 10; i++)
	{
		for (graph = 0; graph < 500; graph++)
		{
			cout << "The " << graph + 1 << " graph for the " << i+1 << " iteration" << endl;

			G = buildRandomGraph(v, arrForTreshold1[i]);
			if (G.connectivity())
			{
				count1++;
			}
			else /*if the Graph is connected - it is not isolated*/
			{
				if (G.isIsolated())
				{
					count3++;
				}
			}

			G = buildRandomGraph(v, arrForTreshold2[i]);
			/* if the Graph is not connected, the diameter is infinite and therefore bigger than 2*/
			if (!G.connectivity())
			{
				continue;
			}

			if (G.diameter() <= 2)
			{
				count2++;
			}
		}

		probArrForTreshold1[i] = count1 / 500;
		count1 = 0;

		probArrForTreshold2[i] = count2 / 500;
		count2 = 0;

		probArrForTreshold3[i] = count3 / 500;
		count3 = 0;
	}

	/*create file for each test*/
	ofstream Cfile, Dfile, Ifile;
	Cfile.open("connectivityFile.csv");
	Dfile.open("diameterFile.csv");
	Ifile.open("isIsolatedFile.csv");

	/*load data to the connectivity file:*/
	Cfile << "Probability Values For Treshold1" << ",";
	for (i = 0; i < 10; i++)
	{
		Cfile << arrForTreshold1[i] << ",";
	}
	Cfile << endl;
	Cfile << "Connectivity results:" << ",";
	for (i = 0; i < 10; i++)
	{
		Cfile << probArrForTreshold1[i] << ",";
	}

	/*load data to the diameter file:*/
	Dfile << "Probability Values For Treshold2" << ",";
	for (i = 0; i < 10; i++)
	{
		Dfile << arrForTreshold2[i] << ",";
	}
	Dfile << endl;
	Dfile << "Diameter results:" << ",";
	for (i = 0; i < 10; i++)
	{
		Dfile << probArrForTreshold2[i] << ",";
	}

	/*load data to the is isoltated file:*/
	Ifile << "Probability Values For Treshold3" << ",";
	for (i = 0; i < 10; i++)
	{
		Ifile << arrForTreshold3[i] << ",";
	}
	Ifile << endl;
	Ifile << "Is isolated results:" << ",";
	for (i = 0; i < 10; i++)
	{
		Ifile << probArrForTreshold3[i] << ",";
	}
}

