#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <cstdio>
#include <sstream>

class PrintableBox{
	private:
		std::string title;
		std::list<std::string> subtitles;
		int width;
		char symbol;
		int *slotSize;
	public:
		PrintableBox(std::string _title);
		void addSubtitle(std::string _subtitle);
		private: void calculateSlotSizes();
		public: void printSeparation();
		private: void printTitle();
		private: void printSubtitles();
		private: void printValues();
		public: void printBox();
		int* SlotSize() const;
		int Width() const;
		int numOfSubtitles() const;
		void printParameter(int _parameter,int size);
		static std::string intToString(int _parameter);
		void printBlankLine(int _startFromIndex);
		void printByRows();
		public: ~PrintableBox();
};
