/*
HEADER
PROGRAMMER: Arthur W. Aznive Jr.
DATE: 3/31/2019
DESCRIPTION: The Game of Googol. A C++ Solution by Arthur W. Aznive Jr. to test the probability that you can find the largest number before seeing the entire set.

GOALS: -Needs to be able to output results to a file and run continuously to get a large data set of results to see how often the computer is able to find the largest value.
	   -Random generator needs to be more "random", look into a better generator code and find ways to increase the randomness of the computer (I know very little about this currently). 
	   -To note, numbers top out around 32,000.

VERSION 1.01

UPDATES:
	4/8/2019, found error in Vector size going out of bounds, havent seen the error after some testing, needs to be fixed if patch wasnt enough. 

	3/12/2022, I am back to working on this sillyness.

*/

#include <iostream>
#include <fstream> //I want to create a results file that I can then analyze to determine how often this algorithm works.
#include <vector> //For storing all the random data.
#include <string> 
#include <time.h> //For seeding the srand.
#include <algorithm> //for sorting the vector dataSetVector
//#include <random/bernoulli_distribution.hpp>


using namespace std;

//Function Delcaration
void eulersChoice(vector<int> vect);

struct myClass { //Compare
	bool operator() (int i, int j) { return (i < j); }
}compareObject;

int main()
{

	//request data to create a set
	int userInput;
	bool run = true;
	bool _print = false;
	while (run)
	{
		cout << "What should our data set size be?\n";
		cout << "Insert size of data set: ";

		//get 
		do {
			cin >> userInput;
		} while (userInput <= 1);


		//seed the random
		srand((unsigned)time(NULL));

		//For holding the random values.
		vector<int> dataSetVector;
		
		//create a set of random seeded inputs.
		for (int i = 0; i < userInput; i++)
		{
			int value = rand() % 1000000000 + 1;
			//insert into vector.
			dataSetVector.push_back(value);
		}

		//cout << dataSetVector.size();

		cout << endl << "Vector filled! We can start testing.\n";

		//Make a choice based on the size of the 
		eulersChoice(dataSetVector);

		cout << endl;
		system("pause");
	}
	
	return 0;
}

//the algorithm 
void eulersChoice(vector<int> vect)
{
	int choiceSize; //This variable is for holding the number of elements we must traverse first to make the choice.


	//This is the number of numbers we need to look through to have the best chance of finding the largest value in the set.
	choiceSize = vect.size() / 2.7182818284590452353602874713527; //set size over e

	//print the size for the operator to see and check the computers output.
	cout << "The computer determined we should look at " << choiceSize << " elements before making a choice\n";

	int maxValue = vect[0]; //start with the first index as max so far, and go from there.
	//find the largest number in the first choiceSize index.
	for (int i = 0; i < choiceSize; i++)
	{
		if (vect[i] > maxValue)
		{
			maxValue = vect[i]; //if the currect element is bigger than the current maxValue, change the max value accordingly.
		}
	}

	cout << endl << "We are looking for anything bigger than: " << maxValue << endl;

	int j = choiceSize + 1; //start looking at the next element after the current element we stopped at just now.

	while (j < vect.size() && maxValue > vect[j - 1])
	{
		j++; //increment j until vect[j-1] is bigger than maxValue, or we hit the end of array
	}
	
	//When you leave the while loop you need to check the last value of the array. so we double check. (j <vect.size() will trigger the end of while before a check)
	if (vect[j - 1] > maxValue)
	{
		maxValue = vect[j - 1]; //if the last value is the largest in set, technically this means we failed to find the largest before flipping all the values, but thats for later polishing.

		
	}
	

	cout << "The maximum value I have calculated is: " << maxValue << endl;

	cout << '\n';


	//This prints out the UN-sorted array. 
	for (vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		cout << ' ' << *it;
	}
	cout << '\n';

	//we can sort the array and see where the value calculated sits in the array.
	sort(vect.begin(), vect.end(), compareObject);

	cout << endl << " - - - - - Sorted Data Set - - - - - \n";


	for (vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		cout << ' ' << *it;
	}
	cout << '\n';

	//by sorting the array i can get the true largest value, which is great for checking the result of my algorithm. DO NOT use the sorted vector for the algorithm the idea is for random sets.
	int _largest = vect[vect.size() - 1];
	cout << "The Largest value was: " << _largest << endl << "The algorithm found: " << maxValue << " to be the largest!" << endl; //maxValue doesnt care about the array being sorted so this is fine.

	cout << endl;

	//If Euler's Number Algorithm was wrong
	if (_largest != maxValue) 
	{
		cout << "Algorithm Failed!" << endl; //if we didnt find the biggest integer, failed.
		ofstream outputFile("AlgResult.txt");
		outputFile << "0";
	}
	else
	{
		//This might be (and probably is) not how I should be trying to analyze the results of hundreds of results for post processing? I'd love suggesions.
		cout << "Algorithm Success!" << endl;//and the opposite. 1 is a success.
		ofstream outputFile("AlgResult.txt");
		outputFile << "1";
	}

}

