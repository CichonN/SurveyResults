// ------------------------------------------------------------------------------------------
// Name: Neina Cichon
// Class: Survey Results
// Date: 2020-12-08
// ------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <stdbool.h> 

#pragma warning(disable : 4996);

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const int intARRAY_SIZE = 100;
#define true 1
#define false 0

// --------------------------------------------------------------------------------
// User Defined Types (UDTs)
// --------------------------------------------------------------------------------
//typedef int boolean;

typedef struct
{
	char strDate[50];
	char strState[50];
	char strCounty[50];
	char strRace[50];
	int intHouseholdCount;
	float sngIncome;
} udtSurveyData;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
char Options(udtSurveyData audtSurveyDataList[]);
int TotalHouseholds(udtSurveyData audtSurveyDataList[]);
int TotalHouseholdsCounty(udtSurveyData audtSurveyDataList[]);
int TotalHouseholdsRace(udtSurveyData audtSurveyDataList[]);
float AverageIncome(udtSurveyData audtSurveyDataList[], int TotalHouseholds);
float AverageIncomeCounty(udtSurveyData audtSurveyDataList[]);
float AverageIncomeRace(udtSurveyData audtSurveyDataList[]);
float PercentageBelowPoverty(udtSurveyData audtSurveyDataList[], int TotalHouseholds);
float PercentageBelowPovertyCounty(udtSurveyData audtSurveyDataList[]);
float PercentageBelowPovertyRace(udtSurveyData audtSurveyDataList[]);
boolean CheckBelowPoverty(udtSurveyData audtSurveyDataList);

void InitializeSurveyList(udtSurveyData audtSurveyDataList[]);
void InitializeSurvey(udtSurveyData* pudtSurveyData);

void PopulateSurveyList(udtSurveyData audtSurveyDataList[]);
int OpenInputFile(char strFileName[], FILE** ppfilInput);
void AddSurveyDataToArray(char strData[], udtSurveyData* pudtSurveyData);

void GetNextField(char strNextField[], char strSource[], char chrDelimiter);

void PrintSurveyData(int intIndex, udtSurveyData udtSurveyData);
void PrintSurveyList(udtSurveyData audtSurveyList[]);

void StringCopy(char strDestination[], char strSource[]);
int StringLength(char strSource[]);
void AppendString(char strDestination[], char strSource[]);
int FindLetterIndex(char strSource[], char chrLetterToFind);
void Trim(char strSource[]);
boolean IsWhiteSpace(char chrLetterToCheck);
int CountWords(char strSource[]);

void ProgramEnded();
void empty_stdin(void);

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts.
// --------------------------------------------------------------------------------
void main()
{
	char chrSelect = '0';
	//int intHouseholdCount = 0;

	udtSurveyData audtSurveyDataList[100];
	InitializeSurveyList(audtSurveyDataList);
	PopulateSurveyList(audtSurveyDataList);

	chrSelect = Options(audtSurveyDataList);

	system("pause");
}

// --------------------------------------------------------------------------------
// Name: Options
// Abstract: Show Options to user and allow selection
// --------------------------------------------------------------------------------
char Options(udtSurveyData audtSurveyDataList[])
{
	char chrSelect = 'x';
	int intHouseholdCount = 0;

		printf("Select one of the following:\n");
		printf("\tA. Total Households Surveyed\n");
		printf("\tB. Total Households Surveyed per County\n");
		printf("\tC. Total Households Surveyed per Race\n");
		printf("\tD. Average Household Income\n");
		printf("\tE. Average Household Income by county and state\n");
		printf("\tF. Average Household Income by race\n");
		printf("\tG. Percentage below Poverty\n");
		printf("\tH. Percentage below Poverty by county and state\n");
		printf("\tI. Percentage below Poverty by race\n\n");
		printf("\tJ. Exit Program\n\n");

	do
	{
		do
		{
			scanf("%c", &chrSelect);
			empty_stdin();
			if ((chrSelect < 'a' || chrSelect > 'j') && (chrSelect < 'A' || chrSelect > 'J'))
			{
				printf("Invalid input. Please try again.\n");
			}
		} while ((chrSelect < 'a' || chrSelect > 'j') && (chrSelect < 'A' || chrSelect > 'J'));

		//Get Count of Households Surveyed
		intHouseholdCount = TotalHouseholds(audtSurveyDataList);

		if (chrSelect >= 'a' && chrSelect <= 'z')
		{
			chrSelect -= 32;
		}

		//Display user selection
		switch (chrSelect)
		{
		case 'A': 
			printf("--------------------------------------------------------------\n");
			printf("Total Households Surveyed:\t%d\n", intHouseholdCount);
			printf("--------------------------------------------------------------\n");
			break;
		case 'B': TotalHouseholdsCounty(audtSurveyDataList);
			break;
		case 'C': TotalHouseholdsRace(audtSurveyDataList);
			break;
		case 'D': AverageIncome(audtSurveyDataList, intHouseholdCount);
			break;
		case 'E': AverageIncomeCounty(audtSurveyDataList, intHouseholdCount);
			break;
		case 'F': AverageIncomeRace(audtSurveyDataList);
			break;
		case 'G': PercentageBelowPoverty(audtSurveyDataList, intHouseholdCount);
			break;
		case 'H': PercentageBelowPovertyCounty(audtSurveyDataList);
			break;
		case 'I': PercentageBelowPovertyRace(audtSurveyDataList);
			break;
		case 'J': ProgramEnded();
			break;
		}
	} while (chrSelect != 'X');
	return chrSelect;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholds
// Abstract: Sum of All Households
// --------------------------------------------------------------------------------
int TotalHouseholds(udtSurveyData audtSurveyDataList[])
{
	int intHouseholdCount = 0;
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			intHouseholdCount += 1;
		}
	}
	
	return intHouseholdCount;
}

