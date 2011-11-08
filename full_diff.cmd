for /f "tokens=1-3 delims=/-. " %%a in ('date /t') do set XDate=%%c-%%b-%%a
set nicename="%XDate%.diff"

svn diff > %nicename%
gvim %nicename%