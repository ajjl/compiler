void compile_program() {
	fputs( PROLOGUE, objectfile );
	/* =BUG= create default environment e */
	environment e1 = compile_block( e );
	if (lex_this.type != ENDFILE) {
		lex_gotbutwant( lex_this, ENDFILE );
	}
	fputs( EPILOGUE, objectfile );
}

environment compile_block( environment e ) {
	while ( (lex_this.type == IDENT)
	||      lex_iskeyset( lex_this, STATEMENT_KEYWORDS ) ) {
		if ( (lex_this.type == IDENT)
		&&   lex_ispunc( lex_next, PT_COLON ) ) {
			e = compile_declaration( e );
		} else {
			compile_statement( e );
		}
		if (lex_ispunc( lex_this, PT_SEMI )) lex_advance();
	}
}
