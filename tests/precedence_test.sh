echo Without precedence operators: ;
echo Apples && echo Banana || echo Cherry && echo Date;

echo With precedence operators: ;
(echo Apples && echo Banana) || (echo Cherry && echo Date);

echo Without precedence operators: ;

echo With precedence operators: ;

echo exit && exit