// --------------------------------------------------------------------------------
// Name: TotalHouseholdsCounty
// Abstract: Sum of Households by county
// --------------------------------------------------------------------------------
int TotalHouseholdsCounty(udtSurveyData audtSurveyDataList[])
{
	int intHouseholdCountyCount = 0;
	int intOhioCount = 0;
	int intHamiltoncount = 0;
	int intButlerCount = 0;
	int intKentuckyCount = 0;
	int intBooneCount = 0;
	int intKentonCount = 0;
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strState, "Ohio") == 0)
			{
				intOhioCount += 1;
				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Hamilton") == 0)
				{
					intHamiltoncount += 1;
				}
				else
				{
					intButlerCount += 1;
				}
			}
			else
			{
				intKentuckyCount += 1;
				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Boone") == 0)
				{
					intBooneCount += 1;
				}
				else
				{
					intKentonCount += 1;
				}
			}
		}
	}

	printf("--------------------------------------------------------------\n");
	printf("Total Households Surveyed (By County)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tOhio:\t\t\t%d\n", intOhioCount);
	printf("\t\tHamilton:\t%d\n", intHamiltoncount);
	printf("\t\tButler:\t\t%d\n", intButlerCount);
	printf("\tKentucky:\t\t%d\n", intKentuckyCount);
	printf("\t\tBoone:\t\t%d\n", intBooneCount);
	printf("\t\tKenton:\t\t%d\n", intKentonCount);

	return intHouseholdCountyCount;
}


// --------------------------------------------------------------------------------
// Name: TotalHouseholdsRace
// Abstract: Sum of Households by race
// --------------------------------------------------------------------------------
int TotalHouseholdsRace(udtSurveyData audtSurveyDataList[])
{
	int intCaucasianCount = 0;
	int intBlackcount = 0;
	int intHispanicCount = 0;
	int intAsianCount = 0;
	int intOtherCount = 0;

	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{

		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strRace, "Caucasian") == 0)
			{
				intCaucasianCount += 1;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "African American") == 0)
			{
				intBlackcount += 1;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Hispanic") == 0)
			{
				intHispanicCount += 1;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Asian") == 0)
			{
				intAsianCount += 1;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Other") == 0)
			{
				intOtherCount += 1;
			}	
		}
	}
	printf("--------------------------------------------------------------\n");
	printf("Total Households Surveyed (By Race)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tCaucasian:\t\t%d\n", intCaucasianCount);
	printf("\tAfrican American:\t%d\n", intBlackcount);
	printf("\tHispanic:\t\t%d\n", intHispanicCount);
	printf("\tAsian:\t\t\t%d\n", intAsianCount);
	printf("\tOther:\t\t\t%d\n", intOtherCount);
}


// --------------------------------------------------------------------------------
// Name: AverageIncome
// Abstract: Average Income of All Households
// --------------------------------------------------------------------------------
float AverageIncome(udtSurveyData audtSurveyDataList[], int TotalHouseholds)
{
	int intIndex = 0;
	float TotalIncome = 0.0;
	float AverageIncome = 0.0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			TotalIncome += audtSurveyDataList[intIndex].sngIncome;
		}
	}

	AverageIncome = TotalIncome / TotalHouseholds;
	printf("--------------------------------------------------------------\n");
	printf("Total Average Income:\t\t$%.2f\n", AverageIncome);
	printf("--------------------------------------------------------------\n");
}


