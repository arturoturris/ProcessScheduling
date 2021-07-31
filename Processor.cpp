#include "Processor.h"

Processor::Processor(bool _multiTask,bool _multiProcess,int _numChannels,int _ram) :
	multiTask(_multiTask),
	multiProcess(_multiProcess),
	numChannels(_numChannels),
	ram(_ram),
	freeSpace(ram),
	executionUnit(0),
	channels(NULL),
	processes(NULL),
	queue(NULL),
	processRecord(NULL){
	
	//CREATING EXECUTION CHANNELS
	channels = new Process*[numChannels];
	for(int i=0;i<numChannels;i++){
		channels[i] = NULL;
	}
	
	//SEED FOR RANDOM NUMBERS
	srand(time(NULL));
}

int Processor::ExecutionUnit() const{
	return executionUnit;}

void Processor::printProcessor() const{
	int index = 0;
	
	PrintableBox box1("Processor");
	box1.addSubtitle("Multi-Task");
	box1.addSubtitle("Multi-Process");
	box1.addSubtitle("# Channels");
	box1.addSubtitle("RAM");
	
	box1.printBox();
	std::cout << "|";
	box1.printParameter(index++,multiTask);
	box1.printParameter(index++,multiProcess);
	box1.printParameter(index++,numChannels);
	box1.printParameter(index++,ram);
	std::cout << std::endl;
	box1.printSeparation();
	std::cout << std::endl;
}

void Processor::printChannels() const{
	int index = 0;
	
	std::string title = "UNIT OF EXECUTION: ";
	std::string unit = PrintableBox::intToString(executionUnit);
	
	PrintableBox box1(title+unit);
	box1.addSubtitle("Chan");
	box1.addSubtitle("PID");
	box1.addSubtitle("Arr");
	box1.addSubtitle("Exe");
	box1.addSubtitle("Exed");
	box1.addSubtitle("Pri");
	box1.addSubtitle("Ram");
	box1.addSubtitle("Lea");
	box1.printBox();
	
	for(int i=0;i<numChannels;i++){
		if(channels[i] == NULL){
			std::cout << "|";
			box1.printParameter(0,i);
			box1.printBlankLine(1);
		}
		else{
			index = 0;
			std::cout << "|";
			box1.printParameter(index++,i);
			box1.printParameter(index++,channels[i]->Pid());
			box1.printParameter(index++,channels[i]->ArrivalTime());
			box1.printParameter(index++,channels[i]->ExecutionTime());
			box1.printParameter(index++,channels[i]->ExecutedTime());
			box1.printParameter(index++,channels[i]->Priority());
			box1.printParameter(index++,channels[i]->RamSpace());
			box1.printParameter(index++,channels[i]->LeaveTime());
			std::cout << std::endl;
		}
	}
	
	box1.printSeparation();
	std::cout << std::endl;	
}

void Processor::printProcessRecord() const{
	int index = 0;
	
	PrintableBox box1("PROCESS RECORD");
	box1.addSubtitle("PID");
	box1.addSubtitle("Arr");
	box1.addSubtitle("Exe");
	box1.addSubtitle("Exed");
	box1.addSubtitle("Prio");
	box1.addSubtitle("RAM");
	box1.addSubtitle("Lea");
	box1.addSubtitle("Wait");
	box1.printBox();
	
	for(std::list<Process>::iterator it = processRecord->begin(); it != processRecord->end(); ++it){
		index = 0;
		std::cout << "|";
		box1.printParameter(index++,(*it).Pid());
		box1.printParameter(index++,(*it).ArrivalTime());
		box1.printParameter(index++,(*it).ExecutionTime());
		box1.printParameter(index++,(*it).ExecutedTime());
		box1.printParameter(index++,(*it).Priority());
		box1.printParameter(index++,(*it).RamSpace());
		box1.printParameter(index++,(*it).LeaveTime());
		box1.printParameter(index++,(*it).waitTime());
		std::cout << std::endl;
	}
	
	box1.printSeparation();
	std::cout << std::endl;
}

void Processor::printCriteria() const{
	PrintableBox box1("CRITERIA");
	box1.addSubtitle("1) " + Process::getNameOfCriteria(::criteria[0]));
	box1.addSubtitle("2) " + Process::getNameOfCriteria(::criteria[1]));
	box1.addSubtitle("3) " + Process::getNameOfCriteria(::criteria[2]));
	box1.printByRows();
}

