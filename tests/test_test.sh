echo Parser.cpp: ;
echo exists: && [ -e Parser.cpp ]; ( test -e Parser.cpp );
echo file: && [ -f Parser.cpp ]; ( test -f Parser.cpp );
echo directory: && [ -d Parser.cpp ]; ( test -d Parser.cpp );

echo tests: ;
echo exists: && [ -e tests ]; ( test -e tests );
echo file: && [ -f tests ]; ( test -f tests );
echo directory: && [ -d tests ]; ( test -d tests );

echo ;
echo Parsnip.cpp: ;
echo exists: && [ -e Parsnip.cpp ]; ( test -e Parsnip.cpp );
echo file: && [ -f Parsnip.cpp ]; ( test -f Parsnip.cpp );
echo directory: && [ -d Parsnip.cpp ]; ( test -d Parsnip.cpp );

echo ;
echo texts: ;
echo exists: && [ -e texts ]; ( test -e texts );
echo file: && [ -f texts ]; (test -f texts );
echo directory: && [ -d texts ]; ( test -d texts );

echo ;
echo Check with operators: ;
( echo Parser.cpp exists && [-e Parser.cpp] ) && ( echo Parser.cpp is file && test -f Parser.cpp ) && ( echo tests directory found && test -d tests ); 

echo ;
([-e Parsnip.cpp] && echo Parsnip.cpp exists) || (echo Parsnip.cpp does not exist);
(test -f Parsnip.cpp && echo Parsnip.cpp is file) || (echo Parsnip.cpp does not exist);
(test -d texts && echo texts directory found) || (echo texts directory not found);

exit;