// --------------------------------------------------------------------------------
// Name: AverageIncomeCounty
// Abstract: Average Income of Households by county
// --------------------------------------------------------------------------------
float AverageIncomeCounty(udtSurveyData audtSurveyDataList[])
{
	int intHouseholdCountyCount = 0;
	int intOhioCount = 0;
	int intHamiltoncount = 0;
	int intButlerCount = 0;
	int intKentuckyCount = 0;
	int intBooneCount = 0;
	int intKentonCount = 0;

	float sngOhioIncome = 0;
	float sngHamiltonIncome = 0;
	float sngButlerIncome = 0;
	float sngKentuckyIncome = 0;
	float sngBooneIncome = 0;
	float sngKentonIncome = 0;

	float sngOhioIncomeAvg = 0;
	float sngHamiltonIncomeAvg = 0;
	float sngButlerIncomeAvg = 0;
	float sngKentuckyIncomeAvg = 0;
	float sngBooneIncomeAvg = 0;
	float sngKentonIncomeAvg = 0;

	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strState, "Ohio") == 0)
			{
				intOhioCount += 1;
				sngOhioIncome += audtSurveyDataList[intIndex].sngIncome;

				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Hamilton") == 0)
				{
					intHamiltoncount += 1;
					sngHamiltonIncome += audtSurveyDataList[intIndex].sngIncome;
				}
				else
				{
					intButlerCount += 1;
					sngButlerIncome += audtSurveyDataList[intIndex].sngIncome;
				}
			}
			else
			{
				intKentuckyCount += 1;
				sngKentuckyIncome += audtSurveyDataList[intIndex].sngIncome;

				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Boone") == 0)
				{
					intBooneCount += 1;
					sngBooneIncome += audtSurveyDataList[intIndex].sngIncome;
				}
				else
				{
					intKentonCount += 1;
					sngKentonIncome += audtSurveyDataList[intIndex].sngIncome;
				}
			}
		}
	}

	if (intOhioCount > 0)
	{
		sngOhioIncomeAvg = sngOhioIncome / intOhioCount;
	}
	else
	{
		sngOhioIncomeAvg = 0;

	}
	if (intHamiltoncount > 0)
	{
		sngHamiltonIncomeAvg = sngHamiltonIncome / intHamiltoncount;
	}
	else
	{
		sngHamiltonIncomeAvg = 0;

	}
	if (intButlerCount > 0)
	{
		sngButlerIncomeAvg = sngButlerIncome / intButlerCount;
	}
	else
	{
		sngButlerIncomeAvg = 0;
	}
	if (intKentuckyCount > 0)
	{
		sngKentuckyIncomeAvg = sngKentuckyIncome / intKentuckyCount;
	}
	else
	{
		sngKentuckyIncomeAvg = 0;
	}
	if (intBooneCount > 0)
	{
		sngBooneIncomeAvg = sngBooneIncome / intBooneCount;
	}
	else
	{
		sngBooneIncomeAvg = 0;
	}
	if (intKentonCount > 0)
	{
		sngKentonIncomeAvg = sngKentonIncome / intKentonCount;
	}
	else
	{
		sngKentonIncomeAvg = 0;
	}

	printf("--------------------------------------------------------------\n");
	printf("Average Income (By County)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tOhio:\t\t\t$%.2f\n", sngOhioIncomeAvg);
	printf("\t\tHamilton:\t$%.2f\n", sngHamiltonIncomeAvg);
	printf("\t\tButler:\t\t$%.2f\n", sngButlerIncomeAvg);
	printf("\tKentucky:\t\t$%.2f\n", sngKentuckyIncomeAvg);
	printf("\t\tBoone:\t\t$%.2f\n", sngBooneIncomeAvg);
	printf("\t\tKenton:\t\t$%.2f\n", sngKentonIncomeAvg);

	return intHouseholdCountyCount;
}