void Processor::setCriteria(){
	int opt = 0;
	
	std::cout << "\n***CHANGE CRITERIA***" << std::endl;
	std::cout << "1) Change position" << std::endl;
	std::cout << "2) Invert Order" << std::endl;
	std::cout << "Option: ";
	std::cin >> opt;
	std::cout << std::endl;
	
	// 1) CHANGE POSITION
	if(opt == 1){
		int pos1,pos2;
		std::cout << "\nOrigin (n): ";
		std::cin >> pos1;
		std::cout << "Destination (n): ";
		std::cin >> pos2;
		
		//VALID VALUE
		if(pos1 >= 1 && pos1 <= 3 && pos2 >=1 && pos2 <= 3){
			pos1--;
			pos2--;
			FncComp aux = ::criteria[pos1];
			::criteria[pos1] = ::criteria[pos2];
			::criteria[pos2] = aux;
		}
	}
	
	else{
		int pos = 0;
		
		std::cout << "Criteria to invert (n): ";
		std::cin >> pos;
		
		//VALID VALUE
		if(pos >= 1 && pos <=3){
			pos--;
			
			if(::criteria[pos] == &Process::lesserPid)
				::criteria[pos] = &Process::greaterPid;
			else if(::criteria[pos] == &Process::greaterPid)
				::criteria[pos] = &Process::lesserPid;
			else if(::criteria[pos] == &Process::lesserExecutionTime)
				::criteria[pos] = &Process::greaterExecutionTime;
			else if(::criteria[pos] == &Process::greaterExecutionTime)
				::criteria[pos] = &Process::lesserExecutionTime;
			else if(::criteria[pos] == &Process::lesserPriority)
				::criteria[pos] = &Process::greaterPriority;
			else
				::criteria[pos] = &Process::lesserPriority;
		}
	}
}

void Processor::setProcessesList(std::list<Process*>* _processes){
	processes = _processes;}

void Processor::setQueue(std::list<Process*>* _queue){
	queue = _queue;}

void Processor::setProcessRecord(std::list<Process>* _processRecord){
	processRecord = _processRecord;}

void Processor::execute(){
	processes->sort(Processor::compareByCriteria);
	assignProcessesToChannels();
	printChannels();
	processChannels();
	vacateChannels();
	vacateQueue();
	executionUnit+=1;
}

int Processor::assignProcessesToChannels(){
	int channelsAssinged = 0;
	//FLAG TO NOT REPEAT THE ASSIGNING IF THE PROCESSES ARE TOO BIG FOR THE AVAILABLE RAM
	bool processesExcedRam = false;
	
	for(int i=0;i<numChannels;i++){
		if(processesExcedRam)
			break;
		
		//CHANNEL OCCUPIED
		if(channels[i] != NULL){
			channelsAssinged++;
			continue;
		}
		
		//SEARCH FOR A PROCESS TO SET INTO THE CHANNEL
		for(std::list<Process*>::iterator it = processes->begin(); it != processes->end(); ++it){	
		//SET PROCESS TO CHANNEL IF THERE'S ENOUGH SPACE
			if((*it)->RamSpace() <= freeSpace){
				channels[i] = (*it);
				freeSpace -= (*it)->RamSpace();
				channelsAssinged++;
				processes->erase(it);
				break;
			}
			
			if(it == processes->end())
				processesExcedRam = true;
		}
	}
	
	return channelsAssinged;
}

int Processor::processChannels(){
	int processedChannels = 0;
	
	for(int i=0;i<numChannels;i++){
		if(channels[i] == NULL)
			continue;
			
		channels[i]->executedTime += 1;
		processedChannels+=1;
	}
	
	return processedChannels;
}

