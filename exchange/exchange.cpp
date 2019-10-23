#include <exchange.hpp>

void exchange::convertto(asset in) {
        
        token_supply exchange_state(_self,_self);
	    auto itr=exchange_state.cbegin();
        asset supply=itr->supply;
        asset quote=itr->quote.balance;
        double weight=itr->quote.weight;

      real_type R(supply.amount);
      real_type C(quote.amount+in.amount);
      real_type F(weight);
      real_type T(in.amount);
      real_type ONE(1.0);

      real_type E = -R * (ONE - std::pow( ONE + T / C, F) );
      
      int64_t issued = int64_t(E);
      exchange_state.modify(itr,0, [&](auto& a){
        a.quote.balance.amount+=in.amount;
	    });
      
     print ("-------");
      print( asset( issued, supply.symbol ));
      bsktleft(issued);
   }

   void exchange::convertfrom(asset in)
{
    asset supply;
    double weight;
    asset quote;

    token_supply exchange_state(_self, _self);
    auto itr = exchange_state.cbegin();
    supply = itr->supply;
    quote = itr->quote.balance;
    weight = itr->quote.weight;
    eosio_assert(in.symbol == supply.symbol, "unexpected asset symbol input");

    real_type R(supply.amount);
    real_type C(quote.amount);
    real_type F(1 / weight);
    real_type E(in.amount);
    real_type ONE(1.0);

    real_type T = C * (std::pow(ONE + E / R, F) - ONE);
    int64_t out = round(T);
    exchange_state.modify(itr,0, [&](auto& a){
        a.base.balance.amount+=in.amount;
	    });
    //print("hello ------");
    print( asset( out, quote.symbol ));
    asset outtoken=asset(out,quote.symbol);
    eosleft(outtoken);
}

   void exchange::addsupply(asset supply,asset base,asset quote)
    {
        token_supply exchange_state(_self,_self);
	    auto itr=exchange_state.find(supply.symbol.name());
	    eosio_assert(itr==exchange_state.end(), "Currency already exists");
	    print (itr==exchange_state.end());
        
            exchange_state.emplace(_self, [&](auto& a){
	        a.supply=supply;
            a.base.balance=base;
            a.quote.balance=quote;
	    
	    });
        print("adding new token");
        print ("-------");
    }

     void exchange::updatesupply(asset supply,asset base,asset quote)
    {
        token_supply exchange_state(_self,_self);
	   // auto itr=exchange_state.find(supply.symbol.name());
        const auto& itr = exchange_state.get(S(4,BSKT), "ram market does not exist");
        //eosio_assert(itr!=address.end(), "Account doesnt exist");
       // print(itr==exchange_state.end());
        exchange_state.modify(itr,0, [&](auto& a){
	        a.supply=supply;
            a.base.balance=base;
            a.quote.balance=quote;
	    });
        
    }

    void exchange::bsktleft(int64_t issued)
    {
        token_supply exchange_state(_self,_self);
	    auto itr=exchange_state.cbegin();
	    //auto itr1=exchange_state.cend();
        asset base=itr->base.balance;
        double weight=itr->base.weight;
         exchange_state.modify(itr,0, [&](auto& a){
	    a.base.balance.amount-=issued;
	    });
        print("---available portfolio token is :", itr->base.balance);
    }

    void exchange::eosleft(asset out)
    {

        token_supply exchange_state(_self, _self);
         auto itr = exchange_state.cbegin(); 
         exchange_state.modify(itr, 0, [&](auto &a) {
         a.quote.balance -= out;
        });
    }

    