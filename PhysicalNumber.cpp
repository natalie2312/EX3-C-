// #include "PhysicalNumber.h"
// #include <stdexcept>
// #include <iostream>
// #include <cmath>


// using namespace std;
// using namespace ariel;

// PhysicalNumber::PhysicalNumber(double num, Unit unit){
//     this->unit = unit;
//     this->num = num;
// };

// Unit PhysicalNumber::getunit(){
//      return this->unit; 
// };

// double PhysicalNumber::getnum(){
//      return this->num; 
// };

// void PhysicalNumber::setnum(double num){ 
//     this->num = num; 
// };


// PhysicalNumber& PhysicalNumber::operator++(){ 
//     num++;
//     return *this;
// };



// PhysicalNumber& PhysicalNumber::operator--(){
//     num--;
//     return *this;
// };

// PhysicalNumber PhysicalNumber::operator++(int){
//     PhysicalNumber old(*this);
//     ++num;
//     return old;
// };

// PhysicalNumber PhysicalNumber::operator--(int){
//     PhysicalNumber old(*this);
//     --num;
//     return old;
// };


// PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& ot){ 
//     double x= casting(ot);
//     PhysicalNumber temp(this->num+x, this->unit);
//     return temp; 
//     };

// PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& ot){ 
//     double x= casting(ot);
//     PhysicalNumber temp(this->num-x, this->unit);
//     return  temp;
//     }; 

// PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& ot){ 
//     double x= casting(ot);
//     setnum(this->num + x);
//     return *this;
// };

// PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& ot){
//     double x= casting(ot);
//     setnum(this->num - x);
//     return *this;
// };

// PhysicalNumber& PhysicalNumber::operator+(){ 
//     return *this; 
// }; 

// PhysicalNumber& PhysicalNumber::operator-(){  // unary minus
//     setnum(-this->num);
//     return *this; 
// };

// bool PhysicalNumber::operator>(const PhysicalNumber& ot){
//      return this->num > casting(ot);
// };

// bool PhysicalNumber::operator>=(const PhysicalNumber& ot){ 
//     return this->num >= casting(ot); 
// };

// bool PhysicalNumber::operator<(const PhysicalNumber& ot){ 
//     return this->num < casting(ot); 
// };

// bool PhysicalNumber::operator<=(const PhysicalNumber& ot){ 
//     return this->num <= casting(ot); 
// };

// bool PhysicalNumber::operator==(const PhysicalNumber& ot){ 
//     return this->num == casting(ot); 
// };

// bool PhysicalNumber::operator!=(const PhysicalNumber& ot){ 
//     return this->num != casting(ot); 
// };


// ostream& ariel::operator<<(ostream& os, PhysicalNumber pn){
//     const char *types[] = { "cm","h","sec","m","kg","min","km","ton","hour" };
//     return os << pn.getnum() <<"[" << types[(int)pn.unit] << "]";
//  };
            
// istream& ariel::operator>>(istream& is, PhysicalNumber pn){
//   double x;
//   int unit;
//   cout << "amount:";
//   is >> x;
//   pn.num= x;
//   cout << "unit:";
//   is >> unit;
//   pn.unit = (Unit)unit;
//   return is;
// };


// string stringUnit(PhysicalNumber pn){
// int x = pn.getunit();
// switch (x) {
//   case 0: return "CM";
//   case 1: return "M";
//   case 2: return "KM";
//   case 3: return "G";
//   case 4: return "KG";
//   case 5: return "TON";
//   case 6: return "SEC";
//   case 7: return "MIN";
//   case 8: return "HOUR";
// }
// return "";
// }



// double PhysicalNumber::casting(const PhysicalNumber& ot){

//     if(this->unit % 3 != ot.unit % 3){
//         throw runtime_error("Can't convert");
//     }
//     else{

//         int myUnit= this->unit;
//         int otUnit= ot.unit;
//         switch(ot.unit % 3){    // mod 0= lenght, mod 1= weight, mod 2= time
//             case 0:  // lenght

//             case 1:  // weight
//                 return ot.num*(pow(1000,(1)));
//                 break;
//             case 2:  //time
//                 return ot.num*(pow(60,(1)));
//                 break;
//             }
//     }
//     return -1; 
// };


#include "PhysicalNumber.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <cmath>

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double units, Unit typeID){
    this->typeID = typeID;
    this->units = units;
};

Unit PhysicalNumber::getTypeID(){ return this->typeID; };

double PhysicalNumber::getUnits(){ return 1.0f*this->units; };

void PhysicalNumber::setUnits(double units){ this->units = units; };

