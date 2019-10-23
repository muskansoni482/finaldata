#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <string>
#include <cmath>

using namespace eosio;
using eosio::asset;
using eosio::symbol_type;
using std::pow;
using std::string;
typedef double real_type;

class exchange : public eosio::contract
{
  public:
    exchange(account_name self) : contract(self) {}

    // @abi action
    void convertto(asset in);
    // @abi action
    void convertfrom(asset in);
    // @abi action
    void addsupply(asset supply, asset base, asset quote);
    // @abi action
    void updatesupply(asset supply, asset base, asset quote);
    // @abi action
    void bsktleft(int64_t issued);
    // @abi action
    void eosleft(asset out);
    
    // @abi table token i64

    struct exchange_state
    {
        asset supply;

        struct connector
        {
            asset balance;
            double weight = .5;

            EOSLIB_SERIALIZE(connector, (balance)(weight))
        };

        connector base;
        connector quote;

        uint64_t primary_key() const { return supply.symbol; }

        EOSLIB_SERIALIZE(exchange_state, (supply)(base)(quote))
    };
    typedef eosio::multi_index<N(token), exchange_state> token_supply;
};

EOSIO_ABI(exchange , (convertto)(convertfrom)(addsupply)(updatesupply)(bsktleft)(eosleft))