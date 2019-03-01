// Conve by Kajetan Krawczyk. Copyright (C) 2019, kajtekjestem.pl
// Released under Creative Commons BY-NC-SA 4.0 license.
//
// Featuring LibXL library FREE version. Grab it now at http://www.libxl.com/home.html
//
// Check README and LICENSE file for more information.

// #include "stdafx.h"
#include <Windows.h>
#include "inc\libxl.h"
#include <iostream>
#include <io.h>
#include <stdio.h>
#include <fstream>

// A few macros to make life easier.
#define msg(str) std::cout << str
#define msgl(str) std::cout << str << endl
#define endl std::endl

#define field1 30
#define field2 16

bool Assign(char *path, char *name);
void ParseFolder(const char *path);
const wchar_t *GetWC(const char *c);

int succ = 0; // heh
int errors = 0;

int main(int argc, char* argv[])
{
	msgl("Conve by Kajtek, Copyright (C) 2019, kajtekjestem.pl");

	// no args:
	if (argc == 1) {
		msg("Usage:");
		msgl(" conve.exe \"path\"");
		return 0;
	}

	// args:
	char *arg2 = argv[1];
	char pt[1024];
	sprintf_s(pt, "%s/*", arg2);

	_finddata_t data;
	int ff = _findfirst(pt, &data);

	// do:
	msgl(" ");
	msgl("Filename                      Header          Verdict         Status");
	msgl("==============================================================================");

	if (ff != -1)
	{
		int res = 0;
		char *s;
		while (res != -1)
		{
			res = _findnext(ff, &data);
			s = data.name;
			char  stary[1024];
			sprintf_s(stary, "%s/%s", arg2, s);

			// only if this file has no ext
			if (!strstr(s, ".")) { 
				Assign(stary, s);
			}
		}
	}

	std::cout << "\r                                                          " << endl;
	msgl(" ");
	msgl("Done!");
	msgl("Successful operations: " << succ);
	if(errors - 1 == -1) msgl("Errors: 0");
	else { msgl("Errors: " << errors - 1); }
	return 0;
}

void ParseFolder(const char* path) {
	_finddata_t data;
	char pt[1024];
	sprintf_s(pt, "%s/*", path);
	int ff = _findfirst(pt, &data);

	if (ff != -1)
	{
		int res = 0;
		char *s;
		while (res != -1)
		{
			res = _findnext(ff, &data);
			s = data.name;
			char  stary[1024];
			sprintf_s(stary, "%s/%s", path, s);

			// only if this file has no ext
			if (!strstr(s, ".")) {
				Assign(stary, s);
			}
		}
	}
}

bool Assign(char *path, char *name) {
	msg(name);
	std::ifstream file(path);
	int miejsce = field1 - strlen(name);
	if (miejsce < 0) miejsce = 0;

	if (!file) { 
		for (size_t i = 0; i < miejsce; i++) {
			msg(" ");
		}
		msgl("DIRECTORY                       EXPANDING"); 
		ParseFolder(path);
		return 0; 
	}

	std::string contents((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	std::string sub = contents.substr(0, 8);
	const char *c = sub.c_str();

	for (size_t i = 0; i < miejsce; i++) {
		msg(" ");
	}

	if (miejsce == 0) {
		std::string cs(c);
		cs = cs.substr(0, field1);
	}
	msg(c);

	bool doc, xls, docx, xlsx;
	doc = xls = docx = xlsx = false;

	bool pdf = strstr(c, "PDF");
	bool jpg = (c[0] == -1 && c[1] == -40 && c[2] == -1);
	bool docxls = (c[0] == -48 && c[1] == -49 && c[2] == 17);
	bool docxxlsx = (c[0] == 80 && c[1] == 75 && c[2] == 3);

	if (docxls) {
		libxl::Book* book = xlCreateBook();
		xls = book->load(GetWC(path));
		if (!xls) doc = true;
	}

	if (docxxlsx) {
		libxl::Book* book = xlCreateXMLBook();
		xlsx = book->load(GetWC(path));
		if (!xlsx) docx = true;
	}






	int miejsce2 = field2 - strlen(c);
	for (size_t i = 0; i < miejsce2; i++) {
		msg(" ");
	}

	const char* ext = "";
	if (pdf) { 
		msg("PDF");
		ext = "pdf";
	}
	else if (jpg) {
		msg("JPG");
		ext = "jpg";
	}
	else if (doc) {
		msg("DOC");
		ext = "doc";
	}
	else if (xls) {
		msg("XLS");
		ext = "xls";
	}
	else if (docx) {
		msg("DOCX");
		ext = "docx";
	}
	else if (xlsx) {
		msg("XLSX");
		ext = "xlsx";
	}
	else msg( "---" );

	char nowy[1024]; // is it safe?
	char stary[1024]; // -||-
	sprintf_s(nowy, "%s.%s", path, ext);
	sprintf_s(stary, "%s", path);
	file.close(); // important!!!!!!!!!!!
	int r = rename(path, nowy);

	int miejsce3 = field2 - strlen(ext);
	for (size_t i = 0; i < miejsce3; i++) {
		msg(" ");
	}

	if (!r) {
		msgl("OK");
		succ++;
	}
	#pragma warning (disable : 4996)
	else {
		msgl("ERROR CODE: " << r);
		errors++;
	}

	return 1;
}



const wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];

	#pragma warning (disable : 4996)
	mbstowcs(wc, c, cSize);

	return wc;
}