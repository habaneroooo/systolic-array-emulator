# Introduction #

This page contains the description of the script language used to describe the behaviour of a systolic array.

# Details #

Note: The script language translator is packed within the program, it is not intended to be used outside of the SAE (although with some tweaks, it could be).

Syntax:
All parametres are separated by one tabulation unless indicate otherwise.

Data :

Each processor has 4 I/O registers, disposed as such:
> U
L processor R
> D

Exemple: 2x2 array

> U1		U2
L1 proc1 [R1](https://code.google.com/p/systolic-array-emulator/source/detail?r=1) proc2 [R2](https://code.google.com/p/systolic-array-emulator/source/detail?r=2)
> D1		D2
L2 proc3 [R3](https://code.google.com/p/systolic-array-emulator/source/detail?r=3) proc4 [R4](https://code.google.com/p/systolic-array-emulator/source/detail?r=4)
> D3		D4

In addition, a temporary register stores the results of operations.
The final result is copied to both output registers (R&D);

All registers are 32bits wide.

You can also create registers by using the macro #register (see the Macro section)

Macros

#register	name
Creates a 32bits register so you can store data inbetween calculations.
This macro cannot be used after the calculation description has started or it will be ignored.


#calculation	name	number of cycles

A calculation is a series of process. There must be at least one

#process	X	Y
X is the series of operation each diagonal will operate each after another.
Y is the number of times that process is executed before going on to the next process.

#end	calculation: quits calculation mode