#include "Slav.h"
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
	exp = 0;
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
	exclusion=exclusions[rand()];
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

void timeSurvey(std::vector < double > tab, Rider riders[])
{	
	double times[4];
	for (int i = 0; i < 4; ++i)
	{
	printf("\n%12d %s\n", i+1, "Lap:");	
	for (int i = 0; i < 4; ++i)
	{
	bool ifFinish=true;
	int wayStart=0;
	double wayLenght=0;
	double difference=0;
	clock_t begin, end;
	time( &begin );
	tab.push_back( 0 );

	while(ifFinish)
	{
		usleep(TIME_INTERVAL);
		wayStart++;

		wayLenght += ((riders[i].luck())/100+riders[i].acceleration())*wayStart*wayStart/2;

		colorin(BRIGHT, i+1, wayLenght);
		
		if(wayLenght<4000)
			ifFinish=true;
		else
			ifFinish=false;
		
	}
	time( &end);
	
	difference = difftime( end, begin ) + riders[i].reaction();
	times[i]=tab[i];
	printf("\n\n%s %i %s %f\n\n", "Czas", i, "zawodnika:", difference);
	
	}
	tab.push_back( times[i] );
	}
}

void isExcluded(Rider riders[])
{
	for (int i = 0; i < 4; ++i)
	{
		if(riders[i].luck()<40)
			riders[i].arbiter();
		else
			printf("\n\n%d", 5);
	}
}

void classification(std::vector < double > tab, Rider riders[])
{
	double whoWin=0;
    	sort( tab.begin(), tab.end() );
    	for( int i = 0; i < tab.size(); i++ )
    	{
        		printf("\n%d %s\n", i,tab[i]);
    	}
    	whoWin=tab[0];
}