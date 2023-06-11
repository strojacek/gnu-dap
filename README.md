README
---

Gnu Dap is an open source implementation of SAS (Statistical Analysis System).

This repository contains the following changes I have made to the system:

- do to loops (completed)
- Termux compatability (completed)
- cards/datalines (in progress)
- proc sql (in progress)
- sas macros (in progress)
- proc mcmc (in progress)

Note: This is very much a work in progress, and the original codebase was written in C. In order to start the implementation of some newer features, I needed to use generics, and have had to update the C code to C++. 

Dap has contributions from the following individuals:

- Susan Bassein
- Anna Reidenbach
- Jeffrin Jose
- Seth Trojacek

Currently implemented Procedures
---

- Proc GLM
- Proc FREQ 
- Proc CORR
- Proc REG
- Proc PRINT
- Proc IMPORT
- Proc SORT
- Proc MEANS
- Proc PLOT
- Proc TABULATE

Dependencies
---

- Boost: For the tuple, version, utility, and iostreams packages.
- Eigen: For the MCMC, Stats, and BaseMatrixOps packages from ktothr.
- OpenXLSX: For the ability to do File I/O with Excel Spreadsheets.
- Sqlite ORM: For the usage of Proc SQL (in progress)

Example of Build Process
---

Note: The Build process is eventually moving completely to CMake from autotools. 

```bash
$ autoreconf -f -i
$ glibtoolize
$ automake --add-missing
$ autoupdate
$ ./configure
$ make
$ sudo make install
```

This should result in two executables: dap, and dappp that are accessible from the command line. Dappp is the preprocessor which will convert the SAS file to a C++ representation, which is compiled. 

To run Dap you can do the following

```bash
dap file.sas
```

This will output a .lst file of the same name as the file with the corresponding output of the sas file. There will also be a .ps file if there are graphics or a .err file if there are errors with the code. 