// --------------------------------------------------------------------------------
// Name: AverageIncomeRace
// Abstract: Average Income of Households by race
// --------------------------------------------------------------------------------
float AverageIncomeRace(udtSurveyData audtSurveyDataList[])
{
	int intCaucasianCount = 0;
	int intBlackCount = 0;
	int intHispanicCount = 0;
	int intAsianCount = 0;
	int intOtherCount = 0;

	float sngCaucasianIncome = 0;
	float sngBlackIncome = 0;
	float sngHispanicIncome = 0;
	float sngAsianIncome = 0;
	float sngOtherIncome = 0;

	float sngCaucasianAvg = 0;
	float sngBlackAvg = 0;
	float sngHispanicAvg = 0;
	float sngAsianAvg = 0;
	float sngOtherAvg = 0;

	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strRace, "Caucasian") == 0)
			{
				intCaucasianCount += 1;
				sngCaucasianIncome += audtSurveyDataList[intIndex].sngIncome;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "African American") == 0)
			{
				intBlackCount += 1;
				sngBlackIncome += audtSurveyDataList[intIndex].sngIncome;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Hispanic") == 0)
			{
				intHispanicCount += 1;
				sngHispanicIncome += audtSurveyDataList[intIndex].sngIncome;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Asian") == 0)
			{
				intAsianCount += 1;
				sngAsianIncome += audtSurveyDataList[intIndex].sngIncome;
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Other") == 0)
			{
				intOtherCount += 1;
				sngOtherIncome += audtSurveyDataList[intIndex].sngIncome;
			}
		}
	}

	if (intCaucasianCount > 0)
	{
		sngCaucasianAvg = sngCaucasianIncome / intCaucasianCount;
	}
	else
	{
		sngCaucasianAvg = 0;
	}
	if (intBlackCount > 0)
	{
		sngBlackAvg = sngBlackIncome / intBlackCount;
	}
	else
	{
		sngBlackAvg = 0;
	}
	if (intHispanicCount > 0)
	{
		sngHispanicAvg = sngHispanicIncome / intHispanicCount;
	}
	else
	{
		sngHispanicAvg = 0;
	}
	if (intAsianCount > 0)
	{
		sngAsianAvg = sngAsianIncome / intAsianCount;
	}
	else
	{
		sngAsianAvg = 0;
	}
	if (intOtherCount > 0)
	{
		sngOtherAvg = sngOtherIncome / intOtherCount;
	}
	else
	{
		sngOtherAvg = 0;
	}

	printf("--------------------------------------------------------------\n");
	printf("Average Income (By Race)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tCaucasian:\t\t$%.2f\n", sngCaucasianAvg);
	printf("\tAfrican American:\t$%.2f\n", sngBlackAvg);
	printf("\tHispanic:\t\t$%.2f\n", sngHispanicAvg);
	printf("\tAsian:\t\t\t$%.2f\n", sngAsianAvg);
	printf("\tOther:\t\t\t$%.2f\n", sngOtherAvg);
}


// --------------------------------------------------------------------------------
// Name: CheckBelowPoverty
// Abstract: Check if below Poverty
// --------------------------------------------------------------------------------
boolean CheckBelowPoverty(udtSurveyData audtSurveyDataList)
{
	int intIndex = 0;
	boolean blnPoverty = false;

		if (audtSurveyDataList.intHouseholdCount == 1 && audtSurveyDataList.sngIncome < 12000)
		{
			blnPoverty = true;
		}
		else if (audtSurveyDataList.intHouseholdCount == 2 && audtSurveyDataList.sngIncome < 18000)
		{
			blnPoverty = true;
		}
		else if (audtSurveyDataList.intHouseholdCount == 3 && audtSurveyDataList.sngIncome < 25000)
		{
			blnPoverty = true;
		}
		else if (audtSurveyDataList.intHouseholdCount == 4 && audtSurveyDataList.sngIncome < 30000)
		{
			blnPoverty = true;
		}
		else if (audtSurveyDataList.intHouseholdCount >= 5 && audtSurveyDataList.sngIncome < 40000)
		{
			blnPoverty = true;
		}
			return blnPoverty;
}


// --------------------------------------------------------------------------------
// Name: PercentageBelowPoverty
// Abstract: Sum of Households by race
// --------------------------------------------------------------------------------
float PercentageBelowPoverty(udtSurveyData audtSurveyDataList[], int TotalHouseholds)
{
	int intIndex = 0;
	float intTotalCount = TotalHouseholds;
	float intPovertyCount = 0;
	float sngPercentPoverty = 0.0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount == 1 && audtSurveyDataList[intIndex].sngIncome < 12000)
		{
			intPovertyCount += 1;
		}
		else if (audtSurveyDataList[intIndex].intHouseholdCount == 2 && audtSurveyDataList[intIndex].sngIncome < 18000)
		{
			intPovertyCount += 1;
		}
		else if (audtSurveyDataList[intIndex].intHouseholdCount == 3 && audtSurveyDataList[intIndex].sngIncome < 25000)
		{
			intPovertyCount += 1;
		}
		else if (audtSurveyDataList[intIndex].intHouseholdCount == 4 && audtSurveyDataList[intIndex].sngIncome < 30000)
		{
			intPovertyCount += 1;
		}
		else if (audtSurveyDataList[intIndex].intHouseholdCount >= 5 && audtSurveyDataList[intIndex].sngIncome < 40000)
		{
			intPovertyCount += 1;
		}
	}
	sngPercentPoverty = (intPovertyCount/ intTotalCount) * 100;

	printf("--------------------------------------------------------------\n");
	printf("Percentage Below Poverty:\t%.2f%%\n", sngPercentPoverty);
	printf("--------------------------------------------------------------\n");
}


