#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

namespace fs = std::filesystem;
map<string, string> fileToFolder; // {.jpg, "G:/Images"}

void readSettings(ifstream &file)
{
	string line;
	while(getline(file,line))
	{
		string ext = "";
		string path = "";

		//start parsing
		int i = 0;
		while(line[i] != ':')
		{
			ext += line[i];
			i++;
		}

		i++;
		for(i; i < line.size(); i++)
			path += line[i];


		fileToFolder[ext] = path;

	}

}


//given a path, find the extension of the file..
string getExtension(string s)
{
	string ret = "";
	int right = s.size() - 1;
	int curr = right;

	while(s[curr] != '.' && curr >= 0)
	{
		ret = s[curr] + ret;
		curr--;
	}

	return ret;
}

//if a file is a folder, make a best guess on where to
//put the file
string determineFolderLocation(string folderDirectory)
{
	string ret = "pdf";
	map<string,int> counts;

	for(const auto &currFile : fs::directory_iterator(folderDirectory))
	{
		string ext = getExtension(currFile.path().string());
		if(fileToFolder.find(ext) == fileToFolder.end())
		{
			continue;
		}
		counts[ext]++;
	}

	int maxVal = 0;
	string max;
	for(auto keyValue : counts)
	{
		if (keyValue.second > maxVal)
		{
			maxVal = keyValue.second;
			max = keyValue.first;
			ret =max;
		}
	}


	return ret;

}


int main()
{
	//what directory should we sort?
	string sortThisDirectory = "";
	cout << "Enter a directory to organize (e.g. C:/Users/Carlos/Documents/): " << endl;

	cin >> sortThisDirectory;

	sortThisDirectory = "C:/Users/Carlos/Pictures/m2/";

	cout << endl << "SORTING DIRECTORY -> " << sortThisDirectory << endl << endl;
	cout << flush;
	

	//this file determines which bin/folder each file would fall into
	ifstream settings_file("settings.txt");

	//error handling
	if(!settings_file.is_open())
	{
		cerr << "Failed to open the file!" << endl;
		return 1;
	}

	readSettings(settings_file);


	for(const auto &currFile : fs::directory_iterator(sortThisDirectory))
	{
		string fileType;
		if(currFile.is_directory()) //this file is a directory, lets try to guess where to put this folder
		{
			fileType = determineFolderLocation(currFile.path().string());
		}
		else //this is a normal file. extract the extension and fild the appropriate corresponding folder
		{
			fileType = getExtension(currFile.path().string());
		}

		if(fileToFolder.find(fileType) == fileToFolder.end()) //this extension was not listed in the settings!
		{
			auto it = fileToFolder.begin(); //just put it in a random folder for now.
			fileType = it->first;
		}

		string destinationDir = fileToFolder[fileType] + "/" + currFile.path().filename().string();

		fs::copy(currFile.path(), destinationDir);
	}

	
	


	return 0;
}



