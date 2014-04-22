#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>
#include <sstream>

using namespace std;

void* findLargestInFile(void*);
int maxFromArray(int*,int);

int main(int argc, char *argv[])
{
    int numberOfFiles = atoi(argv[1]);
    int* max = new int[numberOfFiles];
    pthread_t* threads = new pthread_t[numberOfFiles];

    for(int i = 0; i < numberOfFiles; i++)
    {
        stringstream filestream;
        filestream << "Inputs/file" << i + 1 << ".txt";
        string message = filestream.str();
        pthread_create(&threads[i], NULL, findLargestInFile, (void*)message.c_str());
        cout << message << endl;
    }
    
    for(int i = 0; i < numberOfFiles; i++)
    {
        pthread_join(threads[i], (void **)&max[i]);
    }

    cout << "Maximum number for all files is " << maxFromArray(max, numberOfFiles) << endl;
    
    return 0;
}

void* findLargestInFile(void* rawFileName)
{
    char* fileName = (char*)rawFileName;
    int largest = INT_MAX;
    int current;
    string line;
    ifstream myfile(fileName);
    
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            current = atoi(line.c_str());
            if(largest == INT_MAX)
            {
                largest = current;
            }
            else if(largest < current)
            {
                largest = current;
            }
        }
        
        myfile.close();
    }
    
    pthread_exit((void *)largest);
    
    return 0;
}

int maxFromArray(int* array, int numberOfElements)
{
    int result = array[0];
    
    for(int i = 1; i < numberOfElements; i++)
    {
        cout << array[i] << endl;
        if(array[i] > result)
        {
            result = array[i];
        }
    }
    
    return result;
}

