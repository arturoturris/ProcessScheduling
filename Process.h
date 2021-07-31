#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#define maxArrival 7
#define maxExecution 10
#define maxRamSpace 5

enum PRIORITY{HIGH=1,MEDIUM_HIGH,MEDIUM,MEDIUM_LOW,LOW};

class Process{
	private:
		int pid;
		int arrivalTime;
		int executionTime;
		int executedTime;
		int priority;
		int ramSpace;
		int leaveTime;
	public:
		Process(int _pid,int _arrivalTime,int _executionTime,int _priority,int _ramSpace);
		int Pid() const;
		int ArrivalTime() const;
		int ExecutionTime() const;
		int ExecutedTime() const;
		int Priority() const;
		int RamSpace() const;
		int LeaveTime() const;
		int timeLeft() const;
		int waitTime() const;
		void setLeaveTime(int _leaveTime);
		int getRandomPid();
		int getRandomArrival();
		int getRandomExecutionTime();
		int getRandomPriority();
		int getRandomRamSpace();
		void printProcess() const;
		static int lesserPid(const Process &p1,const Process &p2);
		static int lesserExecutionTime(const Process &p1,const Process &p2);
		static int lesserPriority(const Process &p1,const Process &p2);
		static int greaterPid(const Process &p1,const Process &p2);
		static int greaterExecutionTime(const Process &p1,const Process &p2);
		static int greaterPriority(const Process &p1,const Process &p2);
		static std::string getNameOfCriteria(int (*fn)(const Process&,const Process&));
		~Process();
		friend class Processor;
};
