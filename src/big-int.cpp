#include "big-int.h"
#include <iostream>
#include <sstream>
#include <cassert>

Big_Int::Big_Int(){
    len = 0;
    linked_start = new Digit;
    linked_end = new Digit;
    linked_end->nextDigit = nullptr;
    linked_start->nextDigit = linked_end;
     
}


/* 
 * first the start dummy cell is initialized.
 * and len to 0 if the string is empty the object will be initializs this way
 * else every character in the string will be first converted to an int
 * using a stringstream and a new digit corresponding to it will be created 
 * previous Digit referenced by dp pointer will then point to this newly created Digit.
 */
Big_Int::Big_Int(std::string str){
    linked_start = new Digit;
    linked_end = new Digit;
    linked_end->nextDigit = nullptr;
    len = 0;
    linked_start->nextDigit = linked_end;
    std::stringstream strStream;
    int i = str.length() -1;
    Digit * dp = linked_start;
    int intFromStr;
    while(i >=0){
        strStream << str[i];
        strStream >> intFromStr;
        strStream.clear();
        Digit * nDigit = new Digit;
        nDigit->num = intFromStr;
        ++len;
        --i;
        dp->nextDigit = nDigit;
        dp = nDigit;
    }
    dp->nextDigit = linked_end;
}

/* The destructor
 * must free all dynamic memory allocated by the class
 */
Big_Int::~Big_Int(){
  Digit * dp = linked_start;
  Digit * oldDp;
  while(dp != nullptr){
    oldDp = dp;
    dp = dp->nextDigit;
    delete oldDp;
  }
}

/* The string to be returned must must be constructed from 
 * end to start since the Big_Int class stores a numbers digits
 * in its internal representaion in reverse order.
 */

std::string Big_Int::toString()const{
    if(len == 0) return "";
    std::string result(len,'0');
    int i = len-1;
    Digit * dp = linked_start;
    while(i >=0){
      int digit = dp->nextDigit->num;
      dp = dp->nextDigit;
      std::string strDigit = std::to_string(digit);
      const char * cStr = strDigit.c_str();
      result[i] = cStr[0];
      --i;
    }
    
    return result;

}

Big_Int::getSize()const {
    return len;
}

/* This method addas a digit to an already consturcred Big_int */

void Big_Int::addDigit(unsigned short num){
    Digit * tp = linked_start;
    /* must foraward the pointer up to the last existing digit 
       if it exists.
    */
    while(tp->nextDigit != linked_end){
        tp = tp->nextDigit;
    }
    Digit * toBeAdded = new Digit;
    toBeAdded->num = num;
    toBeAdded->nextDigit = linked_end;
    tp->nextDigit = toBeAdded;
    ++len;
}


/* 
 * This method performos addition as done normally by adding 
 * two given digits and forwarding the carry to be added to the next digit.
 * The larger of the two numbers will be first detected such that if the size
 * difference is significant the addition steps will simplified by using the 
 * remaining digits of the number in the result.
 */


Big_Int  Big_Int::operator+(const Big_Int & num2)const{
    Big_Int result;
    if(len > 0 && num2.len > 0){
      /* gNum should represent the larger number if there not both equal
       * (pointer to its first digit)
       * example 7888888888888
       *       +           888
       *       ---------------
       */
      Digit * gNum;
      Digit * lNum;
      /* These two pointers to keep if track of the end of each number */
      Digit * gEnd;
      Digit * lEnd;
      /* This is a variable to hold the sum of addition of two digits */
      unsigned short currentResult;
      /* This is a variable to hold the number left after the carry is considered
         this variable is the one that gets inserted in the final result of addition. */
      unsigned short resultToInsert;
      if(len >= num2.len){
        gNum = linked_start->nextDigit;
        /*set the carry of the first digit to be 0 */
        gNum->carry = 0;
        gEnd = linked_end;
        lNum = num2.linked_start->nextDigit;
        lEnd = num2.linked_end;
      }else if(len < num2.len){
        gNum = num2.linked_start->nextDigit;
        /* set the the carry of the first digit of the greater of the two 
           numbers to 0 since there was no previous operatin before it to 
           initialize it to something.
        */
         gNum->carry =0;
        gEnd = num2.linked_end;
        lNum = linked_start->nextDigit;
        lEnd = linked_end;
      }
      /* while both numbers stil have digits to add */
      while(gNum != gEnd && lNum != lEnd){
        currentResult = gNum->num + lNum->num + gNum->carry;
        if(currentResult > 9){ 
            resultToInsert = currentResult - 10;
            gNum->nextDigit->carry = 1;
            result.addDigit(resultToInsert);
            gNum = gNum->nextDigit;
            lNum = lNum->nextDigit;
        }else {
            result.addDigit(currentResult);
            gNum->nextDigit->carry = 0;
            gNum = gNum->nextDigit;
            lNum = lNum->nextDigit;
        }
        
        }
        
        while(gNum != gEnd){
            currentResult = gNum->num + gNum->carry;
          
            if(currentResult >9){
                resultToInsert = currentResult -10;
                gNum->nextDigit->carry = 1;
                result.addDigit(resultToInsert);
                gNum = gNum->nextDigit;
            }else {
                result.addDigit(currentResult);
                gNum->nextDigit->carry = 0;
                gNum = gNum->nextDigit;
            }
 
        }
        if(gNum == gEnd){
            if(gNum->carry !=0){
                result.addDigit(gNum->carry);
                return result;
            }else {
                return result;
            }
        }
        return result;
      

    }//#TODO throw error one or both numbers are not initialized.
}
/* deepCopy will copy all the digits of src to 
   the object and set the len variable as the same as src*/
