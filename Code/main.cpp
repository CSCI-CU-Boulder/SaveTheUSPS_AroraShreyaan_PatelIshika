#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"

using namespace std;

int main(int argc,char* argv[])
{
	int testData[40000];
	float insert[400];
	float search[400];
	int lastVal = 99;
	LinkedList ll;
	
// import all of the test data
	string line;
    ifstream infile;
    infile.open(argv[1]);

    if(infile.fail())
	{
        cout << "Failed to open the file." << endl;
    }
    else
	{
		int indexAllData = 0;
        while(getline(infile,line,','))
		{
			testData[indexAllData]=stoi(line);
			indexAllData++;
		} 
    }

	// calcuate run time
	int index= 0; // 0 to 400
	int countInsert = 0; //0 to 40,000 for each ID total
	int insertVal;
	while(index < 400)
	{
		double insertExecution=0; //total time for excecutation for insert (or not insert if duplicate) of 100 IDs
		
		for(int i = 0; i < 100; i++)
		{
    		insertVal = testData[countInsert];
			auto start = chrono::steady_clock::now();
			if(ll.searchList(insertVal) != NULL) // if the value is found in the list already
			{
				auto end = chrono::steady_clock::now();
				insertExecution = insertExecution + (double)chrono::duration_cast<chrono::nanoseconds>(end-start).count();
				countInsert++;
			}
			else // insert node at beginning
			{
				ll.insert(NULL,insertVal); //always insert at the beginning to reduce insert time
				auto end = chrono::steady_clock::now();
				insertExecution = insertExecution + (double)chrono::duration_cast<chrono::nanoseconds>(end-start).count();
				countInsert++;
			}
		}
		insert[index] = insertExecution/(double)100;

		double searchExecution = 0; //total elapsed time for excecutation to search all 100 IDs
		srand(time(NULL)); //seeding the random val function 
		for(int i = 0; i<100; i++) // search or 100 valuses
		{
			int randomVal = rand()%lastVal;
			int testVal = testData[randomVal];
			auto start1 = chrono::steady_clock::now();
			ll.searchList(testVal);
			auto end1 = chrono::steady_clock::now();
			searchExecution = searchExecution + (double)chrono::duration_cast<chrono::nanoseconds>(end1-start1).count();
		}
		search[index] = searchExecution/(double)100;
		lastVal = lastVal + 100; // incremented to increase the range each time 
		index++;
	}

	ofstream myFile;
	myFile.open("insertLLB.csv");
		for(int i = 0; i<400; i++)
		{
			myFile<< insert[i]<< endl;		
		}
		myFile.close();

	ofstream myFile2;
	myFile2.open("searchLLB.csv");
	for(int i = 0; i<400; i++)
	{
		myFile2<< search[i]<< endl;		
	}
	myFile2.close();
}

