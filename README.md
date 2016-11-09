# This program parses MINIML xml files.

Within the file the program searches for the following nodes and attributes:
> 
* __MINiML(root node)__
  * __Sample__
    * __iid__
    * __Channel__
      * _Source_
    * __Title__
    * __Supplementary-Data__
      * _type(IDAT)_
>

The nodes and attributes are used to fill the following fields in a formatted excel file

* _Sample_name:_ iid
* _Sample_plate:_ empty
* _Sample_group:_ Source
* _Pool_ID:_ empty
* _Project:_ empty
* _Sample_Well:_ empty
* _Sentrix_ID:_ Supplementary-Data(type: IDAT)
* _Sentrix_Position:_ Supplementary-Data(type: IDAT)

Upon opening the excel file a warning will be displayed because we created the file using this programm and not excel.
The file is safe to open and use.

The URLs pulled from **Supplementary-Data** are stored in a text file named `GetFile.txt`.
This file is then looked for by `getScript.cpp` which uses the linux command `wget` to download the files to the server.
