#include <iostream>
#include "Processor.h"
#include "Process.h"
#include "Ram.h"
#include "PrintableBox.h"

#define log(x) std::cout << x << std::endl

//CRITERIA FOR SORTING PROCESSES
//SEE "Processor.h" FOR MORE INFORMATION
FncComp criteria[3];

int main(){
	
	//DEFINING OBJECTS
	Processor *p = new Processor(true,true,2,10);
	Ram ram1(256);
	
	p->setQueue(&(ram1.QueueOfProcesses()));
	p->setProcessRecord(&(ram1.ProcessRecord()));
	p->setProcessesList(&(ram1.CreatedProcesses()));

	//LEER DESDE UN ARCHIVO*********
	ram1.createCustomProcesses();
	//******************************

	//INITIALIZING CRITERIA, THESE WILL BE CHANGED DURING EXECUTION
	::criteria[0] = &Process::greaterPriority;
	::criteria[1] = &Process::lesserExecutionTime;
	::criteria[2] = &Process::lesserPid;
	
	//NUMBER OF PROCESSES TO BE EXECUTED
	//THIS VARIABLE DEPENDS ON HOW MANY PROCESSES WERE DEFINED IN "ram.allProcesses"
	int totalProcesses = 0;
	int opt = 0;
	enum OPTIONS{EXIT=-1,ADD_PROCESS=1,DELETE_PROCESS,CHANGE_PROCESSOR,CHANGE_CRITERIA,START_EXECUTION};
	
	do{
		system("cls");
		std::cout << "* * * * * PROCESS SCHEDULER * * * * * \n" << std::endl;
		p->printProcessor();
		p->printCriteria();
		ram1.printAllProcesses();
		
		std::cout << "1) Add process" << std::endl;
		std::cout << "2) Delete process" << std::endl;
		std::cout << "3) Change processor parameters" << std::endl;
		std::cout << "4) Change selection criteria" << std::endl;
		std::cout << "5) Start execution" << std::endl;
		std::cout << "6) Exit" << std::endl;
		std::cout << "\nOption: ";
		std::cin >> opt;
		
		switch(opt){
			case ADD_PROCESS:{
				int pid,ram,executionTime,priority,arrival;
				
				std::cout << "PROCESS TO INSERT\n";
				std::cout << "PID(n): ";
				std::cin >> pid;
				std::cout << "Arrival time(0-n):";
				std::cin >> arrival;
				std::cout << "Time of execution(0-n): ";
				std::cin >> executionTime;
				std::cout << "Priority(0-4): ";
				std::cin >> priority;
				std::cout << "RAM(1-n): ";
				std::cin >> ram;
				Process *p1 = new Process(pid,arrival,executionTime,priority,ram);
				
				ram1.addProcessToList(p1);
				
				break;
			}
			
			case DELETE_PROCESS:{
				int pid;
				
				std::cout << "PROCESS TO BE KILLED\n";
				std::cout << "PID(n):";
				std::cin >> pid;
				
				ram1.deleteProcessToList(pid);
				
				break;
			}
			
			case CHANGE_PROCESSOR:{
				int ncanales,nram,mt,mp;
				bool multitarea,multiproceso;
				
				system("cls");
				p->printProcessor();
				delete p;
				
				std::cout << "Multi-process: " << std::endl;
				std::cout << "1) Yes \t2) No \nOption:";
				std::cin >> mp;
				(mp == 1?  multiproceso=true: multiproceso=false);
				std::cout << "Multi-task:" << std::endl;
				std::cout << "1) Yes \t2) No \nOption:";
				std::cin >> mt;
				(mt == 1?  multitarea=true: multitarea=false);
				
				if(multiproceso){
					std::cout << "Number of channels: ";
					std::cin >> ncanales;
				}
				else{
					ncanales = 1;
				}
				std::cout << "RAM size: ";
				std::cin >> nram;
				
				p = new Processor(multitarea,multiproceso,ncanales,nram);
				p->setQueue(&(ram1.QueueOfProcesses()));
				p->setProcessRecord(&(ram1.ProcessRecord()));
				p->setProcessesList(&(ram1.CreatedProcesses()));
				
				break;
			}
			
			case CHANGE_CRITERIA:{
				system("cls");
				p->printCriteria();
				std::cout << std::endl;
				p->setCriteria();
				
				break;
			}	
			
			case START_EXECUTION:{
				//CARRING PROCESSES FROM RAM TO PROCESSOR, DEPENDING ON THEIR "arrivalTime"
				totalProcesses = ram1.AllProcesses().size();
				do{
					for(std::list<Process*>::iterator it = ram1.AllProcesses().begin(); it != ram1.AllProcesses().end(); ){
						if((*it)->ArrivalTime() == p->ExecutionUnit()){
							ram1.CreatedProcesses().push_back((*it));
							it = ram1.AllProcesses().erase(it);
						}
						else{
							++it;
						}
					}
					
					p->execute();
				}while(totalProcesses != p->sizeOfProcessRecord());
				
				//PRINTING RESULTS
				p->printProcessRecord();
				std::cout << "Time of algorithm: " << p->waitTimeOfAlgorithm() << std::endl;
				system("pause");
				
				system("cls");
				std::cout << "* * * * * PROCESS SCHEDULER * * * * * \n" << std::endl;
				std::cout << "Restart? \n \t1) Yes \t2) No \nOption: ";
				
				int reiniciar = 0;
				std::cin >> reiniciar;
			
				if(reiniciar == 1)
				{
					ram1.createCustomProcesses();
					p->reiniciarP();
					totalProcesses = 0;
				}
				else
					opt = EXIT;
			
				break;
			} 
			
			case 6:{
				opt = EXIT;
				break;
			}
		};
		
	}while(opt != EXIT);
	
	//DELETING THE PROCESSOR
	delete p;
	
	return 0;
}