double PhysicalNumber::translateOther(const PhysicalNumber& other){
    int dif = ((int)this->typeID - (int)other.typeID);
    if(dif % 3 != 0){
        throw runtime_error("Cannot convert");
    } else{
        dif = dif/3;
        switch((int)other.typeID % 3){
            case 0:                        
                if((int)this->typeID == (int)other.typeID){  
                    return other.units;
                    break;
                }else if((int)this->typeID == 0 && (int)other.typeID == 3){
                    return other.units*100*1.0;
                    break;  
                }else if((int)this->typeID == 0 && (int)other.typeID == 6 ){
                    return other.units*10000*1.0f;
                    break;
                }else if((int)this->typeID == 3 && (int)other.typeID == 0 ){
                    return other.units/100*1.0f;
                    break;
                }else if((int)this->typeID == 6 && (int)other.typeID == 0 ){
                    return other.units/10000*1.0f;
                    break;
                }else if((int)this->typeID == 6 && (int)other.typeID == 3 ){
                    return other.units/1000*1.0f;
                    break;
                }else{ // 6 to 3
                    return other.units*1000*1.0;
                    break;
                }
                break;

            case 1: //Length or Mass cases
                return other.units*1.0f*(pow(1000.0,(-dif)));
                break;
            case 2: //Time case
                return (double)other.units*(pow(60.0,(-dif)));
                break;
            }
    }
    return -1; //never gets here.
};
PhysicalNumber& PhysicalNumber::operator++(){ //prefix
    ++units;
    return *this;
};

PhysicalNumber PhysicalNumber::operator++(int){
    PhysicalNumber old(*this);
    ++units;
    return old;
};

PhysicalNumber& PhysicalNumber::operator--(){
    --units;
    return *this;
};

PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber old(*this);
    --units;
    return old;
};

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other){ 
    return PhysicalNumber(1.0f*(this->units+translateOther(other)), this->typeID);
     }; //add units same world

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other){ return PhysicalNumber(this->units-translateOther(other), this->typeID); }; //decrease units same world

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other){ //adding  +=
    setUnits(this->units + translateOther(other));
    return *this;
};

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other){
    setUnits(this->units - translateOther(other));
    return *this;
};

PhysicalNumber& PhysicalNumber::operator+(){ return *this; }; //unary plus

PhysicalNumber PhysicalNumber::operator-(){ return PhysicalNumber(-this->units, this->typeID); };

bool PhysicalNumber::operator>(const PhysicalNumber& other){ return this->units > translateOther(other); };

bool PhysicalNumber::operator>=(const PhysicalNumber& other){ return this->units >= translateOther(other); };

bool PhysicalNumber::operator<(const PhysicalNumber& other){ return this->units < translateOther(other); };

bool PhysicalNumber::operator<=(const PhysicalNumber& other){ return this->units <= translateOther(other); };

bool PhysicalNumber::operator==(const PhysicalNumber& other){ return this->units == translateOther(other); };

bool PhysicalNumber::operator!=(const PhysicalNumber& other){ return this->units != translateOther(other); };

ostream& ariel::operator<<(ostream& os,const  PhysicalNumber& pn){
    const char *types[] = { "cm","g","sec","m","kg","min","km","ton","hour" };
    return os << pn.units<<"[" << types[(int)pn.typeID] << "]";
 };
            
istream& ariel::operator>>(istream& is, PhysicalNumber& pn){
    string input;
    is >> input;
    regex validate("([-])?([\\d]+([.][\\d]+)?)(\\[)((cm)|(m)|(km)|(g)|(kg)|(ton)|(sec)|(min)|(hour))(\\])");
    if(regex_match(input,validate)){
        const char *types[] = { "cm","g","sec","m","kg","min","km","ton","hour" };
        Unit unit;
        int start = input.find('[');
        int end = input.find(']');
        map<string,Unit> unitMap;
        unitMap["cm"] = Unit::CM;
        unitMap["g"] = Unit::G;
        unitMap["sec"] = Unit::SEC;
        unitMap["m"] = Unit::M;
        unitMap["kg"] = Unit::KG;
        unitMap["min"] = Unit::MIN;
        unitMap["km"] = Unit::KM;
        unitMap["ton"] = Unit::TON;
        unitMap["hour"] = Unit::HOUR;
 
        double value = stod(input.substr(0,start));
        string type = input.substr(start+1,end-start-1);
        unit = unitMap.find(type)->second;

        pn.units = value;
        pn.typeID = unit;

    }
    else{
        is.setstate(ios::failbit);
    }
    return is;
};