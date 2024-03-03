#pragma once

// do not need to include PA4.hpp here because DietPlan.hpp and ExercisePlan.hpp include it
#include "DietPlan.hpp"
#include "ExercisePlan.hpp"

// nodes
class DietListNode {

public:

	// setter
	void setDietNodeNewData(DietPlan newData); 
	void setDietNodePNext(DietListNode* newPNext);

	// getter
	DietPlan getDietPlanNodeData(void);
	DietListNode* getPNext(void);

	// copy constructor
	DietListNode(DietListNode& copyListNode);

	// constructor 
	DietListNode(DietPlan newData, DietListNode* newpNext = nullptr); // pNext set to NULL by default

private:

	DietPlan data;
	DietListNode* pNext; // singly linked list

};

class ExerciseListNode {

public:

	// setter
	void setExerciseNodeNewData(ExercisePlan newData);
	void setExerciseNodePNext(ExerciseListNode* newPNext);

	// getter
	ExercisePlan getExercisePlanNodeData(void);
	ExerciseListNode* getPNext(void);

	// copy constructor
	ExerciseListNode(ExerciseListNode& copyListNode);

	// constructor 
	ExerciseListNode(ExercisePlan newData, ExerciseListNode* newpNext = nullptr); // pNext set to NULL by default

private:
	ExercisePlan data;
	ExerciseListNode* pNext;

};

// lists: since member functions of list will create memory for a listNode, destructor must be responsible for freeing that memory
class DietList {

public:

	// setter
	void setpHead(DietListNode* setpHead = nullptr);


	// getter
	DietListNode* getpHead(void);

	// destructor
	~DietList(void);

	int insertAtBack(DietPlan newData); // could have malloc() here or in a create node function
	DietListNode* searchList(int userChoice);
	

private:
	DietListNode* pHead;

};

class ExerciseList { 

public:

	// setter
	void setpHead(ExerciseListNode* setpHead = nullptr);


	// getter
	ExerciseListNode* getpHead(void);

	// destroyer
	~ExerciseList(void);

	int insertAtBack(ExercisePlan newData); // could have malloc() here or in a create node function
	ExerciseListNode* searchList(int userChoice);

private:
	ExerciseListNode* pHead;
};

class FitnessAppWrapper {
public:

	void runApp(void);
	void displayMenu(void);
	void backToMenu(void);


private:

	DietList weeklyDietList;
	ExerciseList weeklyExerciseList;


	void loadDailyPlan(std::fstream& fileStream, DietPlan& plan);
	void loadWeeklyPlan(std::fstream& fileStream, DietList& weeklyPlan);
	void loadDailyPlan(std::fstream& fileStream, ExercisePlan& plan);
	void loadWeeklyPlan(std::fstream& fileStream, ExerciseList& weeklyPlan);
	void displayDailyPlan(DietListNode* node);
	void displayDailyPlan(ExerciseListNode* node);
	void displayWeeklyPlan(DietList& list);
	void displayWeeklyPlan(ExerciseList& list);
	void storeDailyPlan(std::fstream& fOut, DietListNode* node);
	void storeDailyPlan(std::fstream& fOut, ExerciseListNode* node);
	void storeWeeklyPlan(std::fstream& fOut, DietList &list);
	void storeWeeklyPlan(std::fstream& fOut, ExerciseList &list);
	int getRecordToSearch(int dietOrExercise);



};

int isNumber(char str[]);


