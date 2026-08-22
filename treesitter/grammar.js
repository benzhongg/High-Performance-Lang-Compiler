const PREC = {
    ADD: 2,
    MULTIPLY: 3
};

module.exports = grammar({
    name: 'hplc',

    rules: {
        program_file: $ => repeat($._statement),

        _statement: $ => choice(
            $.preprocessor,
            $.assignment,
            $.binary_expression,
            $.print
        ),

        preprocessor: $ => seq(
            '#',
            field('macro', $.macro),
            field('value', $.number_literal)
        ),

        assignment: $ => seq(
            field('type', $.variable_type),
            field('operand', $.identifier),
            '=',
            field('value', choice($._literal, $.binary_expression, $.identifier))
        ),

        binary_expression: $ => choice(
            prec.left(PREC.ADD, seq(
                field('left', choice($._literal, $.binary_expression, $.identifier)),
                field('operator', choice('+', '-')),
                field('right', choice($._literal, $.binary_expression, $.identifier))
            )),
            prec.left(PREC.MULTIPLY, seq(
                field('left', choice($._literal, $.binary_expression, $.identifier)),
                field('operator', choice('*', '/')),
                field('right', choice($._literal, $.binary_expression, $.identifier))
            ))
        ),

        print: $ => seq('print', '(', field('argument', choice(
            $._literal,
            $.binary_expression,
            $.identifier
        )), ')'),

        _literal: $ => choice($.number_literal, $.string_literal),
        string_literal: $ => seq('"', optional(/[^"\\]*/), '"'),
        variable_type: $ => choice('int', 'string'),
        identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
        number_literal: $ => /[0-9]+/,
        macro: $ => 'define'
    }
});