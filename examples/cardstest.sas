/*create dataset*/
data original_data;
	input points assists rebounds;
    datalines;
	22 8 4
	29 5 4
	31 12 8
	30 9 14
	22 7 1
	24 9 2
	18 6 4
	20 5 5
	25 1 4
	;
run;

/*view dataset*/
proc print data=original_data;
run;
