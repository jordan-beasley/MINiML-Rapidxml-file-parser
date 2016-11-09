# This program parses MINIML xml files.

Within the file the program searches for the following nodes and attributes:
> * MINiML(root node)
  * Sample
    * iid
    * Channel
      * Source
    * Title
    * Supplementary-Data
      * type(IDAT)
> 
The nodes and attributes are used to fill the following fields in a formatted excel file
**Sample_name:** iid
**Sample_plate:** empty
**Sample_group:** Source
**Pool_ID:** empty
**Project:** empty
**Sample_Well:** empty
**Sentrix_ID:** Supplementary-Data(type: IDAT)
**Sentrix_Position:** Supplementary-Data(type: IDAT)

Upon opening the excel file a warning will be displayed because we created the file using this programm and not excel.
The file is safe to open and use.

The URLs pulled from **Supplementary-Data** are stored in a text file named `GetFile.txt`.
This file is then looked for by `getScript.cpp` which uses the linux command `wget` to download the files to the server.
