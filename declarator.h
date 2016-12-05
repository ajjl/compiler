// declarator.h file


ifndef EXTERN
#define EXTERN extern
#endif

class Declarator {
public:
        static Environment * compile( Environment * e );
     

        // =BUG= do declarations have any attributes?  they are missing here
      

private:
       //=BUG= nothing lives here yet

};

#undef EXTERN

