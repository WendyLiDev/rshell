([-e Parser.cpp] && echo Parser.cpp exists) && (test -f Parser.cpp && echo Parser.cpp is file) && (test -d tests && echo tests directory found); 

([-e Parse.cpp] && echo Parse.cpp exists) || (echo Parse.cpp does not exist);
(test -f Parse.cpp && echo Parse.cpp is file) || (echo Parse.cpp does not exist);
(test -d texts && echo texts directory found) || (echo texts directory not found);

exit;
