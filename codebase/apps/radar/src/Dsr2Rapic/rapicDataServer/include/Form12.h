
//////////////////////////////////////////////////////////////
//
// Header file for Form12
//
//    This file is generated by RapidApp 1.2
//
//    This class is derived from Form12UI which 
//    implements the user interface created in 
//    RapidApp. This class contains virtual
//    functions that are called from the user interface.
//
//    When you modify this header file, limit your changes to those
//    areas between the "//---- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//////////////////////////////////////////////////////////////
#ifndef FORM12_H
#define FORM12_H
#include "Form12UI.h"
//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


//---- Form12 class declaration

class Form12 : public Form12UI
{

  public:

    Form12 ( const char *, Widget );
    Form12 ( const char * );
    ~Form12();
    const char *  className();
    virtual void newFile();
    virtual void openFile(const char *);
    virtual void print(const char *);
    virtual void save();
    virtual void saveas(const char *);

    static VkComponent *CreateForm12( const char *name, Widget parent ); 

    //---- Start editable code block: Form12 public


    //---- End editable code block: Form12 public



  protected:


    // These functions will be called as a result of callbacks
    // registered in Form12UI

    virtual void closeWin ( Widget, XtPointer );
    virtual void deviceEnabledChanged ( Widget, XtPointer );
    virtual void getFinishedScansChanged ( Widget, XtPointer );

    //---- Start editable code block: Form12 protected


    //---- End editable code block: Form12 protected



  private:

    static void* RegisterForm12Interface();

    //---- Start editable code block: Form12 private


    //---- End editable code block: Form12 private


};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

