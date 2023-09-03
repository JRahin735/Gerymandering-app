# Gerymandering-app

Project Summary:

Recently gerrymandering has been a popular topic in the news and the subject of an ongoing Supreme Court case. Gerrymandering is creating voting districts in such a way that gives one party an unfair advantage over the other. Political parties do this to try to help themselves stay in power. Recently, a research group came up with a mathematical definition for what constitutes gerrymandering. For this project, you will write a code that determines whether the state’s districts are gerrymandered, according to the researchers’ definition. The input data about states’ districts and total voters comes from two input files. Even if you disagree with this definition of gerrymandering, it is interesting to understand it better as the courts are currently debating it. 

Features of the program:
load in voting data (and display it to the screen), 
search the data for a particular state, 
plot all the districts’ votes of that particular state, 
display the calculated stats for that particular state.
Starter Code with Example Input & Output

Example Execution
Here is a quick tour of one execution of the program (console input is in red):
Welcome to the Gerrymandering App!

Data loaded? No
State: N/A

Enter command: load districts.txt eligible_voters.txt

-----------------------------

Reading: districts.txt
...Maryland...8 districts total
...
...Pennsylvania...18 districts total

Reading: eligible_voters.txt
...Alabama...3606103 eligible voters
...
...Wyoming...431011 eligible voters

Data loaded? Yes
State: N/A

Enter command: search illinois

-----------------------------

Data loaded? Yes
State: Illinois

Enter command: stats

-----------------------------

Gerrymandered: No
Wasted Democratic votes: 921521
Wasted Republican votes: 850785
Eligible voters: 8983758

Data loaded? Yes
State: Illinois

Enter command: plot

-----------------------------

District: 1
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRR
…
District: 18
DDDDDDDDDDDDDDDDDDDDDDDDDRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

Data loaded? Yes
State: Illinois

Enter command: exit

-----------------------------

This project was done as a part of CS 251 at UIC during Spring '23 taught under Prof. Adam Kohler.
