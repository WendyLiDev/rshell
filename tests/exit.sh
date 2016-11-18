echo Check Parsnip.cpp exists, is file, or directory and stop program: ;
test -e Parsnip.cpp && exit;
[-e Parsnip.cpp] && exit;
test -f Parsnip.cpp && exit;
[-f Parsnip.cpp] && exit;
test -d Parsnip.cpp && exit;
[-d Parsnip.cpp] && exit;

echo ;
echo Check texts exists, is file, or directory and stop program: ;
test -e texts && exit;
[-e texts] && exit;
test -f texts && exit;
[-f texts] && exit;
test -d texts && exit;
[-d texts] && exit;

echo ;
echo Check Parser.cpp exists and is file and stop program: ;
(test -e Parser.cpp && test -f Parser.cpp) && exit;

echo ;
echo Check tests exists and is directory and stop program: ;
(test -e tests && test -d tests) && exit; 

# file exits before last three lines, change order to test both