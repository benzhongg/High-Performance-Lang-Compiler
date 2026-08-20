const PREC = {
    ASSIGN: 1,
    ADD: 2,
    MULTIPLY: 3
};

export default grammar({
    name: 'HPLC',

    rules: {
        
        program_file: $ => repeat($._statement),

        _statement: $ => choice
        (
            $.preprocessor,
            $.assignment,
            $.binaryexpression,
            $.print
        ),

        preprocessor: $ => seq
        (
            '#',
            field('macro', $.macro),
            field('value', $.number_literal)
        ),

        assignment: $ => seq 
        (
            field('type', $.variable_type),
            field('operand', $.identifier),
            '=',
            field('value', choice($._literal, $.binaryexpression, $.identifier))
        ),

        binaryexpression: $ => choice
        (
            
            prec.left(PREC.ADD, seq
                (
                    field('left', choice($._literal, $.binaryexpression, $.identifier)),
                    field('operator', choice('+', '-')),
                    field('right', choice($._literal, $.binaryexpression, $.identifier)),
                )
            ),
            prec.left(PREC.MULTIPLY, seq
                (
                    field('left', choice($._literal, $.binaryexpression, $.identifier)),
                    field('operator', choice('+', '-')),
                    field('right', choice($._literal, $.binaryexpression, $.identifier)),
                )
            )
        ),

        print: $ => seq
        (
            ('print'),
            ('('),
            field('argument', choice($._literal, $.binaryexpression, $.identifier)),
            (')')
        ),

        _literal: $ => choice
        (
            $.number_literal,
            $.string_literal
        ),

        string_literal: $ => seq('"', optional(/[^"]*/), '"'),
        
        variable_type: $ => choice
        (
            'int',
            'string'
        ),
        
        identifier:     $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
        number_literal: $ => /\d+/,
        macro:         $ => 'define'
    }
});
