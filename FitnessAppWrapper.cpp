#include "PA4.hpp"
#include "FitnessAppWrapper.hpp"

/* Setter, Getter, constructor for linked lists */

// diet
void DietListNode::setDietNodeNewData(DietPlan newData)
{
	data = newData;
}

void DietListNode::setDietNodePNext(DietListNode* newPNext)
{
	pNext = newPNext;
}

DietPlan DietListNode::getDietPlanNodeData(void)
{
	return data;
}

DietListNode* DietListNode::getPNext(void)
{
	return pNext;
}


void DietList::setpHead(DietListNode* setpHead)
{
	pHead = setpHead;
}

DietListNode* DietList::getpHead(void)
{
	return pHead;
}

// copy constructor
DietListNode::DietListNode(DietListNode& copyListNode)
{
	data = copyListNode.data;
	pNext = copyListNode.pNext;
}

DietListNode::DietListNode(DietPlan newData, DietListNode* newpNext)
{
	data = newData;
	pNext = newpNext;
}

int DietList::insertAtBack(DietPlan newData)
{
	int success = 0;
	// allocate memory for node here using new 
	DietListNode* pMem = new DietListNode(newData, nullptr), *temp = pHead;

	if (pMem != nullptr)
	{
		success = 1; // successfully got memory on the heap
		
		if (pHead == nullptr) // ~ insert at front of empty list
		{
			pHead = pMem;
		}
		else {

			// find position at the end
			for (; temp->getPNext() != nullptr; temp = temp->getPNext());
			
			// insert 

			temp->setDietNodePNext(pMem);

		}
	}

	return success;
}


// finds specified node in the list and returns the address of that node
DietListNode* DietList::searchList(int userChoice)
{
	DietListNode* iterate = pHead;
	int count = 1;

	if (userChoice < 1) // handle invalid input
	{
		return nullptr;
	}

	// short circut eval.
	while (iterate != nullptr && count != userChoice)
	{
		iterate = iterate->getPNext();
		++count;
	}

	if (count == userChoice) // successfully found nth node
	{
		return iterate;

	}
	else
	{
		return nullptr; // indicates specified nth node was not found within the list
	}


}


DietList::~DietList(void) // keyword delete calls destructor for this list
{
	DietListNode* pNextToDelete = nullptr, *pCurr = pHead; // will be set to NULL by default by constructor
	

	while (pCurr != nullptr) // while not at end of list, free memory
	{
		pNextToDelete = pCurr->getPNext();
		free (pCurr); 
		pCurr = pNextToDelete; // advance in list

	}

}


// exercise
void ExerciseListNode::setExerciseNodeNewData(ExercisePlan newData) // setter
{
	data = newData; 
}

void ExerciseListNode::setExerciseNodePNext(ExerciseListNode* newPNext) // setter
{
	pNext = newPNext;
}


ExercisePlan ExerciseListNode::getExercisePlanNodeData(void)
{
	return data;
}

ExerciseListNode* ExerciseListNode::getPNext(void)
{
	return pNext;
}

void ExerciseList::setpHead(ExerciseListNode* setpHead)
{
	pHead = setpHead;
}


ExerciseListNode* ExerciseList::getpHead(void)
{
	return pHead;
}

// copy constructor
ExerciseListNode::ExerciseListNode(ExerciseListNode& copyListNode)
{
	data = copyListNode.data;
	pNext = copyListNode.pNext;

}

ExerciseListNode::ExerciseListNode(ExercisePlan newData, ExerciseListNode* newpNext) // inits a dietListNode
{

	data = newData;
	pNext = newpNext;

}

int ExerciseList::insertAtBack(ExercisePlan newData)
{
	int success = 0;
	// allocate memory for node here using new 
	ExerciseListNode* pMem = new ExerciseListNode(newData, nullptr), * temp = pHead;

	if (pMem != nullptr)
	{
		success = 1; // successfully got memory on the heap

		if (pHead == nullptr) // ~ insert at front of empty list
		{
			pHead = pMem;
		}
		else {

			// find position at the end
			for (; temp->getPNext() != nullptr; temp = temp->getPNext());

			// insert 

			temp->setExerciseNodePNext(pMem);

		}
	}

	return success;

}

