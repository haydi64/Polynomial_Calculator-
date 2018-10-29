
/*
 * File Name: polynomial.h
 * Author: Hayden Ivatts
 * Modification Date: 10/18/18
 * Adapted from: Robert Kruse and Alexander Ryba
 *         from "Data Structures and Program Design in C++"
 * Course: CSCI 132
 * Purpose: Specification of polynomial class
*/
#include "queue.h"
#ifndef POLY_H
#define POLY_H
class Polynomial: private Extended_queue { // Use private inheritance.
public:
  void read( );
  void print( );
  void equals_sum(Polynomial p, Polynomial q);
  void equals_difference(Polynomial p, Polynomial q);
  void equals_product(Polynomial p, Polynomial q);
  double evaluate(double number);
  Error_code equals_quotient(Polynomial p, Polynomial q);
  int degree( ) const;
  private:
  void mult_term(Polynomial p, Term t);
};
#endif
