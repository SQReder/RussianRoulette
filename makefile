clean:
	del /s "*.#??" *.il? *.map *.tds *.pdi *.obj *.cgl *.*log*

clean_bin:
	cd bin\
	del /s "*.#??" *.il? *.map *.tds *.pdi *.obj *.cgl *.*log*
