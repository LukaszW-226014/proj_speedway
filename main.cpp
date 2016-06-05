#include "Speedway.h"
#include "colors.h"
#include <stdio.h>
#include <time.h>
#include <vector>


int main(int argc, char const *argv[])
{
	std::vector < double > timeSurveys;
	srand(argc == 2 
		? atoi(argv[1]) 
		: time(NULL));
	//srand(time(NULL));
	
	Rider riders[4];
	
	textcolor(BRIGHT, WHITE);

	for (int i = 0; i < 4; ++i)
	{
		textcolor(BRIGHT, i+1);
		printf("%s\n", riders[i].description().c_str());
	}
	start();
	timeSurvey(timeSurveys, riders);
	classification(timeSurveys, riders);
	textcolor(RESET, WHITE);
}