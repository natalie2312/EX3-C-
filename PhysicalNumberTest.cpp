/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);


    //my test 
    PhysicalNumber t1(200, Unit::M);
    PhysicalNumber t2(300, Unit::CM);
    PhysicalNumber t3(4, Unit::KM);
    PhysicalNumber t4(60, Unit::SEC);
    PhysicalNumber t5(60, Unit::MIN);
    PhysicalNumber t6(2, Unit::HOUR);
    PhysicalNumber t7(10, Unit::G);
    PhysicalNumber t8(5, Unit::KG);
    PhysicalNumber t9(2, Unit::TON);
    // end for the variabales

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT
   

      .CHECK_OUTPUT(t1, "200[m]")
      .CHECK_OUTPUT(t2, "300[cm]")
      .CHECK_OUTPUT(t3, "4[km]")
      .CHECK_OUTPUT(t4, "60[sec]")
      .CHECK_OUTPUT(t5, "60[min]")
      .CHECK_OUTPUT(t6, "2[hour]")
      .CHECK_OUTPUT(t7, "10[g]")
      .CHECK_OUTPUT(t8, "5[kg]")
      .CHECK_OUTPUT(t9, "2[ton]")
      .CHECK_OUTPUT(t1+t2, "203[m]")
      .CHECK_OUTPUT(t1+t3, "4200[m]")
      .CHECK_OUTPUT(t5+t4, "61[min]")
      .CHECK_OUTPUT(t6+t5, "3[hour]")
      .CHECK_THROWS(t1+t4)
      .CHECK_THROWS(t2+t5)
      .CHECK_THROWS(t3+t6)
      .CHECK_THROWS(t3+t7)
      .CHECK_THROWS(t2+t7)
      .CHECK_THROWS(t1+t7)
      .CHECK_THROWS(t3+t8)
      .CHECK_THROWS(t1+t5)
      .CHECK_THROWS(t2+t6)
      .CHECK_OK(istringstream("60[m]") >> t6)
      .CHECK_EQUAL(t1+t2,PhysicalNumber(3,Unit::CM))
      .CHECK_EQUAL(t4+t5,PhysicalNumber(61,Unit::MIN))
      .CHECK_EQUAL(t6,PhysicalNumber(1,Unit::HOUR))

      //
      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