// --------------------------------------------------------------------------------
// Name: PercentageBelowPovertyCounty
// Abstract: Sum of Households by race
// --------------------------------------------------------------------------------
float PercentageBelowPovertyCounty(udtSurveyData audtSurveyDataList[])
{
	int intHouseholdCountyCount = 0;
	int intOhioCount = 0;
	int intHamiltoncount = 0;
	int intButlerCount = 0;
	int intKentuckyCount = 0;
	int intBooneCount = 0;
	int intKentonCount = 0;

	float sngOhioPovCount = 0;
	float sngHamiltonPovCount = 0;
	float sngButlerPovCount = 0;
	float sngKentuckyPovCount = 0;
	float sngBoonePovCount = 0;
	float sngKentonPovCount = 0;

	float sngOhioPovPerc = 0;
	float sngHamiltonPovPerc = 0;
	float sngButlerPovPerc = 0;
	float sngKentuckyPovPerc = 0;
	float sngBoonePovPerc = 0;
	float sngKentonPovPerc = 0;

	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strState, "Ohio") == 0)
			{
				intOhioCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngOhioPovCount += 1;
				}

				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Hamilton") == 0)
				{
					intHamiltoncount += 1;
					if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
					{
						sngHamiltonPovCount += 1;
					}
				}
				else
				{
					intButlerCount += 1;
					if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
					{
						sngButlerPovCount += 1;
					}
				}
			}
			else
			{
				intKentuckyCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngKentuckyPovCount += 1;
				}

				if (strcmp(audtSurveyDataList[intIndex].strCounty, "Boone") == 0)
				{
					intBooneCount += 1;
					if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
					{
						sngBoonePovCount += 1;
					}
				}
				else
				{
					intKentonCount += 1;
					if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
					{
						sngKentonPovCount += 1;
					}
				}
			}
		}
	}

	if (intOhioCount > 0)
	{
		sngOhioPovPerc = (sngOhioPovCount / intOhioCount) * 100;
	}
	else
	{
		sngOhioPovPerc = 0;
	}
	if (intHamiltoncount > 0)
	{
		sngHamiltonPovPerc = (sngHamiltonPovCount / intHamiltoncount) * 100;
	}
	else
	{
		sngHamiltonPovPerc = 0;
	}
	if (intButlerCount > 0)
	{
		sngButlerPovPerc = (sngButlerPovCount / intButlerCount) * 100;
	}
	else
	{
		sngButlerPovPerc = 0;
	}
	if (intKentuckyCount > 0)
	{
		sngKentuckyPovPerc = (sngKentuckyPovCount / intKentuckyCount) * 100;
	}
	else
	{
		sngKentuckyPovPerc = 0;
	}
	if (intBooneCount > 0)
	{
		sngBoonePovPerc = (sngBoonePovCount / intBooneCount) * 100;
	}
	else
	{
		sngBoonePovPerc = 0;
	}
	if (intKentonCount > 0)
	{
		sngKentonPovPerc = (sngKentonPovCount / intKentonCount) * 100;
	}
	else
	{
		sngKentonPovPerc = 0;
	}

	printf("--------------------------------------------------------------\n");
	printf("Percent Below Poverty (By County)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tOhio:\t\t\t%.2f%%\n", sngOhioPovPerc);
	printf("\t\tHamilton:\t%.2f%%\n", sngHamiltonPovPerc);
	printf("\t\tButler:\t\t%.2f%%\n", sngButlerPovPerc);
	printf("\tKentucky:\t\t%.2f%%\n", sngKentuckyPovPerc);
	printf("\t\tBoone:\t\t%.2f%%\n", sngBoonePovPerc);
	printf("\t\tKenton:\t\t%.2f%%\n", sngKentonPovPerc);
}


