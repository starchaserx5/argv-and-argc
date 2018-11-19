#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void transferToCPPString(string* &list, int qty, char* input[]);
void display(string *list, int qty, string &input, string &output);
void displayFileNames(string &input, string &output);
void editedTextFunc(ifstream &inStream, ofstream &outStream, string &input, string &output);
bool checkFile(ifstream &inStream, ofstream &outStream);
bool overwriteFile(ofstream &outStream, string &output, string *list, int qty);
bool appendFile(ofstream &outStream, string &output, string *list, int qty);

int main(int argc, char* argv[])
{
    ifstream inStream;
    ofstream outStream;
    string *list, input, output;
    bool append, overwrite;

    transferToCPPString(list, argc, argv);
    display(list, argc, input, output);
    displayFileNames(input,output);
    editedTextFunc(inStream, outStream, input, output);
    overwrite = overwriteFile(outStream, output, list, argc);
    append = appendFile(outStream, output, list, argc);

    if(!(append || overwrite))
    {
        cout << "Error: This file already exists" << endl;
    }

    return 0;
}

void transferToCPPString(string* &list, int qty, char* input[])
{
    list = new string[qty];
    for(int i = 0; i < qty; ++i)
        list[i] = input[i];
}

void display(string *list, int qty, string &input, string &output)
{
    int pos;
    ofstream outStream;
    input = output = "";

    cout<<"There were "<<qty<<" elements on the command line. They are:"<<endl;

    for(int i = 0; i < qty; ++i)
    {
        if((pos = list[i].find("/i=")) < list[i].size())
        {
            input = list[i].substr(pos + 3);
        }

        if((pos = list[i].find("/o=")) < list[i].size())
        {
            output = list[i].substr(pos + 3);
        }

        cout<<"argv["<<i<<"] = "<<list[i]<<" has "<<list[i].size()<<" characters"<<endl;
    }
}

void displayFileNames(string &input, string &output)
{
    if(input != "")
        cout<<"Input file name is "<<input<<endl;
    if(output != "")
        cout<<"Output file name is "<<output<<endl;
}

bool checkFile(ifstream &inStream, ofstream &outStream)
{
    if(inStream.fail())
    {
        cout << "Input file opening failed. \n";
        exit(1);
    }

    if(outStream.fail())
    {
        cout << "Output file opening failed. \n";
        exit(1);
    }

    return true;
}

void editedTextFunc(ifstream &inStream, ofstream &outStream, string &input, string &output)
{
    inStream.open(input);
    outStream.open(output);
    checkFile(inStream, outStream);

    cout << "The files have been successfuly opened. I will begin to copy and"
         << " edit the file.....\n\n";

    char charFromFile;
    const char BLANK_SPACE = ' ';

    while(inStream >> charFromFile)
    {
        while(charFromFile != BLANK_SPACE)
        {
             outStream.put(charFromFile);
             inStream.get(charFromFile);

             if(inStream.eof())
             {
                 inStream.close();
                 outStream.close();
                 cout << "The file has been copied and edited.\n";
                 //cout << "Please check your output file to check that it's correct.\n";
                 return;
             }
        }
        outStream.put(charFromFile);
    }
    inStream.close();
    outStream.close();
}

bool overwriteFile(ofstream &outStream, string &output, string *list, int qty)
{
    int pos;

    for(int i = 0; i < qty; ++i)
    {
        if((pos = list[i].find("/e")) < list[i].size())
        {
            outStream.open(output, ios::trunc);
            outStream.close();

            cout << "File was overwritten" << endl;
            return true;
        }
    }
    return false;
}

bool appendFile(ofstream &outStream, string &output, string *list, int qty)
{
    char next;
    int pos;

    for(int i = 0; i < qty; ++i)
    {
        if((pos = list[i].find("/a")) < list[i].size())
        {
            outStream.open(output, std::ios_base::app);
            //this command allows for file to be appended

            cout << "Enter what you would like to add to this file: " << endl;

            cin.get(next);
            outStream.put(next);

            while(next != '\n')
            {
                cin.get(next);
                outStream.put(next);

            }
            outStream.close();
            return true;
        }
    }
    return false;
}
