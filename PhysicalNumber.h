#pragma once
#include "Unit.h"
#include <iostream>


namespace ariel{

    class PhysicalNumber{
        private:
            Unit typeID;
            double units;
        public:
            PhysicalNumber(double units, Unit type); 
            Unit getTypeID(); 
            double getUnits(); 
            void setUnits(double units);
            PhysicalNumber operator+(const PhysicalNumber& other); 
            PhysicalNumber& operator+=(const PhysicalNumber& other); 
            PhysicalNumber& operator+ (); 
            PhysicalNumber operator-(const PhysicalNumber& other); 
            PhysicalNumber& operator-=(const PhysicalNumber& other); 
            PhysicalNumber operator- (); 
            PhysicalNumber& operator++ ();
            PhysicalNumber& operator-- ();
            PhysicalNumber operator++ (int);
            PhysicalNumber operator-- (int);
            bool operator>(const PhysicalNumber& other);
            bool operator>=(const PhysicalNumber& other);
            bool operator== (const PhysicalNumber& other);
            bool operator!= (const PhysicalNumber& other);
            bool operator<(const PhysicalNumber& other);
            bool operator<=(const PhysicalNumber& other);
            friend std::ostream& operator<<(std::ostream& os, PhysicalNumber pn);
            friend std::istream& operator>>(std::istream& is, PhysicalNumber pn);
        private:
            double translateOther(const PhysicalNumber& other); 
    };
};
