#include <smarttoken.hpp>

/* void smarttoken::convert(asset in)
{

    token_supply connector(_self, _self);
    auto itr = connector.cbegin();
    asset supply = itr->supply;
    asset quote = itr->quote.balance;
    double weight = itr->quote.weight;

    real_type R(supply.amount);
    real_type C(quote.amount + in.amount);
    real_type F(weight);
    real_type T(in.amount);
    real_type ONE(1.0);

    real_type E = -R * (ONE - std::pow(ONE + T / C, F));

    int64_t issued = int64_t(E);
    connector.modify(itr, 0, [&](auto &a) {
        a.quote.balance.amount += in.amount;
    });

    print("-------");
    print(asset(issued, supply.symbol));
    bsktleft(issued);
}
 */
void smarttoken::addconnector(asset supply, asset base, asset quote,symbol_type symbol)
{
    token_supply connector(_self, _self);
    auto itr = connector.find(symbol);
    eosio_assert(itr == connector.end(), "Currency already exists");
    print(itr == connector.end());

    connector.emplace(_self, [&](auto &a) {
        a.supply = supply;
        a.base.balance = base;
        a.quote.balance = quote;
        a.symbol = symbol;
    });
    print("adding new connector");
    print("-------");
}
/* void smarttoken::bsktleft(int64_t issued)
{
    token_supply connector(_self, _self);
    auto itr = connector.cbegin();
    //auto itr1=connector.cend();
    asset base = itr->base.balance;
    double weight = itr->base.weight;
    connector.modify(itr, 0, [&](auto &a) {
        a.base.balance.amount -= issued;
    });
    print("---available portfolio token is :", itr->base.balance);
} */
/*   void smarttoken::updatesupply(asset supply,asset base,asset quote)
    {
        token_supply connector(_self,_self);
	   // auto itr=connector.find(supply.symbol.name());
        const auto& itr = connector.get(S(4,BSKT), "ram market does not exist");
        //eosio_assert(itr!=address.end(), "Account doesnt exist");
       // print(itr==connector.end());
        connector.modify(itr,0, [&](auto& a){
	        a.supply=supply;
            a.base.balance=base;
            a.quote.balance=quote;
	    });
        
    } */