/*
PROOF

What should our data size be?
Insert data size: 182

Vector filled! We can start testing probability.
The computer determined we should look at 66 elements before making a choice

We are looking for anything bigger than: 31420
The maximum value I have calculated is: 32361

My Vector contains: 80 387 420 478 535 538 650 658 685 820 1455 1531 1765 2651 2727 2895 3525 3570 3615 3735 3815 3888 3930 3996 4080 4171 4476 4604 4745 4752 4909 4934 4987 5046 5210 5220 5481 5490 5818 6440 6944 7275 7319 7480 7522 7611 7746 8219 8290 8499 8990 9132 9191 9440 9531 9609 9813 9857 9909 10043 10259 10709 10941 10962 10995 11128 11280 11314 11472 11837 11859 11951 12033 12147 12587 12803 12971 12975 13425 13544 13752 13761 13990 14015 14071 14287 14307 14469 14476 14811 14859 15011 15103 15279 15435 15529 15690 15727 16024 16114 16435 16798 17689 17827 18025 18287 18539 18776 18963 19156 19321 19425 19437 20119 20483 20850 21089 21126 21261 21389 21495 21601 21665 21775 21948 21982 22585 22917 22931 23333 23369 23581 23827 24034 24927 25085 25255 25279 25303 25305 25511 25518 25616 25689 25913 26106 26194 26440 26609 26752 27181 27320 28551 28656 28674 28716 28736 28780 28903 29262 29481 29651 29694 29908 30074 30094 30099 30138 30200 30790 30819 31008 31099 31352 31420 31542 31762 32004 32266 32324 32361 32747
The Largest value was: 32747
The algorithm found: 32361 to be the largest!

Algorithm Failed!

Press any key to continue . . .



What should our data size be?
Insert data size: 5000

Vector filled! We can start testing probability.
The computer determined we should look at 1839 elements before making a choice

We are looking for anything bigger than: 32758
The maximum value I have calculated is: 32768

My Vector contains: 3 14 39 39 42 50 54 54 57 58 65 84 86 87 88 91 92 103 105 117 135 151 152 159 174 175 
176 183 185 196 202 203 205 211 235 236 239 242 243 245 253 254 255 256 259 262 269 277 283 296 317 320 332 
344 344 346 348 352 353 353 362 373 378 391 404 412 414 434 434 442 447 452 454 468 479 486 493 509 512 515 
523 523 526 526 534 538 544 548 551 559 565 574 604 610 613 617 618 620 621 624 627 628 633 640 655 666 673 
680 690 692 693 697 707 709 710 714 722 726 732 744 745 746 749 752 753 762 768 773 781 815 817 826 829 843 
849 855 861 863 863 867 876 877 878 883 902 906 908 913 918 923 927 939 943 949 962 970 971 972 988 1000 1017 
1022 1031 1035 1035 1038 1041 1058 1062 1064 1073 1089 1107 1143 1146 1159 1168 1175 1178 1183 1183 1190 1192 
1195 1200 1203 1206 1212 1220 1226 1240 1245 1249 1250 1256 1264 1265 1268 1284 1290 1298 1313 1316 1317 1322 
1327 1329 1331 1340 1346 1358 1363 1385 1411 1413 1419 1438 1441 1446 1451 1453 1460 1466 1469 1470 1480 1480 
1483 1491 1495 1499 1501 1502 1540 1546 1548 1562 1572 1575 1578 1599 1601 1602 1604 1614 1617 1628 1645 1647 
1659 1664 1673 1678 1679 1679 1684 1689 1695 1701 1702 1703 1709 1715 1724 1725 1728 1739 1744 1748 1753 1765 
1773 1792 1807 1817 1824 1827 1834 1838 1842 1852 1871 1883 1888 1890 1894 1894 1901 1916 1925 1929 1929 1930 
1934 1941 1950 1959 1970 1976 1982 1985 1986 1989 2003 2005 2005 2009 2023 2025 2037 2039 2041 2045 2066 2082 
2086 2086 2090 2091 2096 2100 2117 2118 2118 2129 2142 2143 2148 2151 2154 2154 2167 2174 2181 2198 2208 2214 
2224 2233 2251 2251 2261 2267 2273 2274 2280 2287 2295 2303 2306 2307 2308 2323 2351 2353 2364 2368 2370 2371 
2377 2379 2383 2392 2395 2395 2428 2430 2431 2432 2437 2444 2448 2455 2468 2473 2477 2480 2487 2490 2503 2513 
2516 2520 2522 2526 2533 2533 2534 2536 2551 2553 2555 2591 2600 2602 2606 2609 2609 2612 2629 2630 2636 2644... Carries on 

The Largest value was: 32768
The algorithm found: 32768 to be the largest!

Algorithm Success!

Press any key to continue . . .
*/