void Big_Int::deepCopy(const Big_Int & src){
    linked_start = new Digit;
    linked_end = new Digit;
    linked_end->nextDigit = nullptr;
    linked_end->carry = src.linked_end->carry;
    len = src.len;

    /* pointer to iterate over the contents of src. */
    Digit * sDp = src.linked_start;
    Digit * thisDp = linked_start;
    while(sDp != src.linked_end){
      thisDp->carry =  sDp->carry;
      thisDp->num =  sDp->num;
      if(sDp->nextDigit != src.linked_end){
      thisDp->nextDigit = new Digit;
      thisDp = thisDp->nextDigit;
      sDp = sDp->nextDigit;
     }else {
        sDp = sDp->nextDigit;
     }
     
    }
    thisDp->nextDigit = linked_end;

    
}

/*the copy constructor initilizes a new Big_int as a copy of another BigInt */
Big_Int::Big_Int(const Big_Int & src){
    deepCopy(src);
}
Big_Int & Big_Int::operator=(const Big_Int & src){
    if(this != &src){
      Digit * dp = linked_start;
      while(dp != nullptr){
        Digit * oldDp = dp;
        dp= dp->nextDigit;
        delete oldDp;
      }
      deepCopy(src);
    }
    return *this;
}

void Big_Int::clear(){
    len = 0;
    linked_start->carry = 0;
    linked_end->carry = 0;
    Digit * dp = linked_start->nextDigit;
    while(dp != linked_end){
        Digit * oldDp = dp;
        dp = dp->nextDigit;
        delete oldDp;
    }
    linked_start->nextDigit = linked_end;
}
/* The effect of this method is adding a digit to the right of 
   an already exisitng numberl
*/
void Big_Int::addToStart(unsigned short num){
    len+=1;
    Digit * nDp = new Digit;
    nDp->num = num;
    nDp->nextDigit = linked_start->nextDigit;
    linked_start->nextDigit = nDp;
}
/* 
 * multiplication will be performed by multiplying the digit
 * of smaller of the two numbers by each of the digits of the larger
 * while performaing the operation for each digit from least significant to most
 * multiplication by 1 10 100 etc will be applied then all results will be summed
 * for the final result.
*/
Big_Int Big_Int::operator*(const Big_Int & num)const {
    if(len >0 && num.len >0){
    /* These values serve the same purpose as in + */
      Digit * gNum;
      Digit * lNum;
      Digit * gEnd;
      Digit * lEnd;
      Digit * gStart;
      if(len >= num.len){
        gNum = linked_start->nextDigit;
        lNum = num.linked_start->nextDigit;
        gEnd =  linked_end;
        lEnd = num.linked_end;
        gStart = linked_start;
      }else {
        gNum = num.linked_start->nextDigit;
        lNum = linked_start->nextDigit;
        gEnd = num.linked_end;
        lEnd = linked_end;
        gStart = num.linked_start;
      }
      /* The final result to be returned and the 
         intermediary result of multiplying a digit by all
         digits of the other number which will be added to the next 
         interemdiary resutl etc to produce the final result.
       */
      Big_Int finalResult("0");
      Big_Int interResult;

      unsigned short currentResult;
      unsigned short resutlToInsert;
      /* a variable to track the current digit in multiplication 
         such that after moving to another digit append a zero to the resutl
         firt digit nothing the second digit zero the third two zeros etc... */
      unsigned short track_digit = 0;
      gNum->carry = 0;
      std::stringstream strStream;
      while(lNum != lEnd){
        while(gNum != gEnd){
          currentResult = lNum->num * gNum->num + gNum->carry;
          if(currentResult >9){
              strStream << currentResult;
              unsigned short tempCarry;
              tempCarry = strStream.get();
              tempCarry-=48;
              gNum = gNum->nextDigit;
              gNum->carry = tempCarry;
              unsigned short tempRes;
              tempRes = strStream.get();
              tempRes -= 48;
              interResult.addDigit(tempRes);
        }else {
            gNum = gNum->nextDigit;
            gNum->carry = 0;
            interResult.addDigit(currentResult);
        }
      }
      strStream.clear();
      if(gEnd->carry != 0)interResult.addDigit(gEnd->carry);
      int i = track_digit;
      while(i>0){
        interResult.addToStart(0);
        --i;
      }
      track_digit+=1;
      finalResult = finalResult + interResult;
      interResult.clear();
      lNum = lNum->nextDigit;
      gNum = gStart->nextDigit;
      gNum->carry=0;

    }
     return finalResult;
    }
    //TODO one or both numbers are not initialized.
}
