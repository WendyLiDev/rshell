echo Check Parser.cpp exists, is file, and tests is directory: ;
[-e Parser.cpp] && (test -f Parser.cpp) && (test -d tests); 

echo ;
echo Check Parsnip.cpp exists, is file, and texts is directory: ;
[-e Parsnip.cpp]; (test -f Parsnip.cpp); (test -d texts);

echo ;
echo A comment follows this;
# This is a comment! 
