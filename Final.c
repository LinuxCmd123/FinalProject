#include <stdlib.h>		//library for c program
#include <stdio.h>		//library for c program
#include<string.h>		//library for using strcmp() and strcpy() functions
#include<time.h>		//library to calculate time
#include "Questions.txt"

/*
struct to store the information for a question which includes,
whole question, its 4 options and an answer
*/
struct questionInfo
{
	char questionString[1000];		//character array to store question statement
	char* options[4];				//character array of 4 size, pointed by pointer, to store the options
	char answer[500];				//character array to store the answer
};

/*
declaration of the function which initializes questions array
this function takes an array of type questionInfo as a parameter
*/
void initialize(struct questionInfo question[]);

//Main Function of Program
int main()
{
	/*
	Declaring an array of type questionInfo of size 12.
	The size is set to 12 because either the user can correctly answer 10 questions.
	Or if he answer 9 questions correctly and 3 questions wrong then 9 + 3 = 12.
	So, atleast 12 questions must be present there
	*/
	struct questionInfo question[12];

	//declaration of variables for counting of points and wrong attempts
	int wrongAttempts = 0, points = 0, questionNum = 0, choice = 0, select = 0;
	//object for time calculation
	time_t initialTime;

	//calling this function to initialize the questions array
	initialize(question);

	/*
	Iterate over each question untill either points become 10 or wrong attempts become 10 or
	user chooses to exit the quiz
	*/
	while (points != 10 && wrongAttempts != 3 && choice != -1)
	{
		//display the current points and wrong attempts made
		printf("You can exit the quiz by pressing -1\n");
		printf("Your Points: %d\n", points);
		printf("Wrong attempts: %d\n\n", wrongAttempts);

		//display the question statement for current question number
		printf("Q%d: %s\n\n", questionNum + 1, question[questionNum].questionString);
		//display all its 4 options using for loop
		for (int i = 0; i < 4; i++)
		{
			printf("Option %d: %s\n", i + 1, question[questionNum].options[i]);
		}
		//prompt the user to choose an option
		printf("\nSelect one option number= ");
		//start the timer
		initialTime = time(NULL);
		//take user input now
		scanf("%d", &choice);
		//stop the timer and calculate the time taken by user to input
		time_t timeTakenForInput = (double)(time(NULL) - initialTime);

		/*
		if user chooses an option number out of range then display error and
		ask him to choose an option out of 4 options only and
		repeat the steps of calculating time taken
		*/
		while (choice < -1 || choice > 4)
		{
			printf("\nPlease choose from options available only: ");
			initialTime = time(NULL);
			scanf("%d", &choice);
			time_t timeTakenForInput = (double)(time(NULL) - initialTime);
		}
		//if user choose to exit the quiz then exit the loop
		if (choice == -1)
			break;
		//clear the terminal
		system("cls");

		/*
		if the answer stored in option selected by user matches the correct answer of
		question and time taken of user input is not greater than 60, then add a point
		*/
		if (strcmp(question[questionNum].options[choice - 1], question[questionNum].answer) == 0 && timeTakenForInput <= 60)
		{
			points++;
			printf("Your answer was correct. ");
		}
		/*
		if the answer stored in option selected by user DOES NOT matches the correct answer of
		question even the time taken of user input is not greater than 60, then its counted as wrong attempt
		and no point is given
		*/
		else if (strcmp(question[questionNum].options[choice - 1], question[questionNum].answer) != 0 && timeTakenForInput <= 60)
		{
			wrongAttempts++;
			printf("Your answer was wrong. ");
		}
		/*
		if the time taken of user input is greater than 60 then its counted as wrong attempt
		and no point is given
		*/
		else if (timeTakenForInput > 60)
		{
			wrongAttempts++;
			printf("Your answer is counted wrong because you took more than 60 seconds. ");
		}
		//move to next question so that next question will be display from array
		questionNum++;
		//display the current total points and wrong attempts made
		printf("\nTotal Points: %d\n", points);
		printf("Wrong attempts: %d\n\n", wrongAttempts);
		//ask user if he want to continue the quiz or wants to exit
		printf("Press 1 to show next question\nPress 2 to exit the quiz\nYour choice: ");
		//read input for his choice
		scanf("%d", &select);

		/*
		if user enters other than 1 and 2 then show error and
		ask him to select between 1 and 2 only
		*/
		while (select != 1 && select != 2)
		{
			printf("\nPlease choose correct option !!\n\nPress 1 to show next question\nPress 2 to exit the quiz\nYour choice: ");
			scanf("%d", &select);
		}
		//if user selects 2 then exit the quiz by exiting the loop
		if (select == 2)
			break;
		//clear the screen
		system("cls");
	}

	//out from quiz now, display the earned points and wrong attempts made
	printf("\nEnd of quiz !!!\n");
	printf("Total Points: %d\n", points);
	printf("Wrong attempts: %d\n\n", wrongAttempts);
	//if points are 10 then display that you are hired
	if (points == 10)
		printf("Congratulations, you are hired for the job !!!\n\n!");
	//if points are not equal to 10 then display that you are NOT hired
	else
		printf("Sorry, you are not hired for the job !!!\n\n");
	//exit the main()

	return 0;
}

/*
definition of the function which initializes questions array
this function takes an array of type questionInfo as a parameter
*/
void initialize(struct questionInfo question[])
{
	/*
	using strcpy() function to copy the question statement and its
	answer into the respective character arrays
	each question will have 4 options, out of which only 1 is correct
	*/
	FILE* fp;
	fp = fopen("questions.txt", "r");	//opening the file for reading.
	size_t size = 1000;				//no. of characters to read from file.

	for (int i = 0; i < 11; i++) {
		char* str = (char*)malloc(sizeof(char) * 1000);	//str to hold input question string from file
		size = 1000;
		getline(&str, &size, fp);						//reading the input from file
		if (str[0] == '-')									//check if the question has ended
			getline(&str, &size, fp);					//reading the new question
		strcpy(question[i].questionString, str);			//copy the str into question.questionstring
		for (int j = 0; j <= 4; j++) {
			char* opt = (char*)malloc(sizeof(char) * 500);	//to hold options read from he file
			size = 500;
			getline(&opt, &size, fp);					//reading the input from file
			if (j == 4) {
				//check if this is the last option from the file. If yes copy this into answer else copy in option
				strcpy(question[i].answer, opt);
			}
			else {
				question[i].options[j] = (char*)malloc(sizeof(char) * 500);	 //creating new array to hold the option input from file
				strcpy(question[i].options[j], opt);  					//copy the input from file to option.
			}
		}
	}
}
