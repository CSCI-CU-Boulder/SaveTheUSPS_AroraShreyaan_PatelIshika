#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "hash.hpp"
using namespace std;
using namespace std::chrono;




int main(int argc,char* argv[])
{

    int lastVal = 99;
    int insertCol[400];
    int searchCol[400];
    float insert[400];
    float search[400];
    int testData[40000];
    string filename = argv[1];
    HashTable HT(40000);
    string scenario = "Chaining | Hash";

 



    // import all of the test data
    string line = "";
    ifstream infile;
    infile.open(filename);

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
	int index = 0; // 0 to 400
	int countInsert = 0; //0 to 40,000 for each ID total
	int insertVal;
	while(index < 400)
	{
		double insertExecution=0; //total time for excecutation for insert (or not insert if duplicate) of 100 IDs
		
		for(int i = 0; i < 100; i++)
		{
    		insertVal = testData[countInsert];
			auto start = chrono::steady_clock::now();
			if(HT.searchItem(insertVal) != NULL) // if the value is found in the list already
			{
				auto end = chrono::steady_clock::now();
				insertExecution = insertExecution + (double)chrono::duration_cast<chrono::nanoseconds>(end-start).count();
				countInsert++;
			}
			else // insert node at beginning
			{
				HT.insertItem(insertVal); //always insert at the beginning to reduce insert time
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
			HT.searchItem(testVal);
			auto end1 = chrono::steady_clock::now();
			searchExecution = searchExecution + (double)chrono::duration_cast<chrono::nanoseconds>(end1-start1).count();
		}
		search[index] = searchExecution/(double)100;
		lastVal = lastVal + 100; // incremented to increase the range each time 
        insertCol[index] = HT.getNumOfInsertCol();
        searchCol[index] = HT.getNumOfSearchCol();
		index++;
	}

    // -------------------------produce CSV's with results-----------------------------

    /**
     * produce CSV of Insertion times
     */
    string resultsInsertionFile  = scenario + "InsertionTimes | " + filename;
    
    ofstream outfileInsert;
    outfileInsert.open(resultsInsertionFile);
    for(int j = 0; j < 400; j++) 
    {
        outfileInsert << insert[j] << endl;
    }
    outfileInsert.close();
    /**
     * produce CSV of Search/Location times
     */
    string resultsSearchFile = scenario + "SearchTimes | " + filename;

    ofstream outfileSearch;
    outfileSearch.open(resultsSearchFile);
    for(int j = 0; j < 400; j++) 
    {
        outfileSearch << search[j] << endl;
    }
    outfileSearch.close();

    
    /**
     * produce CSV of collisions times
     */
    string resultsCollisionFile = scenario + "Collisions | " + filename;

    ofstream outfileCollisions;
    outfileCollisions.open(resultsCollisionFile);
    outfileCollisions << "insertCollisions, searchCollisions" << endl;
    for(int j = 0; j < 400; j++) 
    {
        outfileCollisions << insertCol[j] << "," << searchCol[j] << endl;
    }
    outfileCollisions.close();

    return 0;
}