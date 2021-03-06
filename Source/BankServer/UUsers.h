/* This source has been formatted by an unregistered SourceFormatX */
/* If you want to remove this info, please register this shareware */
/* Please visit http://www.textrush.com to get more information    */

//---------------------------------------------------------------------------

#ifndef UUsersH
#define UUsersH

#include <Classes.hpp>
#include <iostream>
#include <fstream>
#include <vcl.h>

class TUsers {
  public:
    /* Add a User to the internal list                                        */
    /* Params:                                                                */
    /* pip = IP of the user                                                   */
    /* puser = Username                                                       */
    /* ppassword = Password of the User                                       */
    /* pamount = Initial amount (or in case that he have allready an account: */
    /*           The actual amount retreived by LoadFromFile)                 */
    bool add(String pip, String puser, String ppassword, String pamount); 
    /* Autheticate a user by his IP, Username and Password                    */
    /* If successed = set his account to Active(so he gets salary)            */
    /*                and return TRUE
    /* If not       = account doesn't exist// Username or Password false      */
    /*                and return FALSE                                        */
    bool auth(String pip, String puser, String ppassword);
    /* Returns true if the Param pip Exists in the StringList ip else false   */
    bool exist(String pip);
    /* Delete a User of condition that he entered the right                   */
    /* username and password                                                  */
    bool del(String pip, String puser, String ppassword);
    /* Returns the amount of the Param pip (IP)                               */
    String getAmount(String pip);
    /* Returns a list in a String of all users with their amount              */
    /* Example: User1 1000 User2 1000 User3 2000                              */
    String getAllAmounts();
    /* Add the users with their amount into a Listbox                         */
    /* *lb = listbox                                                          */
    /* pactive = true: add users which are active else  add all               */
    /* len = right align the amount to len caracters                          */
    void addUsersToListBox(TListBox *lb, bool pactive, int len);
    /* Removes a specfific amount from an IP                                  */
    /* Returns True if the final amount would be >= 0 else Returns false      */
    /* And returns false if the user does'nt exist                            */
    bool removeAmount(String pip, float pamount);
    /* Adds a specfific amount from an IP                                     */
    /* Returns false if the user does'nt exist else Returns True              */
    bool setAmount(String pip, float pamount);
    /* Moves a amount from a Source IP to a Destination IP                    */
    /* Returns false if the Source or the Dest IP doesn't exist               */
    /* Returns false if the Amount of Source is to Low to provide pamount     */
    /* Else Return True                                                       */
    bool moveAmount(String sip, String dip, float pamount);
    /* Sets a specific IP to active                                           */
    void setActive(String pip, String pactive);
    /* Sets all IP's to inactive                                              */
    void setAllInactive();
    /* Saves the Users into a file (path)                                     */
    /* Format: IP;USER;PASSWORD;AMOUNT                                        */
    void SaveToFile(String path);
    /* Load the Users from a file (path) into the stringlists                 */
    /* Format: IP;USER;PASSWORD;AMOUNT                                        */
    /*          |   |         |      |                                        */
    /*         ip  user  password   amount                                    */
    void LoadFromFile(String path);
    /* Update all active account with a specific amount (pamount)             */
    void updateAmounts(float pamount);
    TUsers();
    ~TUsers();
  private:
    /* Stringlists to Store userinformation                                   */
    /* ip = ip of the user                                                    */
    /* user = username of the user                                            */
    /* password = password of  the user                                       */
    /* active (True/False) = Is he logged in or not                           */
    TStringList *ip,  *user,  *password,  *amount,  *active;
    /* Incremets a amount of a user with the internal index (pos)             */
    void incAmount(int pos, float pamount);
    /* Decrements a amount of a user with the internal index (pos)            */
    /* Returns true if final amount would be >= 0 else Returns false          */
    bool decAmount(int pos, float pAmount);
    /* Formats 3 Strings together into a String where the last will be aligned*/
    /* on the Right side (len characters)                                     */
    /* Example: String1 String2                      String3                  */
    String formatString(String a, String b, String c, int len);
};
//---------------------------------------------------------------------------
#endif
