Doc updated on 02/03/2012

README file for mRALlte Interface

 ******************
  Release dates

  D0.1 :  02.03.2012
 ******************

 The mRALlteInt is compiled and run in the mRALlteInt directory where the zipped file exploded. Just run
  > make
 in the directroy to compile it

 To execute the validation scenario, it is necessary to download and compile ODTONE (open-source multiple-plaftorm IEEE 802.21 MIHF implementation).

 The mih-usr.cpp file provided here must replace the default mih-usr.cpp provided by ODTONE  in order to run the  LTE link test Interface Scenario described in the Test_scenario.jpg file. 
 A mih_usr and odtone-mihf executables will be available by compiling ODTONE.

 Messages are exchanged between the following programs:

 mih_usr <-> ODTONE <-> mRALlteInt

 - to test the validation scenario, execute the following programs, each in its own terminal, and in the following order:
   >./odtone-mihf
   >./mRALlteInt LOG_location LOG_level
   >./mih_usr --dest=mihf1

 ******************
 mRALlteInt usage :

 >./mRALlteInt LOG_location LOG_level

 LOG_location can take the following values
 0 : Log to screen
 1 : Log to file (default is /tmp/log_MT_LTE.txt)
 2 : Log to system (syslog) -- FFS

 If no value is entered , default value as log to file is assumed.

 LOG_level can take the following values
 0 : DEBUG + ERROR
 1 : ERROR only

 ******************


