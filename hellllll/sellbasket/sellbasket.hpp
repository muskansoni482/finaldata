#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <cmath>
#include <string>

using namespace eosio;
using eosio::action;
using eosio::asset;
using eosio::permission_level;
using eosio::symbol_type;
using std::string;

class sellbasket : public contract
{
  public:
    sellbasket(account_name self) : contract(self) {}

    typedef double real_type;

    /// @abi action
    void convertfrom(asset in);

    /// @abi action
    void addsupply(asset supply, asset base, asset quote);

    /// @abi action
    void updatesupply(asset supply, asset base, asset quote);

    /// @abi action
    void updatetoken(asset out);

    /// @abi action
    void addport(asset port);

    /// @abi action
    void removeport(asset port);

    
        /// @abi table basket i64
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

    typedef eosio::multi_index<N(basket), exchange_state> token_supply;
};

EOSIO_ABI(sellbasket, (addsupply)(convertfrom)(updatesupply)(addport)(removeport))
