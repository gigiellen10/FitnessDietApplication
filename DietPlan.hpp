#pragma once

#include <string>


class DietPlan {

public:
	// constructor here - init a diet plan

	DietPlan(int newCals = 0, std::string newPlan = "", std::string newDate = "");

	// copy constructor 
	DietPlan(DietPlan& copyDiet);

	// destructor
	~DietPlan(void);

	// setter
	void setDietPlan(int newGoalCals, std::string newPlanName, std::string newDate);

	// getters
	int getGoalCals(void);
	std::string getPlanName(void);
	std::string getDate(void);

	int editGoal(void);



private:

	int goalCals;
	std::string planName;
	std::string date;

};

// diet plan overloaded operators
std::ostream& operator<<(std::ostream& lhs, DietPlan& const rhs); // may need to change to fstream
std::fstream& operator<<(std::fstream& lhs, DietPlan &rhs);
std::fstream& operator>> (std::fstream& lhs, DietPlan& rhs);

