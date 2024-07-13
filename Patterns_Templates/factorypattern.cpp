#include<iostream>
#include<stdexcept>
#include<memory>
using namespace std;
 class Pizza
 {
 private:

 protected:

 public:
    virtual int  getPrice() const=0;
    virtual ~Pizza(){};
 };

 class HamAndMushroomPizza:public Pizza{
 private:

 protected:

 public:
     virtual int getPrice() const{return 1050;};
     virtual ~HamAndMushroomPizza(){};

 };
  class FarmFreshPizza:public Pizza{
 private:

 protected:

 public:
     virtual int getPrice() const{return 700;};
     virtual ~FarmFreshPizza(){};

 };
  class DeluxePizza:public Pizza{
 private:

 protected:

 public:
     virtual int getPrice() const{return 500;};
     virtual ~DeluxePizza(){};

 };
 class PizzaFactory
 {
 private:

 protected:

 public:
     enum PizzaType{
            Deluxe,HamAndMushroom,FarmFresh
     };
     static unique_ptr<Pizza> createPizza(PizzaType pizzatype){
        switch (pizzatype){
            case Deluxe: return make_unique<DeluxePizza>();
            case HamAndMushroom: return make_unique<HamAndMushroomPizza>();
            case FarmFresh: return make_unique<FarmFreshPizza>();
        }
        throw "invalid";
     }
 };
 void pizza_information(PizzaFactory::PizzaType pizzatype)
 {
     unique_ptr<Pizza> pizza=PizzaFactory::createPizza(pizzatype);
     cout<<"Price of "<<pizzatype<<" is "<<pizza->getPrice()<<endl;
 }
 int main()
 {
     pizza_information(PizzaFactory::Deluxe);
     pizza_information(PizzaFactory::HamAndMushroom);
     pizza_information(PizzaFactory::FarmFresh);

 }
