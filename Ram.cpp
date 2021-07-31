#include "Ram.h"

Ram::Ram(int _capacity):
	capacity(_capacity),
	freeSpace(_capacity){
}

//THIS VARIABLE CONTAINS ALL PROCESSES THAT WILL EXIT IN THE EXECUTION
//THE VARIABLE COULD BE VIEW AS A "FILE" THAT CONTAINS THE PROCESSES
std::list<Process*>& Ram::AllProcesses(){
	return allProcesses;}
	
//THIS VARIABLE CONTAINS THE PROCESSES THAT ARE CREATED DURING AND BEFORE AN "X" UNIT OF EXECUTION
std::list<Process*>& Ram::CreatedProcesses(){
	return createdProcesses;}

//THIS VARIABLE CONTAINS THE PROCESSES THAT ARE WAINTING TO RETURN TO THE "createdProcesses" VARIABLE
//THE QUEUE WILL BE EMPTIED WHEN THERE ARE NO MORE PROCESSES IN THE "createdProcess" VARIABLE
std::list<Process*>& Ram::QueueOfProcesses(){
	return queueOfProcesses;}
	
//THIS VARIABLE CONTAINS ALL THE PROCESSES THAT HAVE ALREADY BEING PROCESSED COMPLETELY
std::list<Process>& Ram::ProcessRecord(){
	return processRecord;}
	
void Ram::createNProcesses(int numProcessesToCreate){
	for(int i=0;i<numProcessesToCreate;i++){
		allProcesses.push_back(new Process(i,2,3,0,3));
	}
}
void Ram::addProcessToList(Process* p){
	allProcesses.push_back(p);
}

void Ram::deleteProcessToList(int _pid){
	for(std::list<Process*>::iterator it = allProcesses.begin(); it != allProcesses.end(); it++){
		if((*it)->Pid() == _pid){
			Process* p = *it;
			allProcesses.erase(it);
			delete p;
			break;
		}
			
	}
}

void Ram::createCustomProcesses(){
	/*
	allProcesses.push_back(new Process(1,0,2,5,7));
	allProcesses.push_back(new Process(2,0,2,4,2));
	allProcesses.push_back(new Process(3,0,1,3,4));
	allProcesses.push_back(new Process(4,0,2,2,5));
	allProcesses.push_back(new Process(5,2,3,3,6));
	allProcesses.push_back(new Process(6,3,2,2,8));
	allProcesses.push_back(new Process(7,2,1,4,9));
	allProcesses.push_back(new Process(8,3,2,3,10));
	allProcesses.push_back(new Process(9,4,2,4,2));
	allProcesses.push_back(new Process(10,3,1,2,7));
	*/
	
	allProcesses.push_back(new Process(1,0,1,2,1));
	allProcesses.push_back(new Process(2,3,3,1,1));
	allProcesses.push_back(new Process(3,5,4,3,1));
	allProcesses.push_back(new Process(4,6,1,2,1));
	allProcesses.push_back(new Process(5,2,2,2,1));
	allProcesses.push_back(new Process(6,4,3,2,1));
	allProcesses.push_back(new Process(7,4,1,1,1));
	allProcesses.push_back(new Process(8,7,1,1,1));
	allProcesses.push_back(new Process(9,4,5,2,1));
	allProcesses.push_back(new Process(10,3,2,1,1));
	allProcesses.push_back(new Process(11,0,1,4,1));
}

void Ram::printAllProcesses(){
	int index = 0;
	
	PrintableBox box1("PROCESSES TO EXECUTE");
	box1.addSubtitle("PID");
	box1.addSubtitle("Arr");
	box1.addSubtitle("Exe");
	box1.addSubtitle("Exed");
	box1.addSubtitle("Prio");
	box1.addSubtitle("RAM");
	box1.addSubtitle("Lea");
	box1.printBox();
	
	for(std::list<Process*>::iterator it = allProcesses.begin(); it != allProcesses.end(); ++it){
		index = 0;
		std::cout << "|";
		box1.printParameter(index++,(*it)->Pid());
		box1.printParameter(index++,(*it)->ArrivalTime());
		box1.printParameter(index++,(*it)->ExecutionTime());
		box1.printParameter(index++,(*it)->ExecutedTime());
		box1.printParameter(index++,(*it)->Priority());
		box1.printParameter(index++,(*it)->RamSpace());
		box1.printParameter(index++,(*it)->LeaveTime());
		std::cout << std::endl;
	}
	
	box1.printSeparation();
	std::cout << std::endl;
}