void Processor::vacateChannels(){
	//THERE ARE 4 CASES 
	
	// MONO-PROCESS
	if(multiProcess == false){
		// MONO-TASK
		if(multiTask == false){
			if(channels[0] == NULL)
				return;
				
			//THE PROCESS HASN'T FINISHED
			if(channels[0]->timeLeft() > 0){
				//THE PROCESS NEED TO CONTINUE IN THE CHANNEL
			}
			//THE PROCESS HAS FINISHED
			else{
				channels[0]->setLeaveTime(executionUnit+1);
				sendFinishedProcessToRecord(channels[0]);
				freeSpace += channels[0]->RamSpace();
				delete channels[0];
				channels[0] = NULL;
			}
		}
		
		// MULTI-TASK
		else if(multiTask == true){
			//THERE'S A PROCESS IN THE CHANNEL 0
			if(channels[0] != NULL){
				freeSpace += channels[0]->RamSpace();
				
				//CHECK IF THE ACTUAL PROCESS HAS FINISHED
				if(channels[0]->ExecutionTime() == channels[0]->ExecutedTime()){
					channels[0]->setLeaveTime(executionUnit+1);
					sendFinishedProcessToRecord(channels[0]);
					delete channels[0];
					channels[0] = NULL;
				}
				
				//THE ACTUAL PROCESS HASN'T FINISHED
				else{
					queue->push_back(channels[0]);
					channels[0] = NULL;
				}
			}
		}
	}
	
	//MULTI-PROCESS
	else if(multiProcess == true){
		// MONO-TASK
		if(multiTask == false){
			for(int i=0;i<numChannels;i++){
				if(channels[i] == NULL)
					continue;
				
				//THE PROCESS HAS FINISHED
				if(channels[i]->ExecutionTime() == channels[i]->ExecutedTime()){
					freeSpace += channels[i]->RamSpace();
					channels[i]->setLeaveTime(executionUnit+1);
					sendFinishedProcessToRecord(channels[i]);
					delete channels[i];
					channels[i] = NULL;
				}
				
				//IF THE PROCESS HASN'T FINISHED IT NEEDS TO CONTINUE IN THE CHANNEL
			}
		}
		
		// MULTI-TASK
		else if(multiTask == true){
			for(int i=0;i<numChannels;i++){
				//THE CHANNEL IS EMPTY
				if(channels[i] == NULL)
					continue;
					
				//CHECK IF THE PROCESS HAS FINISHED
				if(channels[i]->ExecutionTime() == channels[i]->ExecutedTime()){
					freeSpace += channels[i]->RamSpace();
					channels[i]->setLeaveTime(executionUnit+1);
					sendFinishedProcessToRecord(channels[i]);
					delete channels[i];
					channels[i] = NULL;
				}
				
				//THE PROCESS HASN'T FINISHED AND NEEDS TO BE PUTED IN THE QUEUE
				else{
					freeSpace += channels[i]->RamSpace();
					queue->push_back(channels[i]);
					channels[i] = NULL;
				}
			}
		}
	}
}

void Processor::vacateQueue(){
	//VACATE QUEUE TO PROCESSES LIST WHEN THERE'S NOTHING IN "proccesses" AND THERE'S AT LEAST 1 ELEMENT IN "queue"
	if(processes->begin() == processes->end()){
		if(queue->begin() != queue->end()){
			for(std::list<Process*>::iterator it = queue->begin(); it != queue->end(); ++it){
				processes->push_back((*it));
			}
			queue->clear();
		}
	}
}

void Processor::sendFinishedProcessToRecord(Process *p){
	processRecord->push_back(*p);}

bool Processor::compareByCriteria(const Process *p1,const Process *p2){	
	FncComp fnc1,fnc2,fnc3;
	
	fnc1 = criteria[0];
	fnc2 = criteria[1];
	fnc3 = criteria[2];
	
	//EVALUATING
	//FIRST CRITERIA
	// "p1.parameter" < "p2.parameter"
	if(fnc1(*p1,*p2) == 1)
		return true;
	// "p1.parameter" > "p2.parameter"
	else if(fnc1(*p1,*p2) == 0)
		return false;
	// "p1.parameter" = "p2.parameter"
	else{
		//SECOND CRITERIA
		// "p1.parameter" < "p2.parameter"
		if(fnc2(*p1,*p2) == 1)
			return true;
		// "p1.parameter" > "p2.parameter"
		else if(fnc2(*p1,*p2) == 0)
			return false;
		// "p1.parameter" = "p2.parameter"
		else{
			//THIRD CRITERIA
			// "p1.parameter" < "p2.parameter"
			if(fnc3(*p1,*p2) == 1)
				return true;
			// "p1.parameter" > "p2.parameter"
			else
				return false;
		}
	}
}

int Processor::sizeOfProcessRecord() const{
	return processRecord->size();}

float Processor::waitTimeOfAlgorithm(){
	float totalWaitTime = 0;
	
	for(std::list<Process>::iterator it = processRecord->begin(); it != processRecord->end(); ++it){
		totalWaitTime += (*it).waitTime();
	}
	
	return totalWaitTime/processRecord->size();
}
void Processor::reiniciarP()
{
	this->executionUnit = 0;
	this->processes->clear();
	this->queue->clear();
	this->processRecord->clear();
}
Processor::~Processor(){
	delete []channels;
}
