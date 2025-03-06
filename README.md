# File-Sorter

Program that goes through files in a directory and moves each file and subfolder to a designated folder for each file type.

How to use:

- Set up settings.txt
  + for a given file extension, determine where you want those files to go (e.g. mp3 should go to my music folder)
  + to add this to the file correctly it is formated like so: "mp3:G:/Music" (no quotation marks)
  + repeat this step for every file type that you want to support

- Compile 'fileReader.cpp'
- Run the program.
- When prompted enter the directory that you want to sort (in the format C:/Users/Carlos/Documents/)
  + Forward slashes are very important
- The program will go through each file in the directory and determine its new location based on the settings.txt file.
- Files will be copied to the new location.
