#include "PA4.hpp"
#include "ExercisePlan.hpp"

// exercise plan constructor
ExercisePlan::ExercisePlan(int newGoalSteps, std::string newPlan, std::string newDate)
{

	if (newGoalSteps < 0)
	{
		goalSteps = 0;
	}
	else
	{
		goalSteps = newGoalSteps;
	}

	// no need to validate other members because std strings
	planName = newPlan;

	date = newDate; // overloaded "=" operator


}

// exercise plan copy constructor
ExercisePlan::ExercisePlan(ExercisePlan& copyExercise)
{

	goalSteps = copyExercise.goalSteps;
	planName = copyExercise.planName;
	date = copyExercise.date;

}

// exercise plan deconstructor - if using dynamic memory allocation, could use to free memory using free() or keyword "delete" in main() to 
// explicitly call the destructor
ExercisePlan:: ~ExercisePlan(void) { }

/* exercise plan setters and getters */

void ExercisePlan::setExercisePlan(int newGoalSteps, std::string newPlanName, std::string newDate)
{
	if (newGoalSteps < 0)
	{
		goalSteps = 0;
	}
	else
	{
		goalSteps = newGoalSteps;
	}

	planName = newPlanName;
	date = newDate;
}

int ExercisePlan::getGoalSteps(void)  const
{
	return goalSteps;
}

std::string ExercisePlan::getPlanName(void) const
{
	return planName;
}

std::string ExercisePlan::getDate(void) const
{
	return date;
}

/* Overloaded operator functions - exercise plan */

/* stream insertion operator << (1) displaying a plan to the screen and (2) writing to a file */
std::ostream& operator<<(std::ostream& lhs, ExercisePlan& const rhs)
{
	lhs << "Plan Name: " << rhs.getPlanName() << endl;
	lhs << "Date: " << rhs.getDate() << endl;
	lhs << "Goal Calories: " << rhs.getGoalSteps() << endl;

	return lhs;
}

std::fstream& operator<<(std::fstream& lhs, ExercisePlan& rhs)
{

	lhs << rhs.getPlanName() << endl
		<< rhs.getGoalSteps() << endl
		<< rhs.getDate() << endl;


	return lhs;

}

// stream extraction operator >> - reading a plan from a file
std::fstream& operator>> (std::fstream& lhs, ExercisePlan& rhs)
{
	std::string tempPlanName, tempDate, tempGoalSteps, empty;
	int goalSteps = 0;

	// not validating data here because already validated within getDietPlan() function

	// read in plan name (day of the week), delimeter is \n by default
	std::getline(lhs, tempPlanName);

	// read in goal cals
	std::getline(lhs, tempGoalSteps);

	// read in date
	std::getline(lhs, tempDate);

	// read in empty line 

	std::getline(lhs, empty);

	// convert tempGoalSteps to integer
	goalSteps = stoi(tempGoalSteps);

	// store all parsed information into diet plan (rhs)
	rhs.setExercisePlan(goalSteps, tempPlanName, tempDate);

	return lhs;
}

// everytime plan changed (if this function returns 1), display to screen 
int ExercisePlan::editGoal(void)
{
	char temp[100] = "";

	// prompt user to enter a new goal
	cout << "Enter a new goal: ";

	cin >> temp; // store new goal cals into temp string

	if (atoi(temp) < 0 || !isNumber(temp))
	{
		system("cls");
		cout << "Sorry, that data is invalid. Your plan was not edited." << endl;
		return 0; // indicates invalid data (<0) was passed and record was not changed
	}
	else
	{
		goalSteps = atoi(temp);
		return 1; // indicates valid data was entered into the goal cals
	}

}