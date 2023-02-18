//
//  Project 1: Gerrymandering
//  Author: Rahin Jain
//  Course: CS 251, UIC Spring' 23
//  
// ** The logic for parts of this project were discussed with a few peers and TAs from within the CS 251 batch.
//    Hence, the logic might seem familiar at some parts.

#include "ourvector.h"
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "math.h"
using namespace std;

// -----------------------------------------------------------------------------------------
// 2 struct that saves the data of each state from the file.
struct StateDistrictData{

    int districtID;
    int democraticVoters;
    int republicVoters;
};
struct stateData{

    string StateName;
    int totalVoters;
    ourvector <StateDistrictData> DistrictData;
};


// -----------------------------------------------------------------------------------------
// Function definitions
void splitString(string line, char delimiter, ourvector<string>& items );
string lowerCasing (string currStr);

int commandProcessing (ourvector <stateData>& stateVec, ourvector <string>& cmdStr, string& STATE, int& loc);

int loadCMD (ourvector <stateData>& stateVec, string file1, string file2, int load_check);
int searchCMD (ourvector <stateData>& stateVec,ourvector <string>& cmdStr, string& STATE, int& loc);
int statsCMD (ourvector<stateData>& stateVec, int& loc);
int plotCMD (ourvector<stateData>& stateVec, int&loc);

