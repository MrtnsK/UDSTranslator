# **UDSTranslator**

The purpose of this soft is to take a log file, read it and translate it to be readable by human with 3 sources :
- The AGCO specification
- The SID (Service Identifier) from the [Wikipedia UDS page](https://en.wikipedia.org/wiki/Unified_Diagnostic_Services)
- A local [csv file](id_ecu.csv) (that need to be formatted like it is actually to work well, if not the comportement will be undefinded)

## **Build**

On Linux system:
```make```

On Window system *(with cygwin64)*:
```make wdw```

## **Usage**

You need to keep the [id_ecu.csv](id_ecu.csv) at the same place of your compiled file.

 ***linux:***
```
./UDSTranlate [TraceFile]
or
./UDSTranlate
Path to the file to translate ? (Not case sensitive)
$> [TraceFile]
```

 ***window:*** 
> Directly launch the exe UDSTranlate.exe
```
Path to the file to translate ? (Not case sensitive)
$> [TraceFile]
```

## **Template of the id_ecu.csv file**

The formatting of the file is pretty important, he **has** to be like this *(The semicolon is the delimitor of the csv)*

you need to add 0x at the front of your id (if there's not already)
> **0x**ID;ECU

and at the end
>EOF;

***Exemple:***
```
0x14DAF9EC;A5 Trans Dyna - 4PS - App138
0x0ADAF9ED;A11 virgin
0x14DAF9FC;IC1
0x0ADAF9D0;A5 Cab susp Valtra
0x0ADAF9D1;A5 Cab susp MF
0x0ADAF9D2;A5 Additionnal
0x0ADAF9D3;A5 Cab Armrest
EOF;
```
