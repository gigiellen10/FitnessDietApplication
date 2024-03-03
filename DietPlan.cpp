#include "PA4.hpp"
#include "DietPlan.hpp"

// diet plan constructor
DietPlan::DietPlan(int newCals, std::string newPlan, std::string newDate)
{
	if (newCals < 0)
	{
		goalCals = 0;
	}
	else
	{
		goalCals = newCals; // set diet Plan to new cals passed in 
	}

	// no need to validate other members because std strings
	planName = newPlan;

	date = newDate; // overloaded "=" operator

}

// diet plan copy constructor
DietPlan::DietPlan(DietPlan& copyDiet)
{
	goalCals = copyDiet.goalCals;
	planName = copyDiet.planName;
	date = copyDiet.date;

}

// diet plan destructor
DietPlan::~DietPlan(void) { }

/* diet plan setters and getters */

void DietPlan::setDietPlan(int newGoalCals, std::string newPlanName, std::string newDate)
{
	// validate data passed in

	if (newGoalCals < 0)
	{
		goalCals = 0;
	}
	else
	{
		goalCals = newGoalCals;
	}

	// no need to validate strings

	planName = newPlanName; // set private planName to new plan name string passed in
	date = newDate; // set private date to date string passed in
}

int DietPlan::getGoalCals(void)
{
	return goalCals;

}

std::string DietPlan::getPlanName(void)
{
	return planName;
}

std::string DietPlan::getDate(void)
{
	return date;
}

/* Overloaded operator functions - diet plan */

/* stream insertion operator << (1) displaying a plan to the screen and (2) writing to a file */

std::ostream& operator<<(std::ostream& lhs, DietPlan& const rhs)
{
	lhs << "Plan Name: " << rhs.getPlanName() << std::endl;
	lhs << "Date: " << rhs.getDate() << std::endl;
	lhs << "Goal Calories: " << rhs.getGoalCals() << std::endl;

	return lhs;
}

// write to a file -- designed to write each plan entry in a specific format
std::fstream& operator<<(std::fstream& lhs, DietPlan& rhs)
{
	lhs << rhs.getPlanName() << std::endl
		<< rhs.getGoalCals() << std::endl
		<< rhs.getDate() << std::endl;


	return lhs;
}

// stream extraction operator >> - reading a plan from a file, designed to read from a specific format
std::fstream& operator>> (std::fstream& lhs, DietPlan& rhs)
{
	std::string tempPlanName, tempDate, tempGoalCals, empty;
	int goalCals = 0;

	// not validating data here because already validated within getDietPlan() function

	// read in plan name (day of the week), delimeter is \n by default
	std::getline(lhs, tempPlanName);

	// read in goal cals
	std::getline(lhs, tempGoalCals);

	// read in date
	std::getline(lhs, tempDate);

	// read in empty line 

	std::getline(lhs, empty);

	// convert tempGoalCals to integer
	goalCals = stoi(tempGoalCals);

	// store all parsed information into diet plan (rhs)
	rhs.setDietPlan(goalCals, tempPlanName, tempDate);

	return lhs;
}

// everytime plan changed (if this function returns 1), display to screen 
int DietPlan::editGoal(void)
{
	char temp[100] = "";
	// prompt user to enter a new goal
	std::cout << "Enter a new goal: ";

	std::cin >> temp; // store new goal cals into temp string

	if (atoi(temp) < 0 || !isNumber(temp))
	{
		system("cls");
		cout << "Sorry, that data is invalid. Your plan was not edited." << endl;
		return 0; // indicates invalid data (<0) was passed and record was not changed
	}
	else
	{
		goalCals = atoi(temp);
		return 1; // indicates valid data was entered into the goal cals
	}
}
