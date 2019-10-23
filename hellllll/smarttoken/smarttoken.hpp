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

class smarttoken : public eosio::contract
{
  public:
    smarttoken(account_name self) : contract(self) {}

    // @abi action
    void addsupply(asset supply, symbol_type sym);

    // @abi table token i64

    struct connector
    {
        asset supply;
        symbol_type symbol;
        double weight = .5;

        uint64_t primary_key() const { return symbol; }

        EOSLIB_SERIALIZE(connector, (supply)(symbol)(weight))
    };
    typedef eosio::multi_index<N(token), connector> token_supply;
};

EOSIO_ABI(smarttoken, (addsupply))