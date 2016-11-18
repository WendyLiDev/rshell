echo With precedence operators: ;
(echo Apples && echo Banana) || (echo Cherry && echo Date);

echo ;
echo With nested precedence operators: ;
((echo Apples && (echo Figs && echo Banana) || (echo Cherry && echo Date);
echo ;
(echo Grapes && ( ( test -e Parsnip.cpp) || echo Honeydew ) && echo kiwi);

echo ;
echo exit && exit
