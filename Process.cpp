#include "Process.h"

Process::Process(int _pid,int _arrival,int _executionTime,int _priority,int _ramSpace):
	pid(_pid),
	arrivalTime(_arrival),
	executionTime(_executionTime),
	executedTime(0),
	priority(_priority),
	ramSpace(_ramSpace),
	leaveTime(-1)
{

}

int Process::getRandomPid(){
	srand(time(NULL));
	std::cout << "Random number: " << rand() << std::endl;
}

int Process::getRandomArrival(){
}

int Process::getRandomExecutionTime(){
}

int Process::getRandomPriority(){
}

int Process::getRandomRamSpace(){
}

int Process::Pid() const{
	return pid;}

int Process::ArrivalTime() const{
	return arrivalTime;}
	
int Process::ExecutionTime() const{
	return executionTime;}

int Process::ExecutedTime() const{
	return executedTime;}
	
int Process::Priority() const{
	return priority;}
	
int Process::RamSpace() const{
	return ramSpace;}
	
int Process::LeaveTime() const{
	return leaveTime;}
	
int Process::timeLeft() const{
	return executionTime-executedTime;}
	
int Process::waitTime() const{
	return leaveTime - arrivalTime - executionTime;}

void Process::setLeaveTime(int _leaveTime){
	leaveTime = _leaveTime;}

void Process::printProcess() const{
	/*std::cout << "Pid: " << pid << std::endl;
	std::cout << "Arrival Time: " << arrivalTime << std::endl;
	std::cout << "Execution Time: " << executionTime << std::endl;
	std::cout << "Executed Time: " << executedTime << std::endl;
	std::cout << "Priority: " << priority << std::endl;
	std::cout << "Ram Space: " << ramSpace << std::endl;
	std::cout << "Leave Time: " << leaveTime << std::endl;*/
	std::cout << pid << "\t";
	std::cout << arrivalTime << "\t";
	std::cout << executionTime << "\t";
	std::cout << executedTime << "\t";
	std::cout << priority << "\t";
	std::cout << ramSpace << "\t";
	std::cout << leaveTime;
}

//THE COMPARISON EVALUEATE IF "p1" IS LESSER THAN "p2"
//RETURN 1 IN CASE "p1" < "p2"
//RETURN 0 IN CASE "p1" > "p2"
//RETURN -1 IN CASE "p1" = "p2"
int Process::lesserPid(const Process &p1,const Process &p2){
	if(p1.pid < p2.pid)
		return 1;
	else if(p1.pid > p2.pid)
		return 0;
	else
		return -1;
}

int Process::lesserExecutionTime(const Process &p1,const Process &p2){
	if(p1.executionTime < p2.executionTime)
		return 1;
	else if(p1.executionTime > p2.executionTime)
		return 0;
	else
		return -1;
}

int Process::lesserPriority(const Process &p1,const Process &p2){
	if(p1.priority > p2.priority)
		return 1;
	else if(p1.priority < p2.priority)
		return 0;
	else
		return -1;
}

//THE COMPARISON EVALUEATE IF "p1" IS GREATER THAN "p2"
//RETURN 1 IN CASE "p1" > "p2"
//RETURN 0 IN CASE "p1" < "p2"
//RETURN -1 IN CASE "p1" = "p2"
int Process::greaterPid(const Process &p1,const Process &p2){
	if(p1.pid > p2.pid)
		return 1;
	else if(p1.pid < p2.pid)
		return 0;
	else
		return -1;
}

int Process::greaterExecutionTime(const Process &p1,const Process &p2){
	if(p1.executionTime > p2.executionTime)
		return 1;
	else if(p1.executionTime < p2.executionTime)
		return 0;
	else
		return -1;
}

int Process::greaterPriority(const Process &p1,const Process &p2){
	if(p1.priority < p2.priority)
		return 1;
	else if(p1.priority > p2.priority)
		return 0;
	else
		return -1;
}

std::string Process::getNameOfCriteria(int (*fn)(const Process&,const Process&)){
	if(fn == &lesserPid)
		return "PID (ASC)";
	else if(fn == &lesserExecutionTime)
		return "Execution Time (LOW)";
	else if(fn == &lesserPriority)
		return "Priority (HIGH)";
	else if(fn == &greaterPid)
		return "PID (DES)";
	else if(fn == &greaterExecutionTime)
		return "Execution Time (HIGH)";
	else
		return "Priority (LOW)";
}

Process::~Process(){
}
