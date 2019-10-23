#include <sellbasket.hpp>

void sellbasket::convertfrom(asset in)
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
    int64_t out = int64_t(T);
    exchange_state.modify(itr, 0, [&](auto &a) {
        a.base.balance.amount += in.amount;
    });
    print("hello ------");
    print(asset(out, quote.symbol));
    asset outtoken = asset(out, quote.symbol);
    updatetoken(outtoken);
}

void sellbasket::addsupply(asset supply, asset base, asset quote)
{
    token_supply exchange_state(_self, _self);
    auto itr = exchange_state.find(supply.symbol.name());

    eosio_assert(itr == exchange_state.end(), "Currency already exists");

    exchange_state.emplace(_self, [&](auto &a) {
        a.supply = supply;
        a.base.balance = base;
        a.quote.balance = quote;
    });
    print("adding new currency");
    print("-------");
}

void sellbasket::updatesupply(asset supply, asset base, asset quote)
{
    token_supply exchange_state(_self, _self);
    const auto &itr = exchange_state.get(S(4, BSKT), "ram market does not exist");
    exchange_state.modify(itr, 0, [&](auto &a) {
        a.supply = supply;
        a.base.balance = base;
        a.quote.balance = quote;
    });
}

void sellbasket::updatetoken(asset out)
{

    token_supply exchange_state(_self, _self);
    auto itr = exchange_state.cbegin();
    exchange_state.modify(itr, 0, [&](auto &a) {
        a.quote.balance -= out;
    });
}

void sellbasket::addport(asset port)
{
    uint64_t maxsize = 64ll * 1024 * 1024 * 1024;
    uint64_t total_port_reserved = 0;

    require_auth(_self);
    token_supply exchange_state(_self, _self);

    uint64_t p = port.amount;
    eosio_assert(maxsize > p, "ram may only be increased"); /// decreasing ram might result market maker issues
    eosio_assert(p < 1024ll * 1024 * 1024 * 1024 * 1024, "ram size is unrealistic");
    eosio_assert(p > total_port_reserved, "attempt to set max below reserved");

    auto delta = int64_t(p) - int64_t(maxsize);
    auto itr = exchange_state.find(S(4, BSKT));
    exchange_state.modify(itr, 0, [&](auto &m) {
        m.base.balance.amount += p;
    });

    maxsize = p;
    print("hello-----------", maxsize);
}

void sellbasket::removeport(asset port)
{

    require_auth(_self);
    token_supply exchange_state(_self, _self);
    auto itr = exchange_state.find(port.symbol);
    uint64_t amount = itr->base.balance.amount;
    uint64_t p = port.amount;
    eosio_assert(amount > p, "insufficient balance of port");

    if (p == amount)
    {
        exchange_state.erase(itr);
    }
    else
    {
        auto itr = exchange_state.cbegin();
        exchange_state.modify(itr, 0, [&](auto &m) {
            m.base.balance.amount -= p;
        });
    }
}

