echo CONTENTS OF CURRENT DIRECTORY: ;
ls;

echo CD TO TESTS: ;
cd tests;
echo;

echo RETURN TO PREV WORKING DIRECTORY: ;
cd -;
cd -;
cd -;
echo;

(test -d test && test -e test) && (cd test && echo moved to test directory);

(test -d tests && test -e tests) && (cd tests && echo moved to tests directories);

cd -;

(test -d tests && test -e tests) && (cd tests && [-e exit.sh]);

echo RETURN TO HOME DIRECTORY: ;
cd;
echo;

exit;