#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <string.h>
#include "Process.h"
#include "PrintableBox.h"

//DEFINING A VARIABLE "FncComp" OF FUNCTION TYPE
//THIS TYPE IS THE SAME AS COMPARISON FUNCTION IN "Process.h"
typedef int (*FncComp)(const Process&,const Process&);

//ARRAY OF 3 FUNCTIONS THAT ARE USED TO COMPARE THE PROCESSES WITH THE FUNCTION "compareByCriteria"
//THE GLOBAL VARIABLE IS BECAUSE IN STATIC FUNCTIONS WE CANNOT ACCESS MEMBER VARIABLES, SO
//I DEFINED OUT THE CRITERIA TO USE "list::sort()" WITH NO PROBLEMS
//THE VARIABLE IS MADE EXTERN TO AVOID REDUNDANCY, DECLARATION WILL BE MADE AT MAIN FILE
extern FncComp criteria[3];

class Processor{
	private:
		bool multiTask;
		bool multiProcess;
		int numChannels;
		int ram;
		int freeSpace;
		int executionUnit;
		Process **channels;
		std::list<Process*> *processes;
		std::list<Process*> *queue;
		std::list<Process> *processRecord;
	public:
		Processor(bool _multiTask,bool _multiProcess,int _numChannels,int _ram);
		int ExecutionUnit() const;
		void printProcessor() const;
		void printChannels() const;
		void printProcessRecord() const;
		void printCriteria() const;
		void setCriteria();
		void setProcessesList(std::list<Process*>* _processes);
		void setQueue(std::list<Process*>* _queue);
		void setProcessRecord(std::list<Process>* _processRecord);
		void execute();
		int assignProcessesToChannels();
		int processChannels();
		void vacateChannels();
		void vacateQueue();
		void sendFinishedProcessToRecord(Process *p);
		static bool compareByCriteria(const Process *p1,const Process *p2);
		int sizeOfProcessRecord() const;
		float waitTimeOfAlgorithm();
		void reiniciarP();
		~Processor();
};
