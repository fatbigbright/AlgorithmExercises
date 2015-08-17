#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 1
#define TRUE 0

const int MAX_CHAR = 128;
const int CITY_LEN = 20;
const int TEMP_LEN = 4;

struct Node {
	char city[CITY_LEN];
	int temp;
	struct Node* next;
};

//function definitions
int CheckLine(const char*, char*, int*);

int main(int argc, char* argv[])
{
	if(argc < 2) //at least one string parameter except program name itself
	{
		printf("Parameter missing....\n");
		return 1;
	}
	char buffer[MAX_CHAR];
	memset(buffer, '\0', MAX_CHAR);

	char* inputFileName = argv[1];

	FILE* inputFile = fopen(inputFileName, "r");

	if(inputFile == NULL)
	{
		printf("FileName: %s, but it does not exist.\n", inputFileName);
	}

	int lineNumber = 0;
	char tempCity[CITY_LEN];

	int tempTemp = 0;
	struct Node* header = NULL;
	struct Node* tail = NULL;
	struct Node* dummy = NULL;
	while(fgets(buffer, MAX_CHAR, inputFile) != NULL)
	{
		memset(tempCity, '\0', CITY_LEN);
		lineNumber++;
		if(CheckLine(buffer, tempCity, &tempTemp) == FALSE)
		{
			printf("Line %d is not in the correct format. Ignore...\n", lineNumber);
			continue;
		}

		dummy = (struct Node*)malloc(sizeof(struct Node));
		strcpy(dummy->city, tempCity);
		dummy->temp = tempTemp;
		dummy->next = NULL;

		if(header == NULL)
		{
			header = dummy;
			tail = dummy;
		}
		else
		{
			struct Node* flagPrev = NULL;
			for(struct Node* flag = header; flag != NULL; flag = flag->next)
			{
				if(flag->temp >= dummy->temp)
				{
					dummy->next = flag;
					if(flagPrev == NULL)
					{
						header = dummy;
					}
					else
					{
						flagPrev->next = dummy;
					}
					break;
				}
				flagPrev = flag;
				if(flag->next == NULL)
				{
					flag->next = dummy;
					tail = dummy;
					break;
				}
			}
		}
		dummy = NULL;
	}

	int middleIndex = lineNumber / 2;

	int count = 0;
	for(struct Node* flag = header; flag != NULL; flag = flag->next)
	{
		printf("City: %s -- Temperature: %d %s\n", flag->city, flag->temp, count == middleIndex ? "--Median--" : "");
		count++;
	}

	for(struct Node* flag = header; flag != NULL; )
	{
		header = flag->next;
		free(flag);
		flag = header;
	}
	header = NULL;
	tail = NULL;

	fclose(inputFile);

	return 0;
}

int CheckLine(const char* buffer, char* tempCity, int* tempTemp)
{
	char* leading = NULL;
	leading = strchr(buffer, ',');
	if(leading == NULL)
		return FALSE;

	strncpy(tempCity, buffer, leading - buffer);
	*tempTemp = atoi(leading + 1);

	return TRUE;
}