// --------------------------------------------------------------------------------
// Name: PercentageBelowPovertyRace
// Abstract: Percentage Below Poverty by race
// --------------------------------------------------------------------------------
float PercentageBelowPovertyRace(udtSurveyData audtSurveyDataList[])
{
	int intCaucasianCount = 0;
	int intBlackCount = 0;
	int intHispanicCount = 0;
	int intAsianCount = 0;
	int intOtherCount = 0;

	float sngCaucasianPovCount = 0;
	float sngBlackPovCount = 0;
	float sngHispanicPovCount = 0;
	float sngAsianPovCount = 0;
	float sngOtherPovCount = 0;

	float sngCaucasianPovPerc = 0;
	float sngBlackPovPerc = 0;
	float sngHispanicPovPerc = 0;
	float sngAsianPovPerc = 0;
	float sngOtherPovPerc = 0;

	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			if (strcmp(audtSurveyDataList[intIndex].strRace, "Caucasian") == 0)
			{
				intCaucasianCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngCaucasianPovCount += 1;
				}
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "African American") == 0)
			{
				intBlackCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngBlackPovCount += 1;
				}
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Hispanic") == 0)
			{
				intHispanicCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngHispanicPovCount += 1;
				}
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Asian") == 0)
			{
				intAsianCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngAsianPovCount += 1;
				}
			}
			else if (strcmp(audtSurveyDataList[intIndex].strRace, "Other") == 0)
			{
				intOtherCount += 1;
				if (CheckBelowPoverty(audtSurveyDataList[intIndex]) == true)
				{
					sngOtherPovCount += 1;
				}
			}

		}
	}

	if (intCaucasianCount > 0)
	{
		sngCaucasianPovPerc = (sngCaucasianPovCount / intCaucasianCount) * 100;
	}
	else
	{
		sngCaucasianPovPerc = 0;
	}
	if (intBlackCount > 0)
	{
		sngBlackPovPerc = (sngBlackPovCount / intBlackCount) * 100;
	}
	else
	{
		sngBlackPovPerc = 0;
	}
	if (intHispanicCount > 0)
	{
		sngHispanicPovPerc = (sngHispanicPovCount / intHispanicCount) * 100;
	}
	else
	{
		sngHispanicPovPerc = 0;
	}
	if (intAsianCount > 0)
	{
		sngAsianPovPerc = (sngAsianPovCount / intAsianCount) * 100;
	}
	else
	{
		sngAsianPovPerc = 0;
	}
	if (intOtherCount > 0)
	{
		sngOtherPovPerc = (sngOtherPovCount / intOtherCount) * 100;
	}
	else
	{
		sngOtherPovPerc = 0;
	}

	printf("--------------------------------------------------------------\n");
	printf("Percent Below Poverty (By Race)\n");
	printf("--------------------------------------------------------------\n");
	printf("\tCaucasian:\t\t%.2f%%\n", sngCaucasianPovPerc);
	printf("\tAfrican American:\t%.2f%%\n", sngBlackPovPerc);
	printf("\tHispanic:\t\t%.2f%%\n", sngHispanicPovPerc);
	printf("\tAsian:\t\t\t%.2f%%\n", sngAsianPovPerc);
	printf("\tOther:\t\t\t%.2f%%\n", sngOtherPovPerc);
}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyList
// Abstract: Initialize all the survey data in the list
// --------------------------------------------------------------------------------
void InitializeSurveyList(udtSurveyData audtSurveyDataList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		//Pass a single array element  by pointer
		InitializeSurvey(&audtSurveyDataList[intIndex]);
	}
}

// --------------------------------------------------------------------------------
// Name: InitializeSurvey
// Abstract: Set all the values to 0 or empty strings
// --------------------------------------------------------------------------------
void InitializeSurvey(udtSurveyData* pudtSurveyData)
{
	StringCopy(pudtSurveyData->strDate, "");
	StringCopy(pudtSurveyData->strState, "");
	StringCopy(pudtSurveyData->strCounty, "");
	StringCopy(pudtSurveyData->strRace, "");
	pudtSurveyData->intHouseholdCount = 0;
	pudtSurveyData->sngIncome = 0;
}

// --------------------------------------------------------------------------------
// Name: PopulateSurveyList
// Abstract: Load the survey data from a file into the array.
// --------------------------------------------------------------------------------
void PopulateSurveyList(udtSurveyData audtSurveyDataList[])
{
	//Declare a file pointer
	FILE* pfillInput = 0;
	int intResultFlag = 0;
	char strBuffer[100] = "";
	char chrLetter = 0;
	int intIndex = 0;

	//Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile("c:\\temp\\Census.txt", &pfillInput);

	//Was file opened?
	if (intResultFlag == 1)
	{
		//yes, read records until EOF
		while (feof(pfillInput) == 0)
		{
			//Read next line from file
			ReadNextLineFromFile(strBuffer, pfillInput);

			AddSurveyDataToArray(strBuffer, &audtSurveyDataList[intIndex]);
			intIndex += 1;
		}
		//clean up
		fclose(pfillInput);
	}
}


// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile(char strFileName[], FILE** ppfilInput)
{
	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen(strFileName, "rb");

	// Success?
	if (*ppfilInput != 0)
	{
		// Yes
		intResultFlag = 1;
	}
	else
	{
		// No
		printf("Error opening %s for reading!!!\n", strFileName);
	}

	return intResultFlag;
}

