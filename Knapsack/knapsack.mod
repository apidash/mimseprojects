/*********************************************
 * OPL 12.4 Model
 * Author: apidash
 * Creation Date: 16 oct. 2015 at 16:55:56
 *********************************************/
int nbObj=...;
int Capacity=...;

range  I=1..nbObj;

int Profit[I]=...;
int Weight[I]=...;

dvar int x[I] in 0..1;


maximize sum(i in I)x[i]*Profit[i];

subject to{
  
  sum(i in I)x[i]*Weight[i]<=Capacity;
}  

