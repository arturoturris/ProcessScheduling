#include "PrintableBox.h"

PrintableBox::PrintableBox(std::string _title) : title(_title),slotSize(NULL),symbol('-'){
	width = strlen(title.c_str());
}

void PrintableBox::addSubtitle(std::string _subtitle){
	if(subtitles.size() == 0){
		width = 0;
	}

	subtitles.push_back(_subtitle);
}

void PrintableBox::calculateSlotSizes(){
	if(slotSize != NULL)
		delete slotSize;
	
	slotSize = new int[subtitles.size()];
	
	int i = 0;
	for(std::list<std::string>::iterator it = subtitles.begin(); it != subtitles.end(); ++it){
		slotSize[i] = strlen((*it).c_str());
		width += slotSize[i];
		i++;
	}
	
	width += subtitles.size() + 1;
}

void PrintableBox::printSeparation(){
	for(int i=0;i<width;i++)
		std::cout << symbol;
	std::cout << std::endl;
}

void PrintableBox::printTitle(){
	for(int i=0;i<=width;i++){
		if(i == 0 || i == width)
			std::cout << "|";
		else if(i == 1){
			std::cout << title;
			i += strlen(title.c_str());
		}
		else
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PrintableBox::printSubtitles(){
	std::list<std::string>::iterator it = subtitles.begin();
	for(int i=0;i<=width;i++){
		if(i == 0 || i == width)
			std::cout << "|";
		else{
			std::cout << (*it) << "|";
			i += strlen((*it).c_str()) +1;
			++it;
		}
	}

	std::cout << std::endl;
}

void PrintableBox::printValues(){
}

void PrintableBox::printBox(){
	calculateSlotSizes();

	//SUPERIOR LINE
	printSeparation();
	printTitle();
	printSeparation();
	printSubtitles();
	//INFERIOR LINE
	printSeparation();
}

int* PrintableBox::SlotSize() const{
	return slotSize;}
	
int PrintableBox::Width() const{
	return width;}

int PrintableBox::numOfSubtitles() const{
	return subtitles.size();}

void PrintableBox::printParameter(int index,int _parameter){
	//LENGHT OF PARAMETER
	//WARNING: THIS ONLY WORKS FOR "int type"
	char buffer[32];
	int parameterLenght =  sprintf(buffer, "%d",_parameter);
	
	std::cout << _parameter;
	
	for(int i=0;i<slotSize[index]-parameterLenght;i++){
		std::cout << " ";
	}
	
	std::cout << "|";
}

std::string PrintableBox::intToString(int _parameter){
	 std::ostringstream ss;
     ss << _parameter;
     return ss.str();
}

void PrintableBox::printBlankLine(int _startFromIndex){
	for(int i=_startFromIndex;i<subtitles.size();i++){
		for(int j=0;j<slotSize[i];j++){
			std::cout << " ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;
}

void PrintableBox::printByRows(){
	int topWidth = strlen(title.c_str());
	
	for(std::list<std::string>::iterator it = subtitles.begin(); it != subtitles.end(); ++it){
		if(strlen((*it).c_str()) > topWidth)
			topWidth = strlen((*it).c_str());
	}
	
	width = topWidth+2;
	
	printSeparation();
	printTitle();
	printSeparation();
	
	int charPrinted = 0;
	for(std::list<std::string>::iterator it = subtitles.begin(); it != subtitles.end(); ++it){
		charPrinted = 0;
		std::cout << "|";
		charPrinted += 1;
		std::cout << (*it);
		charPrinted += strlen((*it).c_str());
		
		for(int i=charPrinted;i<width-1;i++){
			std::cout << " ";
		}
		
		std::cout << "|\n";
	}
	
	printSeparation();
	std::cout << std::endl;
}

PrintableBox::~PrintableBox(){
	if(slotSize != NULL)
		delete slotSize;
}
