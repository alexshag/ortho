
=======
APTREAD
=======

What is it?
-----------

There is 'wpnavapt.txt' file that hold airport's data in PMDG format. 
It has more than 33 thousand records. This file is protected by copyright 
and cannot be distributed freely. However, if you have an installation 
of PMDG product the file is placed in 'NavData' folder. It is desirable 
to have some kind of tool to search for data in such a huge database 
without having to open it directly.

This program searches for the specified airport in the 'wpnavapt.txt' file 
and displays the airport runway data.

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

Restrictions imposed by copyright
---------------------------------

Next files are included in Navigraph database (www.navigraph.com)

airports.txt
cycle_info.txt
fmc_ident.txt
wpNavAID.txt
wpNavAPT.txt
wpNavFIX.txt
wpNavRTE.txt

Source data are copyright by Jeppesen (https://ww2.jeppesen.com).

This data may be used for ground based recreational computer game
simulation software only, and may not be recompiled, interpreted,
or distributed for any purpose without the written consent of Navigraph.
The contents of this database is dated and must not be used for real
world navigation as it is unlawful and unsafe to do so.
