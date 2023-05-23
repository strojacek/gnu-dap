data data1;
		x = 0;
		do i = 1 to 10;
				x = i * 4;
				output;
		end;
run;

proc print data1;
run;