// --------------------------------------------------------------------------------
// Name: ReadNextLineFromFile
// Abstract: Read until end of line or end of file
// --------------------------------------------------------------------------------
int ReadNextLineFromFile(char strBuffer[], FILE* pfilInput)
{
	char chrLetter = 0;
	int intIndex = 0;

	while (feof(pfilInput) == 0)
	{
		chrLetter = fgetc(pfilInput);
		strBuffer[intIndex] = chrLetter;
		intIndex += 1;

		if (chrLetter == '\n')
		{
			//stop reading
			break;
		}
	}
	//terminate
	strBuffer[intIndex] = 0;
}


// --------------------------------------------------------------------------------
// Name: PrintSurveyList
// Abstract: Print all the Survey data
// --------------------------------------------------------------------------------
void PrintSurveyList(udtSurveyData audtSurveyDataList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtSurveyDataList[intIndex].intHouseholdCount > 0)
		{
			//Pass a single array element
			PrintSurveyData(intIndex, audtSurveyDataList[intIndex]);

		}
	}
}


// --------------------------------------------------------------------------------
// Name: PrintSurveyData
// Abstract: Print all the Survey Data
// --------------------------------------------------------------------------------
void PrintSurveyData(int intIndex, udtSurveyData udtSurveyData)
{
	printf("\n");
	printf("Survey Data #%2d ---------------------------------------\n", intIndex + 1);
	//printf("\tRecord ID     : %ld\n", udtSurveyData.lngRecordID);
	printf("\tDate			: %s\n", udtSurveyData.strDate);
	printf("\tState			: %s\n", udtSurveyData.strState);
	printf("\tCounty			: %s\n", udtSurveyData.strCounty);
	printf("\tRace			: %s\n", udtSurveyData.strRace);
	printf("\tSize of Household	: %d\n", udtSurveyData.intHouseholdCount);
	printf("\tIncome			: %.2f\n", udtSurveyData.sngIncome);
}


// --------------------------------------------------------------------------------
// Name: String Copy
// Abstract: Copy the source to the destination
// --------------------------------------------------------------------------------
void StringCopy(char strDestination[], char strSource[])
{
	int intIndex = 0;

	//Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intIndex] = strSource[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intIndex] = 0;
}


// --------------------------------------------------------------------------------
// Name: AddSurveyDataToArray
// Abstract: Add survey data to the array
// --------------------------------------------------------------------------------
void AddSurveyDataToArray(char strData[], udtSurveyData* pudtSurveyData)
{
	char strNextField[50] = "";

	// Add comma to the end of string
	AppendString(strData, ",");

	// Date
	GetNextField(strNextField, strData, ',');
	//SplitFullName(pudtSurveyData, strNextField);
	StringCopy(pudtSurveyData->strDate, strNextField);

	// State
	GetNextField(strNextField, strData, ',');
	StringCopy(pudtSurveyData->strState, strNextField);

	// County
	GetNextField(strNextField, strData, ',');
	StringCopy(pudtSurveyData->strCounty, strNextField);

	// Race
	GetNextField(strNextField, strData, ',');
	StringCopy(pudtSurveyData->strRace, strNextField);

	// Size of Household
	GetNextField(strNextField, strData, ',');
	pudtSurveyData->intHouseholdCount = atoi(strNextField);

	// Income
	GetNextField(strNextField, strData, ',');
	pudtSurveyData->sngIncome = atof(strNextField);
}


// --------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// --------------------------------------------------------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	// Pre-test because string may be empty
	while (strSource[intIndex] != 0)
	{
		intIndex += 1;
	}

	intLength = intIndex;

	return intLength;
}



//// --------------------------------------------------------------------------------
//// Name: GetNextField
//// Abstract: Get next field in record and remove info up to delimiter
//// --------------------------------------------------------------------------------
void GetNextField(char strNextField[], char strSource[], char chrDelimiter)
{
	int intDelimiterIndex = 0;
	int intIndex = 0;
	char strBuffer[100] = "";

	//Find delimiter
	intDelimiterIndex = FindLetterIndex(strSource, chrDelimiter);

	if (intDelimiterIndex >= 0)
	{
		//Copy everything up to comma into next field
		for (intIndex = 0; intIndex < intDelimiterIndex; intIndex += 1)
		{
			strNextField[intIndex] = strSource[intIndex];
		}

		//terminate
		strNextField[intIndex] = 0;

		intIndex = 0;

		//Copy everything from comma up to end of string
		while (strSource[intDelimiterIndex + intIndex + 1] != 0)
		{
			strBuffer[intIndex] = strSource[intDelimiterIndex + intIndex + 1];
			intIndex += 1;
		}
		//terminate
		strBuffer[intIndex] = 0;

		//copy back to survey data
		StringCopy(strSource, strBuffer);

		Trim(strSource);
		Trim(strNextField);
	}
}

