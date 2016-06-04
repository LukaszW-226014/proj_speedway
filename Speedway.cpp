#include "Speedway.h"
#include "colors.h"
#include <stdlib.h>
#include <stdio.h>
#include <iterator>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <algorithm>

vector <string> Rider::names;
vector <string> Rider::exclusions;

void Rider::init()
{
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

void Rider::initArbiter()
{
	ifstream file("exclusions.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(exclusions));
	file.close();
}

int randomValue()
{
	return 10 + rand() % 90;	
}

Rider::Rider()
{
	static int amountOfNames = (init(), names.size());
	_name = names[rand() % amountOfNames];
	_reaction = randomValue();
	_acceleration = randomValue();
	_luck = randomValue();
}

string Rider::description()
{
	return _name + "\n\tReaction:" + to_string(_reaction) + 
		" Acceleration:" + to_string(_acceleration) + 
		" Luck:" + to_string(_luck); 
}

void Rider::arbiter()
{
	
	static int amountOfExclusions = (initArbiter(), exclusions.size());
	string exclusion;
	exclusion=exclusions[rand()%amountOfExclusions];
	printf("%s", exclusion.c_str());
}

double Rider::way(int value)
{
	return _reaction+(_acceleration*value*value/2);
}

void start()
{
	for (int i = 3; i >0; i--)
	{
		usleep(TIME_INTERVAL);
		printf("\n%14d\n", i);
	}
	printf("\n%18s\n", "START!!");
}

void textcolor(int attr, int fg) 
{
        char command[13];

     
        //sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40); //Tlo
         sprintf(command, "%c[%d;%dm", 0x1B, attr, fg + 30);
        printf("%s", command);
}

void colorin(int attr, int fg, double in)
{
	textcolor(attr, fg);
		printf("\n%20f", in);	
}

void timeSurvey(std::vector < double > &tab, Rider riders[])
{	
	double times[4];
	double timesLap[16];
	double difference[16];
	int k=0;
	for (int i = 0; i < 4; i++)
	{
	textcolor(BRIGHT, WHITE);
	printf("\n%s%9d %s\n",":::::::::::::::::::", i+1, "Lap:");	
	for (int j = 0; j< 4; j++)
	{
	bool ifFinish=true;
	int wayStart=0;
	double wayLenght=0;
	clock_t begin, end;
	time( &begin );
	textcolor(BRIGHT, j+1);
	printf("%s\n", riders[j].name().c_str());

	while(ifFinish)
	{
		usleep(TIME_INTERVAL);
		wayStart++;

		
			wayLenght += ((riders[j].luck())/100+riders[j].acceleration()+randomValue()/100)*wayStart*wayStart/2;

		//colorin(BRIGHT, j+1, wayLenght);
		printf("%20s\n", "*");	
		
		if(wayLenght<4000)
			ifFinish=true;
		else
			ifFinish=false;
		
	}
	time( &end);
	
	difference[k] = difftime( end, begin ) + riders[j].reaction()/1000;
	//timesLap[j+4]=difference
	//times[j]+=difference;
	printf("\n\n%s %f\n\n", "Time: ", difference[k]);
	k++;
	}
	}
	for (int i = 0; i < 4; i++)
	{
	times[i]+=difference[i]+difference[i+4]+difference[i+8]+difference[i+12];
	tab.push_back( times[i] );
	}
	textcolor(BRIGHT, WHITE);
	printf("%s\n%19s\n", "::::::::::::::::::::::::::::::::::", "META!");
}

void classification(std::vector < double > &tab, Rider riders[])
{
	std::vector < double > tabCopy;
	tabCopy=tab;
	int whoWin[4];
    	sort( tabCopy.begin(), tabCopy.end() );
    	for( int i = 0; i < 4; i++ )
    	{
        		//printf("\n%d %f\n", i, tabCopy[i]);
        		//printf("\n%d %f\n", i, tab[i]);
        		if (tabCopy[0]==tab[i])
        		{
        			whoWin[0]=i;
        		}
        		if (tabCopy[1]==tab[i])
        		{
        			whoWin[1]=i;
        		}
        		if (tabCopy[2]==tab[i])
        		{
        			whoWin[2]=i;
        		}
        		if (tabCopy[3]==tab[i])
        		{
        			whoWin[3]=i;
        		}
    	}
    	for (int i = 0; i < 4; i++)
    	{
    		printf("\n\n%d %s %s %f\n", i+1, riders[whoWin[i]].name().c_str(), "Time:", tabCopy[i]);
    	}

    	printf("\n\n%s %s %s %f\n", "WINNER:", riders[whoWin[0]].name().c_str(), "Time:", tabCopy[0]);
}

/*if(riders[j].luck()<40)
		{
			printf("%s", "EXCLUSED!!: " );
			riders[j].arbiter();
			ifFinish=false;
		}*/