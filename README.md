# Postfix Calculator
Files for a calculator that converts infix notation to postfix, and then evaluates the expression.

USAGE

Expressions are entered in the standard infix notation and will be evaluated with the standard PEMDAS order of operations. Spaces can be entered into the expression as desired and will not affect the result. For example:

    1 + 2 - 3 * 4 / 5
    
          and
          
    1+2-3*4/5

are evaluated in exactly the same way and will produce the same result. However, numbers with spaces in between them will ALWAYS be treated as separate numbers. For example:

    1 + 23 * 4 / 5
    
        and
    
    1 + 2 3 * 4 / 5
    
will not be treated the same (in fact, the second expression will be read as an incorrect input).

Incomplete expressions will are not properly able to be evaluated and will generate a default result of 0. For example:

    1 + 2 - 3 * 4 / 5 +
    
will not be evaluated properly.

Group operations are allowed, but only via parenthesis. For example:

    (1 + 2) - 3 * 4 / 5
    
Groups in parenthesis will be evaluated prior to any other operations.

Parenthesis must be placed and closed properly in order for an expression to be evaluated. For example:

    (1 + 2 - 3 * 4 / 5
    1 + 2) - 3 * 4 / 5
    ((1 + 2) - 3 * 4 / 5
    1 + 2 - (3 * 4 / 5)))
    
will all fail to evaluate and prompt the user to enter the expression again.
