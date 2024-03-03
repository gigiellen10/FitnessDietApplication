#pragma once


class ExercisePlan {

public:

	// constructor here
	ExercisePlan(int newGoalSteps = 0, std::string newPlan = "", std::string newDate = "");

	// copy constructor here
	ExercisePlan(ExercisePlan& copyExercise);

	// destructor
	~ExercisePlan(void);

	// setter
	void setExercisePlan(int newGoalSteps, std::string newPlanName, std::string newDate);


	// getter
	int getGoalSteps(void) const;
	std::string getPlanName(void) const;
	std::string getDate(void) const;

	int editGoal(void);

private:

	int goalSteps;
	std::string planName;
	std::string date;

};

// exercise operator overloading
std::ostream& operator<<(std::ostream& lhs, ExercisePlan& const rhs);
std::fstream& operator<<(std::fstream& lhs, ExercisePlan& rhs);
std::fstream& operator>> (std::fstream& lhs, ExercisePlan& rhs);