ExerciseListNode* ExerciseList::searchList(int userChoice)
{
	ExerciseListNode* iterate = pHead;
	int count = 1;

	if (userChoice < 1) // handle invalid input
	{
		return nullptr;
	}

	// short circut eval.
	while (iterate != nullptr && count != userChoice)
	{
		iterate = iterate->getPNext();
		++count;
	}

	if (count == userChoice) // successfully found nth node
	{
		return iterate;

	}
	else
	{
		return nullptr; // indicates specified nth node was not found within the list
	}
}

ExerciseList::~ExerciseList(void)
{
	ExerciseListNode* pNextToDelete = nullptr, * pCurr = pHead; // will be set to NULL by default by constructor


	while (pCurr != nullptr) // while not at end of list, free memory
	{
		pNextToDelete = pCurr->getPNext();
		delete pCurr;
		pCurr = pNextToDelete; // advance in list

	}

}


void FitnessAppWrapper::backToMenu(void)
{
	char buff[100] = "";
		cout << "Double tap enter to go back to the main menu. If you would like to exit, select option (9) from the menu.";

		cin.getline(buff, 100);
		cin.ignore(100, '\n');

}


void FitnessAppWrapper::runApp(void)
{
	int invalid = 0, play = 1, success = -1;
	std::fstream dietPlanFile, exercisePlanFile; // declare file streams

	// init linked lists
	weeklyExerciseList;
	weeklyDietList;

		do 
		{
			char buff[100] = "";
			int decision = 0, invalid = 0, rec = 0; // reset control variables 

			cout << "Welcome to your diet and exercise plan manager!! Please select from the following menu.\n" << std::endl;

			displayMenu();

			cout << "\n\nEnter your choice here (1 - 9): ";

			cin.getline(buff, 100);

			decision = atoi(buff);

			switch (decision)
			{
				// load diet plan
			case 1:
				
				dietPlanFile.open("dietPlans.txt");

				if (dietPlanFile.is_open())
				{
					if (weeklyDietList.getpHead() != nullptr) // clear list if already full
					{
						weeklyDietList.~DietList();
						weeklyDietList.setpHead(); // set pHead back to nullptr
					}

					loadWeeklyPlan(dietPlanFile, weeklyDietList);

					system("cls");
					cout << "Your diet plans have been loaded from the text file!!" << std::endl << std::endl;
					dietPlanFile.close();
				}
				else
				{
					cout << "Error: \"dietPlans.txt\" could not be opened!! No records were loaded.\n" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// load exercise plans
			case 2:

				exercisePlanFile.open("exercisePlan.txt");

				if (exercisePlanFile.is_open())
				{
					if (weeklyExerciseList.getpHead() != nullptr) // clear list if already full
					{
						weeklyExerciseList.~ExerciseList();
						weeklyExerciseList.setpHead(); // set pHead back to nullptr
					}

					loadWeeklyPlan(exercisePlanFile, weeklyExerciseList);

					system("cls");
					cout << "Your exercise plans have been loaded from the text file!!" << std::endl << std::endl;
					exercisePlanFile.close();
				}
				else
				{
					cout << "Error: \"exercisePlan.txt\" could not be opened!! No records were loaded.\n" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// store diet plan 
			case 3:

				dietPlanFile.open("dietPlans.txt");

				if (dietPlanFile.is_open())
				{
					if (weeklyDietList.getpHead() == nullptr)
					{
						system("cls");
						cout << "Sorry, there are no records in your diet plan list. Nothing could be loaded to the file.\n" << std::endl;
					}
					else
					{
						storeWeeklyPlan(dietPlanFile, weeklyDietList);

						system("cls");
						cout << "Your records have been loaded to the file \"dietPlans.txt\"\n" << std::endl;

					}

					dietPlanFile.close();
				}
				else
				{
					cout << "Error: \"dietPlan.txt\" could not be opened!! No records were stored.\n" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// store exercise plan
			case 4:


				exercisePlanFile.open("exercisePlan.txt");

				if (exercisePlanFile.is_open())
				{
					if (weeklyExerciseList.getpHead() == nullptr)
					{
						system("cls");
						cout << "Sorry, there are no records in your exercise plan list. Nothing could be loaded to the file.\n" << std::endl;
					}
					else
					{
						storeWeeklyPlan(exercisePlanFile, weeklyExerciseList);

						system("cls");
						cout << "Your records have been loaded to the file \"exercisePlan.txt\"\n" << std::endl;

					}

					exercisePlanFile.close();
				}
				else
				{
					cout << "Error: \"exercisePlan.txt\" could not be opened!! No records were stored.\n" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// display weekly diet plan
			case 5:

				dietPlanFile.open("dietPlans.txt");

				if (dietPlanFile.is_open())
				{
					system("cls");

					if (weeklyDietList.getpHead() != nullptr)
					{
						displayWeeklyPlan(weeklyDietList);
					}
					else
					{
						cout << "Error: no records contained in your diet plan list. Cannot be displayed.\n" << std::endl;
					}

					dietPlanFile.close();
				}
				else
				{
					system("cls");
					cout << "Error: \"dietPlans.txt\" could not be opened!! No records were stored.\n" << std::endl;
				}

				
				backToMenu();
				system("cls");
				break;

				// display weekly exercise plan
			case 6:
				
				exercisePlanFile.open("exercisePlan.txt");

				if (exercisePlanFile.is_open())
				{
					system("cls");

					if (weeklyExerciseList.getpHead() != nullptr)
					{
						displayWeeklyPlan(weeklyExerciseList);
					}
					else
					{
						cout << "Error: no records contained in your exercise plan list. Cannot be displayed.\n" << std::endl;
					}

					exercisePlanFile.close();
				}
				else
				{
					system("cls");
					cout << "Error: \"exercisePlan.txt\" could not be opened!! No records were stored.\n" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// edit diet plan
			case 7:
				
				system("cls");

				// prompt which to edit and get input
				rec = getRecordToSearch(1);
				
				// search for record
				DietListNode* record;
				record = weeklyDietList.searchList(rec);

				// found a matching record in the list, so can edit
				if (record != nullptr)
				{

					DietPlan tChangeGoal;
					tChangeGoal = record->getDietPlanNodeData(); // copy current data from current record in list

					success = tChangeGoal.editGoal(); // allow user to edit the goal field of the temporary diet plan
					record->setDietNodeNewData(tChangeGoal); // overwrite data in the current node with the updated goal information
					
					if (success)
					{
						system("cls");
						cout << "Record #" << rec << " in your diet list has been updated successfully and now contains:\n" << std::endl;
						displayDailyPlan(record);
						cout << "\n\n";
					}

				}
				else if (rec != -1)
				{
					system("cls");
					cout << "Sorry, that record does not exist in your list.\n";
				}
				else
				{
					// list is empty
					system("cls");
					cout << "Sorry, your list is empty!" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// edit exercise plan
			case 8:

				system("cls");

				// prompt which to edit and get input
				rec = getRecordToSearch(2);

				// search for record
				ExerciseListNode* eRecord;
				eRecord = weeklyExerciseList.searchList(rec);

				// found a matching record in the list, so can edit
				if (eRecord != nullptr)
				{

					ExercisePlan tChangeGoal;
					tChangeGoal = eRecord->getExercisePlanNodeData(); // copy current data from current record in list

					success = tChangeGoal.editGoal(); // allow user to edit the goal field of the temporary diet plan
					eRecord->setExerciseNodeNewData(tChangeGoal); // overwrite data in the current node with the updated goal information

					if (success)
					{
						system("cls");
						cout << "Record #" << rec << " in your exercise list has been updated successfully and now contains: \n" << std::endl;
						displayDailyPlan(eRecord);
						cout << "\n\n";

					}

				}
				else if (rec != -1)
				{
					system("cls");
					cout << "Sorry, that record does not exist in your list.\n";
				}
				else
				{
					// list is empty
					system("cls");
					cout << "Sorry, your list is empty and may not be edited!" << std::endl;
				}

				backToMenu();
				system("cls");
				break;

				// exit
			case 9:

				exercisePlanFile.open("exercisePlan.txt");
				dietPlanFile.open("dietPlans.txt");
				

				// load existing lists to files...
				if (exercisePlanFile.is_open()) {
					
					storeWeeklyPlan(exercisePlanFile, weeklyExerciseList);
					exercisePlanFile.close();
				}
				if (dietPlanFile.is_open())
				{
					storeWeeklyPlan(dietPlanFile, weeklyDietList);
					dietPlanFile.close();
				}
				
				play = 0; // exit main loop

				system("cls");
				break;

			default:
				invalid = 1;
				system("cls");
				cout << "Sorry, that input is invalid. Please try again" << std::endl;
			}

		} while (invalid || play);

		// 7/8 paste new diet/exer plan to screen after changing

		cout << "Exiting program...Goodbye." << std::endl;
}

void FitnessAppWrapper::displayMenu(void)
{
	cout << "1. Load weekly diet plan from file.\n"
		"2. Load weekly exercise plan from file.\n"
		"3. Store weekly diet plan to file.\n"
		"4. Store weekly exercise plan to file.\n"
		"5. Display weekly diet plan to screen.\n"
		"6. Display weekly exercise plan to screen.\n"
		"7. Edit daily diet plan.\n"
		"8. Edit daily exercise plan.\n"
		"9. Exit."; // Note: this must write the most recent weekly plans to the corresponding files

}


void FitnessAppWrapper::loadDailyPlan(std::fstream& fileStream, DietPlan& plan)
{
	
	// reads one record from the file and stores into the DietPlan object passed in
	fileStream >> plan;
	
}

// not tested
void FitnessAppWrapper::loadWeeklyPlan(std::fstream& fileStream, DietList& weeklyPlan)
{
	// we need to load 7 plans total, so will loop 7 times and save each record into a new node in DietList
	for (int count = 0; count != 7; ++count)
	{
		DietPlan newData; 

		loadDailyPlan(fileStream, newData); // load plan into variable

		weeklyPlan.insertAtBack(newData); // store into diet linked list

	}
}

void FitnessAppWrapper::loadDailyPlan(std::fstream& fileStream, ExercisePlan& plan)
{
	fileStream >> plan;

}

void FitnessAppWrapper::loadWeeklyPlan(std::fstream& fileStream, ExerciseList& weeklyPlan)
{
	for (int count = 0; count != 7; ++count)
	{
		ExercisePlan newData;

		loadDailyPlan(fileStream, newData); // load plan into variable

		weeklyPlan.insertAtBack(newData); // store into diet linked list

	}

}


// need to add parameters here
void FitnessAppWrapper::displayDailyPlan(DietListNode* node)
{
	DietPlan d;
	d = node->getDietPlanNodeData();
	
	cout << d;
}

void FitnessAppWrapper::displayDailyPlan(ExerciseListNode* node)
{
	ExercisePlan e;
	e = node->getExercisePlanNodeData();

	cout << e;
}

// print out list
void FitnessAppWrapper::displayWeeklyPlan(DietList& list)
{
	DietListNode* iterate = list.getpHead();

	while (iterate != nullptr)
	{
		displayDailyPlan(iterate); // display plan to screen
		cout << "\n";

		iterate = iterate->getPNext(); // go to next node in list
	}
}

void FitnessAppWrapper::displayWeeklyPlan(ExerciseList& list)
{
	ExerciseListNode* iterate = list.getpHead();

	while (iterate != nullptr)
	{
		displayDailyPlan(iterate); // display plan to screen
		cout << "\n";

		iterate = iterate->getPNext(); // go to next node in list
	}
}


void FitnessAppWrapper::storeDailyPlan(std::fstream& fOut, DietListNode* node)
{
	DietPlan d;
	d = node->getDietPlanNodeData();

	fOut << d << std::endl;

}

void FitnessAppWrapper::storeDailyPlan(std::fstream& fOut, ExerciseListNode* node)
{
	ExercisePlan e;
	e = node->getExercisePlanNodeData();

	fOut << e << std::endl;

}

void FitnessAppWrapper::storeWeeklyPlan(std::fstream& fOut, DietList &list)
{
	DietListNode* iterate = list.getpHead();

	while (iterate != nullptr)
	{
		storeDailyPlan(fOut, iterate); // store to file

		iterate = iterate->getPNext(); // go to next node in list
	}

}

void FitnessAppWrapper::storeWeeklyPlan(std::fstream& fOut, ExerciseList &list)
{
	ExerciseListNode* iterate = list.getpHead();

	while (iterate != nullptr)
	{
		storeDailyPlan(fOut, iterate); // store to file

		iterate = iterate->getPNext(); // go to next node in list
	}

}

/* Function: int isNumber(char str[])
Description: Determines if a string contains all numbers.
Accepts: A string.
Returns: An integer, 0 or 1, indicating if the string was not all numbers or was composed of all digits, respectively.
Preconditions: str[] must be defined.
Postconditions: Return value must be used to validate user input in several do-while loops throughout the program.
*/

int isNumber(char str[])
{
	int isNum = 0, i = 0, result = -1;

	strtok(str, "\n"); // since being used to validate user input, get rid of newline if present

	for (; str[i] != '\0' && isdigit(str[i]) != 0; ++i); // breaks out of loop when end of string or found non-number in string

	if (str[i] == '\0') // did not find non-digit
	{
		isNum = 1;
	}
	else // found non-digit
	{
		isNum = 0;
	}

	return isNum;

}

int FitnessAppWrapper::getRecordToSearch(int dietOrExercise)
{
	
	int isNum = -1, choice = -1, emptyList = 0;

	// check if list is empty
	if (weeklyDietList.getpHead() == nullptr && dietOrExercise == 1)
	{
		return -1;
	}
	else if (weeklyExerciseList.getpHead() == nullptr && dietOrExercise == 2)
	{
		return -1;
	}


	do {
		
		char buff2[100] = "";

		if (dietOrExercise == 1)
		{
			cout << "Would you like to see the records in your diet list?\n"
				"Enter 1 to display your diet plans, or 0 to skip this step: ";
		}
		else if (dietOrExercise == 2)
		{
			cout << "Would you like to see the records in your exercise list?\n"
				"Enter 1 to display your exercise plans, or 0 to skip this step: ";
		}

		cin >> buff2;

		choice = atoi(buff2);
		isNum = isNumber(buff2);

		if ((choice < 0 || choice > 1) || !isNum)
		{
			system("cls");
			cout << "Invalid input. Please enter a number, 0 - 1.\n\n";
		}

	} while ((choice < 0 || choice > 1) || !isNum);

	if (choice == 1 && dietOrExercise == 1)
	{
			system("cls");
			displayWeeklyPlan(weeklyDietList);
			system("pause");
			system("cls");
		
	}
	else if (choice == 1 && dietOrExercise == 2)
	{

			system("cls");
			displayWeeklyPlan(weeklyExerciseList);
			system("pause");
			system("cls");
			
	}

		do {

			char buff[100] = "";
			

			cout << "Which record would you like to edit? (1 - 7): ";

			cin >> buff;

			isNum = isNumber(buff);

			choice = atoi(buff);

			if (!isNum || !(choice > 0 && choice < 8))
			{
				system("cls");
				cout << "Invalid input. Please enter a number 1 - 7.\n\n";
			}

		} while (!isNum || !(choice > 0 && choice < 8));

		return choice;
	
	
}