#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>
using namespace eosio;
using std::string;
class second : public eosio::contract {
  public:
      using contract::contract;
/// @abi table books i64
     
struct book{
account_name bname;
string author_name;
uint64_t id;
uint64_t price;
account_name primary_key() const {return bname;}
uint64_t by_price() const {return price;}
EOSLIB_SERIALIZE(book,(bname)(author_name)(id)(price))

};

typedef eosio::multi_index<N(books),book,
		indexed_by<N(price),
		const_mem_fun<book, uint64_t , &book::by_price>>> book_table;

 /// @abi action
 void create(const account_name bname,string& author_name, uint64_t id,uint64_t price)
{
require_auth(bname);
book_table book(_self,_self);
auto itr=book.find(bname);
if(itr==book.end())
{
print("already existing account here");
}
book.emplace(bname,[&] (auto& b)
{
b.bname=bname;
b.author_name=author_name;
b.id=id;
b.price=price;
});
print("proifle created hello");
}

/// @abi action
void byprice(uint64_t price)
{
book_table book(_self,_self);

auto price_index = book.get_index<N(price)>();
auto itr = price_index.lower_bound(price);
while(itr != price_index.end() && itr->price == price) 
{
print(name{itr->bname} , " has price " , itr->price , " \n");
++itr;
}
}
/// @abi action
void byrange(uint64_t lower,uint64_t upper)
{
book_table book(_self,_self);

auto price_index = book.get_index<N(price)>();
auto begin = price_index.lower_bound(lower);
auto end = price_index.upper_bound(upper);
for_each(begin,end,[&] (auto& b){
print(b.bname , " has price " , b.price , " \n");
});
}
};
EOSIO_ABI( second, (create)(byprice)(byrange))



