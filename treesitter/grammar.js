module.exports = grammar({
    name: 'HPLC',

    rules: {
        
        program_file: $ => repeat($._statement),

        _statement: $ => choice
        (
            $._preprocessor,
            $._assignment,
            $._binaryexpression,
            $._print
        ),

        _preprocessor: $ => seq
        (
            '#',
            $._macro,
            $._value
        ),

        _assignment: $ => seq 
        (
            $._variableType,
            $._operand,
            '=',
            choice($._literal, $._binaryexpression)
        ),

        _binaryexpression: $ => seq
        (
            choice($._literal, $._binaryexpression, $._identifier),
            ('=', '+', '-', '/'),
            choice($._literal, $._binaryexpression, $._identifier),
        ),

        _print: $ => seq
        (
            ('print('),
            choice($._literal, $._binaryexpression, $._identifier),
            (')')
        ),

        _literal: $ =>
        {
            choice($._numberliteral, $._stringliteral)
        },  

        _stringliteral: $ => seq
        (
            '\"',
            [a-z],
            repeat
            (
                repeat(choice([a-z][A-Z])),
                repeat($._numberliteral)
            ),
            '\"',
        ),
        
        _variableType: $ => choice
        (
            'int',
            'string'
        ),
        
        _operand: $ => seq
        (
            [a-z],
            repeat
            (
                repeat(choice([a-z][A-Z])),
                repeat($._numberliteral)
            )
        ),
        
        _numberliteral: $ => /\d+/,
        _macro:         $ => 'define',
        _value:         $ => $._numberliteral,
        _identifier:    $ => $._operand, 
        
    }
});