// -----------------------------------------------------------------------------------------
// Logistical functions
// takees in one string and split every substring divided by the delimeter into a vector items
void splitString(string line, char delimiter, ourvector<string>& items ) {

    stringstream s_stream(line);
    while (s_stream.good()) {

        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}
// takes in a string and lowercases it before returning it
string lowerCasing (string currStr){

    string newStr = "";
    for (int i = 0; i < currStr.size(); i++){
        newStr.push_back(tolower(currStr.at(i)));
    }
    return newStr;
}
// splits the processes into different functions based on the command inputted by the user
int commandProcessing (ourvector <stateData>& stateVec, ourvector <string>& cmdStr, string& STATE, int& loc){

    int FUNCreturn = -1;

    if (cmdStr.at(0) == "load"){

        int load_check = 0;
        load_check = loadCMD(stateVec, cmdStr.at(1), cmdStr.at(2), load_check);

        if (load_check == 1 || load_check ==3){
            FUNCreturn = 11;
        } else if (load_check == 2) {
            FUNCreturn = 12;
        } else if (load_check == 0) {
            FUNCreturn = 0;
        }
    }
    else if (cmdStr.at(0) == "search"){

        FUNCreturn = searchCMD(stateVec, cmdStr, STATE, loc);
    }
    else if (cmdStr.at(0) == "stats"){

        statsCMD(stateVec, loc);
        FUNCreturn = 2;
    }
    else if (cmdStr.at(0) == "plot"){

        plotCMD(stateVec, loc);
        FUNCreturn = 3;
    }
    else if (cmdStr.at(0) == "exit"){
        FUNCreturn = 4;
    }
    else {
        cout << "Enter a valid command" << endl;
    }

    return FUNCreturn;
}


// -----------------------------------------------------------------------------------------
// Command Functions
// loads both the files and updates the stateVec
int loadCMD (ourvector <stateData>& stateVec, string file1, string file2, int load_check){

    ifstream districtStream;
    districtStream.open(file1);
    ifstream voterStream;
    voterStream.open(file2);

    if(!districtStream.is_open()){
        load_check += 1;
        return load_check;
    }

    // For first file (assuming first file is always about district data)

    string tempLine;
    ourvector<string>tempVec;
    StateDistrictData districtOBJ;
    ourvector <StateDistrictData> districtDataVec;

    cout << "Reading: " << file1 << endl;

    if (districtStream.is_open()){

        while (!districtStream.fail() && !districtStream.eof()){

            getline(districtStream, tempLine);
            splitString(tempLine, ',', tempVec);


            stateData stateOBJ;
            stateOBJ.StateName = tempVec.at(0);



            for(int i = 1; i < tempVec.size();i+=3){

                if (tempVec.at(i) == "AL"){
                    tempVec.at(i) = "1";
                }

                districtOBJ.districtID = stoi(tempVec.at(i));
                districtOBJ.democraticVoters= stoi(tempVec.at(i+1));
                districtOBJ.republicVoters= stoi(tempVec.at(i+2));

                districtDataVec.push_back(districtOBJ);

            }
            stateOBJ.DistrictData = districtDataVec;
            stateVec.push_back(stateOBJ);
            // ---
            districtDataVec.clear();

            if (stateOBJ.StateName != "") {
                cout << "..." << stateOBJ.StateName << "..." << districtOBJ.districtID << " districts total" << endl;
            }


            tempVec.clear();

        }
    }
    // Resetting variables
    tempLine = " ";
    tempVec.clear();

    // For second file (assuming its always about eligible voters)

    if(!voterStream.is_open()){
        load_check += 2;
        return load_check;
    }

    cout << endl;

    if(voterStream.is_open()){

        cout<< "Reading:" << file2 <<endl;
        while(!voterStream.fail()){

            getline(voterStream,tempLine);
            splitString(tempLine,',', tempVec);

            for(int i =0; i < stateVec.size()-1;i++) {
                //string nameInVec = stateVec.at(i).stateName;
                if(stateVec.at(i).StateName == tempVec.at(0) ) {

                    stateVec.at(i).totalVoters = stoi(tempVec.at(1));
                    cout<< "..." << stateVec.at(i).StateName<<"...";
                    cout<<stateVec.at(i).totalVoters<< " eligible voters" << endl;
                    break;
                }
            }
            tempVec.clear();
        }
    }
    return load_check;
}
// updates loc to find exactly which element in stateVec needs to be accessed
int searchCMD (ourvector <stateData>& stateVec, ourvector <string>& cmdStr, string& STATE, int& loc){
    bool stateFound = false;
    int funcReturn;

    for (int n = 0; n < stateVec.size(); n++){

        string stateSearched = "";
        for (int i = 1; i < cmdStr.size(); i++){
            stateSearched += cmdStr.at(i);
            stateSearched += " ";
        }

        string lowerCased = lowerCasing(stateSearched);
        string lowerStateName = lowerCasing(stateVec.at(n).StateName);

        lowerStateName += " ";

        if (lowerStateName == lowerCased){

            STATE = stateVec.at(n).StateName;
            stateFound = true;
            loc = n;

            funcReturn = 1;
            break;
        }}
    if (!stateFound){
        funcReturn = 13;
    }
    return funcReturn;
}
// calculates stats required to find out if a state is gerrymandered or not. and outputs UI as needed
int statsCMD (ourvector<stateData>& stateVec, int& loc){

    long totalDemWasted = 0.0;
    long totalRepWasted = 0.0;
    float efficiency = 0.0;
    float totalActVotes = 0;
    bool gerry = false;

    int totalEllVoters = 0;
    int totalDemVotes = 0;
    int totalRepVotes = 0;

    string loweredStateInFile = lowerCasing(stateVec.at(loc).StateName);

    float distDemWasted;
    float distRepWasted;

    int overhalf;

    totalEllVoters = stateVec.at(loc).totalVoters;

    for (int j = 0; j < stateVec.at(loc).DistrictData.size(); j++){

        totalRepVotes += stateVec.at(loc).DistrictData.at(j).republicVoters;
        totalDemVotes += stateVec.at(loc).DistrictData.at(j).democraticVoters;

        int repInADist = stateVec.at(loc).DistrictData.at(j).republicVoters;
        int demInADist = stateVec.at(loc).DistrictData.at(j).democraticVoters;

        overhalf = ((repInADist + demInADist)/2)+1;
        if (repInADist > demInADist){

            distDemWasted = demInADist;
            distRepWasted = repInADist-overhalf;
        } else {

            distRepWasted = repInADist;
            distDemWasted = demInADist-overhalf;
        }

        totalDemWasted += distDemWasted;
        totalRepWasted += distRepWasted;
        totalActVotes += (demInADist+repInADist);

    }

    efficiency = ((abs(totalDemWasted-totalRepWasted))/totalActVotes)*100;

        if (efficiency >= 7 && stateVec.at(loc).DistrictData.size() >= 3){
            gerry = true;
        }
    // UI
    cout << "Gerrymandered: ";
    if (gerry){
        cout << "Yes" << endl;
        cout << "Gerrymandered against: " ;
        if (totalDemVotes < totalRepVotes)
        {
            cout << "Democrats" << endl;
        }
        else
        {
            cout << " Republicans" << endl;
        }
        cout << "Efficiency Factor: " << efficiency << "%" << endl;
    } else {cout << "No" << endl;}
    cout << "Wasted Democratic votes: " << totalDemWasted << endl;
    cout << "Wasted Republican votes: " << totalRepWasted << endl;
    cout << "Eligible voters: " << totalEllVoters << endl << endl;

    return 0;
}
// Calculates percentage of democratic and rupublican votes in a state and plot it in a specific format
int plotCMD (ourvector<stateData>& stateVec, int&loc){

    float demWon = 0.0;
    double total = 0.0;
    for (int i = 0; i < stateVec.at(loc).DistrictData.size(); ++i) {

        double demVotes = stateVec.at(loc).DistrictData.at(i).democraticVoters;
        total = stateVec.at(loc).DistrictData.at(i).democraticVoters + stateVec.at(loc).DistrictData.at(i).republicVoters;
        demWon = ((stateVec.at(loc).DistrictData.at(i).democraticVoters)/total);
        int final = demWon*100;

        cout << "District: " << stateVec.at(loc).DistrictData.at(i).districtID << endl;
        cout << setw(final) << setfill('D') << "";
        cout << setw(100-(final)) << setfill('R') << "";
        cout << endl;
    }


    return 3;
}
// -----------------------------------------------------------------------------------------
// Main logic

int main() {

    bool dataLoaded = false;
    bool stateSearched = false;

    int loc = 0;
    int commandKey = -1;
    ourvector <string> commandVec;
    ourvector<stateData> stateVec;
    string STATE = " ";
    string COMMAND;
    // Possible commands: load (0) / search (1) / stats (2) / plot (3) / exit (4).
    // Error handling command returns: invalid file1 (11) / invalid file (12)
    //                                 invalid search (13)

    cout << "Welcome to the Gerrymandering App!" << endl;

    // Basic UI & logistics
    while (commandKey != 4) {

        cout << "Data loaded? ";
        if (dataLoaded){cout << "Yes" << endl;}
        else {cout << "No" << endl; }

        cout << "State: ";
        if (stateSearched){cout << STATE << endl;} 
        else {cout << "N/A" << endl;}

        cout << "Enter command: ";
        getline(cin, COMMAND);
        cout << endl << "-----------------------------" << endl;

        splitString(COMMAND, ' ', commandVec);
        // error checking
        if (commandVec.at(0) != "exit") {
            if (dataLoaded && (commandVec.at(0) == "load")) {

                cout << "Already read data in, exit and start over." << endl;
            } else {
                if (!dataLoaded && (commandVec.at(0) != "load")) {

                    cout << "No data loaded, please load data first." << endl;
                } else {

                    commandKey = commandProcessing(stateVec, commandVec, STATE, loc);
                    // error checking
                    if (commandKey == 0) { dataLoaded = true; }
                    if (commandKey == 11) {cout << "Invalid first file, try again." << endl;}
                    if (commandKey == 12) {cout << "Invalid second file, try again." << endl;}
                    if (commandKey == 13) {cout << "State does not exist, search again." << endl;}
                    if (commandKey == 1) { stateSearched = true; }
                }
            }
            commandVec.clear();
        } else {
            return 0;
        }
    }
    return 0;
}
