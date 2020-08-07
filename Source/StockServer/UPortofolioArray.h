//---------------------------------------------------------------------------

#ifndef UPortofolioArrayH
#define UPortofolioArrayH
#define MAXSIZE 100

#include "UPortofolio.h"
class TPArray {
  public:
    /* Deletes a specific Index of the array                                  */
    void Delete(int index);
    /* Add a portofolio to the back of the array                              */
    void Add(TPortofolio *porto);
    /* Cleans up the array                                                    */
    void Clear();
    /* Returns the number of portofolios in the array                         */
    int Count();
    /* Access via normal array behaviour                                      */
    TPortofolio *operator[](int i);
    TPArray();
    ~TPArray();
  private:
    int size;
    /* Stores the Portofolios in a array of the Macro MAXSIZE                 */
    TPortofolio *arr[MAXSIZE];
};

//---------------------------------------------------------------------------
#endif
