/*Code generation file, cpp file*/

/* WE NEED TO SLOWLY LOWER THE ABSTRACTION LEVEL SLOWLY, LIKE ONE STEP A TIME TO WRITE THIS PART, IT IS ALSO GOOD FOR DEBUG*/

/* AFTER CHECK THE SEMANTICS, THIS PART WILL BE USED*/

/*POSSIBLY THERE WILL BE SOME OPTIMIZATIONS BETWEEN SOME PASSES TO MAKE THE ENTIRE PROCESS BETTER*/


/* WE ALSO NEED TO ADD TETING METHOD FOR CODE GENERATION SO WE CAN TREAT BUG WISELY AND EFFECIENTLY*/

/* GUIDELINE OF CODE GENERATOR CPP ENDS HERE*/

/*THIS CODE DOES NOT COMPILE NOW*/

#if 0


/* first of all, need to divide different symbols and keywords into different sub parts*/

/* AS AN ARRAY */
/* tHE TABLE NAME IS GOING TO BE CHANGED*/

newTable[]={
{ "=", mathSymbol },
{ "+". mathSymbol },
{ "-", mathSymbol },
/* * means multiple and pointer in c++, but in Kestrel? */
{ "*", mathSymbol },
{ "/", mathSymbol },
{ "%", mathSymbol },
{ "//", mathSymbol},
/* HOW TO DIVIDE '//' AND '/' , SURELY '//' SHOULD BE IN HIGHER PRIORITY*/
{"!", logicalSymbol},
{"==", logicalSymbol},
{"<", comparisonSymbol},
{">", comparisonSymbol},
{"<=", comparisonSymbol},
{"=<", comparisonSymbol},
{">=", comparisonSymbol},
{"=<", comparisonSymbol},
/* FOR EXAMPLE, case, statemnet maybe should be adding here*/



/* SURELY WE NEED TO DISTINGUISH SYMBOLS STUCK TOGETHER GENERAL SITUATION AND SPECIAL OCCASIONS*/

/* there are still many things to fill in this table */



}
 

/* NEED TO ADD FUNCTION SWITCH BETWEEN CASES*/

/* need to check structures of finding certain key words,
add pointer on for example "while" w->h->i->l->e->recon"while" key word,
just a reminder.*/









#endif
