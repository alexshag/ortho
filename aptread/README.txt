
=======
APTREAD
=======

What is it?
-----------

There is 'wpnavapt.txt' file that hold airport's data in PMDG format. 
It has more than 33 thousand records.   
 
If you have an installation of PMDG product the file is placed in 'NavData'
folder. It is likely to have some tool for searching airport's data if such
huge database without open it directly.

The program search any given airport in the file and display these data.

How to use?
-----------

Just set some airport's ICAO code as an argument of the program.

What is format of the file?
---------------------------

Here is the description of 'wpnavapt.txt' file.
All positions are represented in characters.
Start Length Description

 0 25 Airport name  
25  4 ICAO code
29  3 Runway ID
32  5 Runway length (ft)
37  3 Rwy number
41  9 Rwy threshold latitude
51 11 Rwy threshold longitude
61  6 ILS frequency
67  3 ILS magnetic heading
70  5 Rwy threshold altitude (ft)

