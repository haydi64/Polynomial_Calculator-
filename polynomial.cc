/*******************************************************************
* Name: Hayden Ivatts
* Date: 10-23-18
* Course: CSCI 132
* Assignment: Assignment 4
* Program: polynomial.cc
* Purpose: Implementation of polynomial class
***************************************************************************/
#include <iostream>
#include <cmath>
#include "polynomial.h"
using namespace std;

void Polynomial :: equals_difference(Polynomial p, Polynomial q)
/**********************************************************************
 * Pre: None
 * Post: The Polynomial object is reset as the difference of the two parameters.
 **********************************************************************/
{
    clear();
    while (!p.empty( ) || !q.empty( )) {
        //Temporary variables to hold info of each term
        Term p_term, q_term;
        if (p.degree( ) > q.degree( )) {
            p.serve_and_retrieve(p_term);
            p_term.coefficient = p_term.coefficient * -1;
            append(p_term);
        } else if (q.degree( ) > p.degree( )) {
            q.serve_and_retrieve(q_term);
            append(q_term);
        } else {
            p.serve_and_retrieve(p_term);
            q.serve_and_retrieve(q_term);
            if(q_term.coefficient - p_term.coefficient != 0) {
                //Adds answer to new queue
                Term answer_term(p_term.degree,
                                 q_term.coefficient - p_term.coefficient);
                append(answer_term);
            }
        }
    }
}

void Polynomial :: equals_product(Polynomial p, Polynomial q)
/**********************************************************************
 * Pre: None
 * Post: The Polynomial object is reset as the product of the two parameters.
 **********************************************************************/
{
    
    clear();
    //Temporary polynomial to hold terms while others are multiplied
    Polynomial equals_temp;
    while(!q.empty()) {
        //Holds current term of q
        Term q_term;
        //holds result of mult_term function
        Polynomial temp;
        q.serve_and_retrieve(q_term);
        temp.mult_term(p,q_term);
        equals_temp.equals_sum(equals_temp, temp);
    } //end while
    while(!equals_temp.empty()) {
        //holds term to be added to new polynomial
        Term answer;
        equals_temp.serve_and_retrieve(answer);
        append(answer);
    } //end while
} //end equals_product


void Polynomial :: mult_term(Polynomial p, Term t)
/**********************************************************************
* Pre: None
* Post: The Polynomial object is reset as the product of the polynomial,
*       p, and the single term, t.
**********************************************************************/
{
    clear();
    while(!p.empty()) {
        //Holds current term of p
        Term p_term;
        p.serve_and_retrieve(p_term);
        //Holds term to be added to new polynomial
        Term answer_term(p_term.degree + t.degree,
                         p_term.coefficient * t.coefficient);
        
        append(answer_term);
    }
}

double Polynomial :: evaluate (double number)
/**********************************************************************
* Pre: None
* Post: Evaluates the Polynomial object at number.
**********************************************************************/
{
   Polynomial p = *this;  //uses the object "receiving the message", but
                          //does not change the object data.
   //Holds running total of evaluation
   double answer = 0;
   while(!p.empty()) {
       //Current p term
       Term p_term;
       p.serve_and_retrieve(p_term);
       //Holds result of number to the power of degree
       double power = pow(number,p_term.degree);
       //Holds result of multiplication of power and coefficient to get answer
       double term_total = power * p_term.coefficient;
       answer+=term_total;
   }
   return answer;
} //end evaluate

Error_code Polynomial :: equals_quotient(Polynomial p, Polynomial q)
/**********************************************************************
* Pre: None
* Post: The Polynomial object is reset as the quotient of the two parameters.
**********************************************************************/
{
  cout << "This function not yet implemented." << endl;
  return success;
} //end equals_quotient()


void Polynomial :: print( )
/**********************************************************************
* Pre: None
* Post: The Polynomial is printed to cout. If the polynomial is empty, 
*       0 is printed.
**********************************************************************/
{
  
  double r;
  Polynomial temp;
  bool first_term = true;
  while (!empty( )) {
    Term print_term;
    serve_and_retrieve(print_term);
    temp.append(print_term);
    if (first_term) { // In this case, suppress printing an initial +.
      first_term = false;
      if (print_term.coefficient < 0) {
        cout << "- ";
      } 
    } else if (print_term.coefficient < 0) {
      cout << " - ";
    } else {
      cout << " + ";
    }
    if (print_term.coefficient >= 0) {    
      r = print_term.coefficient;
    } else {
      r = -(print_term.coefficient);
    } 
    if (r != 1) {
      cout << r;
    } 
    if (print_term.degree > 1) {
      cout << " X^" << print_term.degree;
    } 
    if (print_term.degree == 1) {
      cout << " X";
    }
    if (r == 1 && print_term.degree == 0) {
      cout << " 1";
    }
  } //end while
  if (first_term) {
    cout << "0"; // Print 0 for an empty Polynomial.
  } //end if
  cout << endl;
  while(!temp.empty( )) {
    Term temp_term;
    temp.serve_and_retrieve(temp_term);
    append(temp_term);
  }
} // end print()

void Polynomial :: read( )
/**********************************************************************
* Pre: None
* Post: The Polynomial is read from cin.
**********************************************************************/
{
  clear( );                  /* An Extended_queue function */
  double coefficient;
  int last_exponent, exponent;
  bool first_term = true;
  cout << "Enter the coefficients and exponents for the polynomial, "
       << "one pair per line. Exponents must be in descending order." << endl
       << "Enter a coefficient of 0 or an exponent of 0 to terminate." << endl;
  do {
    cout << "coefficient? " << flush;
    cin >> coefficient;
    if (coefficient != 0.0) {
      cout << "exponent? " << flush;
      cin >> exponent;
      if ((!first_term && exponent >= last_exponent) || exponent < 0) {
        exponent = 0;
        cout << "Bad exponent: Polynomial terminates without its last term."
             << endl;
      } else {
        Term new_term(exponent, coefficient);
        append(new_term);
        first_term = false;
      } //end if
      last_exponent = exponent;
    }
  } while (coefficient != 0.0 && exponent != 0); //end do-while
} // end read()

void Polynomial :: equals_sum(Polynomial p, Polynomial q)
/**********************************************************************
* Pre: None
* Post: The Polynomial object is reset as the sum of the two parameters.
**********************************************************************/
{
  clear( );
  while (!p.empty( ) || !q.empty( )) {
    Term p_term, q_term;
    if (p.degree( ) > q.degree( )) {
      p.serve_and_retrieve(p_term);
      append(p_term);
    } else if (q.degree( ) > p.degree( )) {
      q.serve_and_retrieve(q_term);
      append(q_term);
    } else {
      p.serve_and_retrieve(p_term);
      q.serve_and_retrieve(q_term);
      if (p_term.coefficient + q_term.coefficient != 0) {
        Term answer_term(p_term.degree, p_term.coefficient + q_term.coefficient);
        append(answer_term);
      } //end inner if
    } //end if-else
  } // end while
} //end equals_sum()


int Polynomial :: degree( ) const
/**********************************************************************
* Pre: None
* Post:If the Polynomial is identically 0, a result of -1 is returned. 
*      Otherwise the degree of the Polynomial is returned.
**********************************************************************/
{
  if (empty( )) return -1;
  Term lead;
  retrieve(lead);
  return lead.degree;
} //end degree( )

