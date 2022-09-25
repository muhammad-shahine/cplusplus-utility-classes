
#ifndef _BIG_INT_H
#define _BIG_INT_H

 #include <string>

/*
 * bigint.h
 * ------------------------
 * The interface for the class BigInt
 * used to represent numbers larger than 32 bits
 * or larger than 64 bit numbers the number grows dynamically
 * this class uses a linked list to represet the large number
 * every digit is a struct type the number reads from right to left
 * example: 923 the first digit in the linked list will be 3 then 2 then 9.
 */



class Big_Int {
    public:

     /* Default constructor creates an empty  Big_Int could be used
        for late to copy another Big_Int to it 
     */
     Big_Int();
     /* This constructor creates a Big_Int 
      * that is initializes from the given string value
      */
     Big_Int(std::string str);
     

    /* The destructor */
     ~Big_Int();

     /* method: toStirng
      * Usage: strRepresentaion = bigInt.toString();
      */
     std::string toString() const;
     
    /* method: operator+
     * usage: BigInt sum = bigInt1 + bigInt2;
     * ---------------------------------------
     * implements the overloaded addition operator for 
     * two Big_int objects the operation performed is 
     * normal addition.
     */
    /* method: getSize
     * usage int size = bigInt.getSize();
     * ----------------------------------
     * returns the number of digits in the number.
     */
     int getSize()const;
     /* adds a digit at the beginging of a Big_int (left side) */
      void addDigit(unsigned short num);
    /* normal addition */
    Big_Int operator+(const Big_Int & num2)const;
    /* Overloaded mulitplication 
     * Usage: Big_Int product = bigIntObj1 * BingIntObj2;
     * --------------------------------------------------
     * will multiply two big int objects and return the result.
     */
    Big_Int operator*(const Big_Int & num) const;
    /* copy construcor */
    Big_Int(const Big_Int & src);
    /* copy assignment operator */
    Big_Int & operator=(const Big_Int & src);
    
    /* adds a digit to the right of a number */
    void addToStart(unsigned short num);
    /* deletes all digits only leves the start and end dummy digits */
    void clear();
    private:
      /* The representaion of a digit in the linked list of digits 
       * will consit of a number between 0 and 9 and a carry when addition or
       * multiplication is performed also a pointer to the next digit.
       * num and carry are unsigned short which is more than enough to represent digits 
       * from 0 -> 9.
       */
      struct Digit {
        unsigned short num;
        unsigned short carry;
        Digit * nextDigit;
      };
      /* a dummy digit to  simplify the implementaion */
      Digit * linked_start;
      /* a dummy digit to simplify the implementation */
      Digit * linked_end;
      /* The length of the big int */
      int len;
      
      /* method: deepCopy
       * Usage: deepCopy(src);
       * -------------------------
       * copies the contents of a given object src
       * to the object upon which its called on.
       */
      void deepCopy(const Big_Int & src);
};

#endif