// --------------------------------------------------------------------------------
// Name: AppendString
// Abstract: Append the source to the end of the destinatoin.
// --------------------------------------------------------------------------------
void AppendString(char strDestination[], char strSource[])
{
	int intDestinationLength = 0;
	int intIndex = 0;

	// Find the length
	intDestinationLength = StringLength(strDestination);

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = strSource[intIndex];

		intIndex += 1;
	}

	// Terminate
	strDestination[intDestinationLength + intIndex] = 0;
}


// --------------------------------------------------------------------------------
// Name: FindLetterIndex
// Abstract: Find first occurence of letter (case-sensitive) from left to right.
// --------------------------------------------------------------------------------
int FindLetterIndex(char strSource[], char chrLetterToFind)
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	// Check character
	while (strSource[intIndex] != 0)
	{
		// Is this the character for which we are looking
		if (strSource[intIndex] == chrLetterToFind)
		{
			// Yes, save the index
			intLetterToFindIndex = intIndex;

			// Stop searching
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
}


// --------------------------------------------------------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// --------------------------------------------------------------------------------
void Trim(char strSource[])
{
	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	// Default first non-whitespace character index to end of string in case string is all whitespace
	intFirstNonWhitespaceIndex = StringLength(strSource);

	// Find first non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			// Stop searching!
			break;
		}

		// Next character
		intIndex += 1;
	}

	// Find the last non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		// Next character
		intIndex += 1;
	}

	// Any non-whitepsace characters?
	if (intFirstNonWhitespaceIndex >= 0)
	{
		// Yes, copy everything in between
		for (intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1)
		{
			// Copy next character
			strSource[intDestinationIndex] = strSource[intSourceIndex];

			intDestinationIndex += 1;
		}
	}

	// Terminate 
	strSource[intDestinationIndex] = 0;
}



// --------------------------------------------------------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
boolean IsWhiteSpace(char chrLetterToCheck)
{
	boolean blnIsWhiteSpace = false;

	// Space
	if (chrLetterToCheck == ' ') blnIsWhiteSpace = true;

	// Tab
	if (chrLetterToCheck == '\t') blnIsWhiteSpace = true;

	// Carriarge return
	if (chrLetterToCheck == '\r') blnIsWhiteSpace = true;

	// Line feed
	if (chrLetterToCheck == '\n') blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}


// --------------------------------------------------------------------------------
// Name: CountWords
// Abstract: Count the words in a string
// --------------------------------------------------------------------------------
int CountWords(char strSource[])
{
	int intWordCount = 0;
	int intIndex = 0;
	char chrCurrentLetter = 0;
	char chrPreviousLetter = ' ';

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		chrCurrentLetter = strSource[intIndex];

		// Word boundary (space followed by non-space)?
		if (chrPreviousLetter == ' ' && chrCurrentLetter != ' ')
		{
			// Yes, count it
			intWordCount += 1;
		}

		// Save current character
		chrPreviousLetter = chrCurrentLetter;

		// Next
		intIndex += 1;
	}

	return intWordCount;
}

// --------------------------------------------------------------------------------
// Name: empty_stdin
// Abstract: emptys buffer
// --------------------------------------------------------------------------------
void empty_stdin(void) {
	int unwantedCharacter = getchar();

	while (unwantedCharacter != '\n' && unwantedCharacter != EOF)
		unwantedCharacter = getchar();
}

// --------------------------------------------------------------------------------
// Name: ProgramEnded
// Abstract: Ends Program
// --------------------------------------------------------------------------------
void ProgramEnded()
{
	printf("\n\nProgram Ended.\n\n");
	printf ("             ________________________________________________\n");
	printf ("            /                                                \\\n");
	printf ("           |    _________________________________________     |\n");
	printf ("           |   |                                         |    |\n");
	printf ("           |   |  C:\> Thank You!                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |                                         |    |\n");
	printf("           |   |_________________________________________|    |\n");
	printf("           |                                                  |\n");
	printf("           \\_________________________________________________ / \n");
	printf("                   \\___________________________________ / \n");
	printf("                ___________________________________________\n");
	printf("             _ - '    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n");
	printf("          _ - '.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_ \n");
	printf("       _ - '.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_ \n");
	printf("    _ - '.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_ \n");
	printf(" _ - '.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`- \n");
	printf(":------------------------------------------------------------------------ - : \n");
	printf("`---._.------------------------------------------------------------ - ._.-- - '\n\n\n");


	Sleep(1000);
	exit(0);
}