#pragma once
#include <iostream>
#include <list>
#include "Process.h"
#include "Processor.h"
#include "PrintableBox.h"

class Ram{
	private:
		int capacity;
		int freeSpace;
		std::list<Process*> allProcesses;
		std::list<Process*> createdProcesses;
		std::list<Process*> queueOfProcesses;
		std::list<Process> processRecord;
	public:
		Ram(int _capacity);
		std::list<Process*>& AllProcesses();
		std::list<Process*>& CreatedProcesses();
		std::list<Process*>& QueueOfProcesses();
		std::list<Process>& ProcessRecord();
		void addProcessToList(Process* p);
		void deleteProcessToList(int _pid);
		void createNProcesses(int numProcessesToCreate);
		void createCustomProcesses();
		void printAllProcesses();
};
