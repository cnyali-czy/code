// 旁边的同志说要我别怂
// 我就submit了
#define REP(i,s,e) for (register int i(s),end_##i(e); i <= end_##i; i++)
#define DEP(i,s,e) for (register int i(s),end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr,"Passing [%s] in Line %d\n",__FUNCTION__,__LINE__)
#define CLOCK cerr << clock() * 1. / CLOCKS_PER_SEC << endl

#define chkmax(a,b) (a < (b) ? a = (b) : a)
#define chkmin(a,b) (a > (b) ? a = (b) : a)

#include <bits/extc++.h>
#include <bits/stdc++.h>

//  Copyright Malte Skarupke 2017.
// Distributed under the Boost Software License,Version 1.0.
//(See http://www.boost.org/LICENSE_1_0.txt)
#define tpl template
#define tpn typename
#define opr operator
#define rtn return 
#define ile inline 

#ifdef _MSC_VER
#define SKA_NOINLINE(...) __declspec(noile) __VA_ARGS__
#else
#define SKA_NOINLINE(...) __VA_ARGS__ __attribute__((noile))
#endif

namespace ska
{
struct phc;
struct power_of_two_HASH_POLICY;
struct fibonacci_HASH_POLICY;

namespace d3
{
tpl<tpn Result,tpn Functor>
struct functor_storage : Functor
{
functor_storage() = default;
functor_storage(const Functor & functor)
: Functor(functor)
{
}
tpl<tpn... Args>
Result opr()(Args &&... args)
{
rtn static_cast<Functor &>(*this)(std::forward<Args>(args)...);
}
tpl<tpn... Args>
Result opr()(Args &&... args) const
{
rtn static_cast<const Functor &>(*this)(std::forward<Args>(args)...);
}
};
tpl<tpn Result,tpn... Args>
struct functor_storage<Result,Result (*)(Args...)>
{
typedef Result (*function_ptr)(Args...);
function_ptr function;
functor_storage(function_ptr function)
: function(function)
{
}
Result opr()(Args... args) const
{
rtn function(std::forward<Args>(args)...);
}
opr function_ptr &()
{
rtn function;
}
opr const function_ptr &()
{
rtn function;
}
};
tpl<tpn key_type,tpn value_type,tpn hasher>
struct KOVHSER : functor_storage<size_t,hasher>
{
typedef functor_storage<size_t,hasher> hasher_storage;
KOVHSER() = default;
KOVHSER(const hasher & hash)
: hasher_storage(hash)
{
}
size_t opr()(const key_type & key)
{
rtn static_cast<hasher_storage &>(*this)(key);
}
size_t opr()(const key_type & key) const
{
rtn static_cast<const hasher_storage &>(*this)(key);
}
size_t opr()(const value_type & value)
{
rtn static_cast<hasher_storage &>(*this)(value.first);
}
size_t opr()(const value_type & value) const
{
rtn static_cast<const hasher_storage &>(*this)(value.first);
}
tpl<tpn F,tpn S>
size_t opr()(const std::pair<F,S> & value)
{
rtn static_cast<hasher_storage &>(*this)(value.first);
}
tpl<tpn F,tpn S>
size_t opr()(const std::pair<F,S> & value) const
{
rtn static_cast<const hasher_storage &>(*this)(value.first);
}
};
tpl<tpn key_type,tpn value_type,tpn key_equal>
struct KOVEquality : functor_storage<bool,key_equal>
{
typedef functor_storage<bool,key_equal> equality_storage;
KOVEquality() = default;
KOVEquality(const key_equal & equality)
: equality_storage(equality)
{
}
bool opr()(const key_type & lhs,const key_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs,rhs);
}
bool opr()(const key_type & lhs,const value_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs,rhs.first);
}
bool opr()(const value_type & lhs,const key_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs);
}
bool opr()(const value_type & lhs,const value_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs.first);
}
tpl<tpn F,tpn S>
bool opr()(const key_type & lhs,const std::pair<F,S> & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs,rhs.first);
}
tpl<tpn F,tpn S>
bool opr()(const std::pair<F,S> & lhs,const key_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs);
}
tpl<tpn F,tpn S>
bool opr()(const value_type & lhs,const std::pair<F,S> & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs.first);
}
tpl<tpn F,tpn S>
bool opr()(const std::pair<F,S> & lhs,const value_type & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs.first);
}
tpl<tpn FL,tpn SL,tpn FR,tpn SR>
bool opr()(const std::pair<FL,SL> & lhs,const std::pair<FR,SR> & rhs)
{
rtn static_cast<equality_storage &>(*this)(lhs.first,rhs.first);
}
};
static constexpr int8_t min_lookups = 4;
tpl<tpn T>
struct sherwood_v3_entry
{
sherwood_v3_entry()
{
}
sherwood_v3_entry(int8_t distance_from_desired)
: distance_from_desired(distance_from_desired)
{
}
~sherwood_v3_entry()
{
}
static sherwood_v3_entry * empty_default_table()
{
static sherwood_v3_entry result[min_lookups] = {{},{},{},{special_end_value}};
rtn result;
}

bool has_value() const
{
rtn distance_from_desired >= 0;
}
bool is_empty() const
{
rtn distance_from_desired < 0;
}
bool is_at_desired_position() const
{
rtn distance_from_desired <= 0;
}
tpl<tpn... Args>
void emplace(int8_t distance,Args &&... args)
{
new (std::addressof(value)) T(std::forward<Args>(args)...);
distance_from_desired = distance;
}

void destroy_value()
{
value.~T();
distance_from_desired = -1;
}

int8_t distance_from_desired = -1;
static constexpr int8_t special_end_value = 0;
union {T value;};
};

ile int8_t log2(size_t value)
{
static constexpr int8_t table[64] =
{
63, 0,58, 1,59,47,53, 2,
60,39,48,27,54,33,42, 3,
61,51,37,40,49,18,28,20,
55,30,34,11,43,14,22, 4,
62,57,46,52,38,26,32,41,
50,36,17,19,29,10,13,21,
56,45,25,31,35,16, 9,12,
44,24,15, 8,23, 7, 6, 5
};
value |= value >> 1;
value |= value >> 2;
value |= value >> 4;
value |= value >> 8;
value |= value >> 16;
value |= value >> 32;
rtn table[((value - (value >> 1)) * 0x07EDD5E59A4E28C2) >> 58];
}

tpl<tpn T,bool>
struct AssignIfTrue
{
void opr()(T & lhs,const T & rhs)
{
lhs = rhs;
}
void opr()(T & lhs,T && rhs)
{
lhs = std::move(rhs);
}
};
tpl<tpn T>
struct AssignIfTrue<T,false>
{
void opr()(T &,const T &)
{
}
void opr()(T &,T &&)
{
}
};

ile size_t next_power_of_two(size_t i)
{
--i;
i |= i >> 1;
i |= i >> 2;
i |= i >> 4;
i |= i >> 8;
i |= i >> 16;
i |= i >> 32;
++i;
rtn i;
}

tpl<tpn...> using void_t = void;

tpl<tpn T,tpn = void>
struct HashPolicySelector
{
typedef fibonacci_HASH_POLICY Type;
};
tpl<tpn T>
struct HashPolicySelector<T,void_t<tpn T::HASH_POLICY> >
{
typedef tpn T::HASH_POLICY type;
};

tpl<tpn T,tpn FindKey,tpn ArgumentHash,tpn HSER,tpn ArgumentEqual,tpn Equal,tpn ArgumentAlloc,tpn EntryAlloc>
class sv3 : private EntryAlloc,private HSER,private Equal
{
using Entry = d3::sherwood_v3_entry<T>;
using AllocatorTraits = std::allocator_traits<EntryAlloc>;
using EntryPointer = tpn AllocatorTraits::pointer;
struct convertible_to_iterator;

public:

using value_type = T;
using size_type = size_t;
using difference_type = std::ptrdiff_t;
using hasher = ArgumentHash;
using key_equal = ArgumentEqual;
using allocator_type = EntryAlloc;
using reference = value_type &;
using const_reference = const value_type &;
using pointer = value_type *;
using const_pointer = const value_type *;

sv3()
{
}
explicit sv3(size_type bucket_count,const ArgumentHash & hash = ArgumentHash(),const ArgumentEqual & equal = ArgumentEqual(),const ArgumentAlloc & alloc = ArgumentAlloc())
: EntryAlloc(alloc),HSER(hash),Equal(equal)
{
rehash(bucket_count);
}
sv3(size_type bucket_count,const ArgumentAlloc & alloc)
: sv3(bucket_count,ArgumentHash(),ArgumentEqual(),alloc)
{
}
sv3(size_type bucket_count,const ArgumentHash & hash,const ArgumentAlloc & alloc)
: sv3(bucket_count,hash,ArgumentEqual(),alloc)
{
}
explicit sv3(const ArgumentAlloc & alloc)
: EntryAlloc(alloc)
{
}
tpl<tpn It>
sv3(It first,It last,size_type bucket_count = 0,const ArgumentHash & hash = ArgumentHash(),const ArgumentEqual & equal = ArgumentEqual(),const ArgumentAlloc & alloc = ArgumentAlloc())
: sv3(bucket_count,hash,equal,alloc)
{
insert(first,last);
}
tpl<tpn It>
sv3(It first,It last,size_type bucket_count,const ArgumentAlloc & alloc)
: sv3(first,last,bucket_count,ArgumentHash(),ArgumentEqual(),alloc)
{
}
tpl<tpn It>
sv3(It first,It last,size_type bucket_count,const ArgumentHash & hash,const ArgumentAlloc & alloc)
: sv3(first,last,bucket_count,hash,ArgumentEqual(),alloc)
{
}
sv3(std::initializer_list<T> il,size_type bucket_count = 0,const ArgumentHash & hash = ArgumentHash(),const ArgumentEqual & equal = ArgumentEqual(),const ArgumentAlloc & alloc = ArgumentAlloc())
: sv3(bucket_count,hash,equal,alloc)
{
if (bucket_count == 0)
rehash(il.size());
insert(il.begin(),il.end());
}
sv3(std::initializer_list<T> il,size_type bucket_count,const ArgumentAlloc & alloc)
: sv3(il,bucket_count,ArgumentHash(),ArgumentEqual(),alloc)
{
}
sv3(std::initializer_list<T> il,size_type bucket_count,const ArgumentHash & hash,const ArgumentAlloc & alloc)
: sv3(il,bucket_count,hash,ArgumentEqual(),alloc)
{
}
sv3(const sv3 & other)
: sv3(other,AllocatorTraits::select_on_container_copy_construction(other.get_allocator()))
{
}
sv3(const sv3 & other,const ArgumentAlloc & alloc)
: EntryAlloc(alloc),HSER(other),Equal(other),_max_load_factor(other._max_load_factor)
{
rehash_for_other_container(other);
try
{
insert(other.begin(),other.end());
}
catch(...)
{
clear();
deallocate_data(entries,num_slots_minus_one,max_lookups);
throw;
}
}
sv3(sv3 && other) noexcept
: EntryAlloc(std::move(other)),HSER(std::move(other)),Equal(std::move(other))
{
swap_pointers(other);
}
sv3(sv3 && other,const ArgumentAlloc & alloc) noexcept
: EntryAlloc(alloc),HSER(std::move(other)),Equal(std::move(other))
{
swap_pointers(other);
}
sv3 & opr=(const sv3 & other)
{
if (this == std::addressof(other))
rtn *this;

clear();
if (AllocatorTraits::propagate_on_container_copy_assignment::value)
{
if (static_cast<EntryAlloc &>(*this) != static_cast<const EntryAlloc &>(other))
{
reset_to_empty_state();
}
AssignIfTrue<EntryAlloc,AllocatorTraits::propagate_on_container_copy_assignment::value>()(*this,other);
}
_max_load_factor = other._max_load_factor;
static_cast<HSER &>(*this) = other;
static_cast<Equal &>(*this) = other;
rehash_for_other_container(other);
insert(other.begin(),other.end());
rtn *this;
}
sv3 & opr=(sv3 && other) noexcept
{
if (this == std::addressof(other))
rtn *this;
else if (AllocatorTraits::propagate_on_container_move_assignment::value)
{
clear();
reset_to_empty_state();
AssignIfTrue<EntryAlloc,AllocatorTraits::propagate_on_container_move_assignment::value>()(*this,std::move(other));
swap_pointers(other);
}
else if (static_cast<EntryAlloc &>(*this) == static_cast<EntryAlloc &>(other))
{
swap_pointers(other);
}
else
{
clear();
_max_load_factor = other._max_load_factor;
rehash_for_other_container(other);
for (T & elem : other)
emplace(std::move(elem));
other.clear();
}
static_cast<HSER &>(*this) = std::move(other);
static_cast<Equal &>(*this) = std::move(other);
rtn *this;
}
~sv3()
{
clear();
deallocate_data(entries,num_slots_minus_one,max_lookups);
}

const allocator_type & get_allocator() const
{
rtn static_cast<const allocator_type &>(*this);
}
const ArgumentEqual & key_eq() const
{
rtn static_cast<const ArgumentEqual &>(*this);
}
const ArgumentHash & hash_function() const
{
rtn static_cast<const ArgumentHash &>(*this);
}

tpl<tpn ValueType>
struct tpld_iterator
{
tpld_iterator() = default;
tpld_iterator(EntryPointer current)
: current(current)
{
}
EntryPointer current = EntryPointer();

using iterator_category = std::forward_iterator_tag;
using value_type = ValueType;
using difference_type = ptrdiff_t;
using pointer = ValueType *;
using reference = ValueType &;

friend bool opr==(const tpld_iterator & lhs,const tpld_iterator & rhs)
{
rtn lhs.current == rhs.current;
}
friend bool opr!=(const tpld_iterator & lhs,const tpld_iterator & rhs)
{
rtn !(lhs == rhs);
}

tpld_iterator & opr++()
{
do
{
++current;
}
while(current->is_empty());
rtn *this;
}
tpld_iterator opr++(int)
{
tpld_iterator copy(*this);
++*this;
rtn copy;
}

ValueType & opr*() const
{
rtn current->value;
}
ValueType * opr->() const
{
rtn std::addressof(current->value);
}

opr tpld_iterator<const value_type>() const
{
rtn {current};
}
};
using iterator = tpld_iterator<value_type>;
using const_iterator = tpld_iterator<const value_type>;

iterator begin()
{
for (EntryPointer it = entries;; ++it)
{
if (it->has_value())
rtn {it};
}
}
const_iterator begin() const
{
for (EntryPointer it = entries;; ++it)
{
if (it->has_value())
rtn {it};
}
}
const_iterator cbegin() const
{
rtn begin();
}
iterator end()
{
rtn {entries + static_cast<ptrdiff_t>(num_slots_minus_one + max_lookups)};
}
const_iterator end() const
{
rtn {entries + static_cast<ptrdiff_t>(num_slots_minus_one + max_lookups)};
}
const_iterator cend() const
{
rtn end();
}

iterator find(const FindKey & key)
{
size_t index = HASH_POLICY.index_for_hash(hash_object(key),num_slots_minus_one);
EntryPointer it = entries + ptrdiff_t(index);
for (int8_t distance = 0; it->distance_from_desired >= distance; ++distance,++it)
{
if (compares_equal(key,it->value))
rtn {it};
}
rtn end();
}
const_iterator find(const FindKey & key) const
{
rtn const_cast<sv3 *>(this)->find(key);
}
size_t count(const FindKey & key) const
{
rtn find(key) == end() ? 0 : 1;
}
std::pair<iterator,iterator> equal_range(const FindKey & key)
{
iterator found = find(key);
if (found == end())
rtn {found,found};
else
rtn {found,std::next(found)};
}
std::pair<const_iterator,const_iterator> equal_range(const FindKey & key) const
{
const_iterator found = find(key);
if (found == end())
rtn {found,found};
else
rtn {found,std::next(found)};
}

tpl<tpn Key,tpn... Args>
std::pair<iterator,bool> emplace(Key && key,Args &&... args)
{
size_t index = HASH_POLICY.index_for_hash(hash_object(key),num_slots_minus_one);
EntryPointer current_entry = entries + ptrdiff_t(index);
int8_t distance_from_desired = 0;
for (; current_entry->distance_from_desired >= distance_from_desired; ++current_entry,++distance_from_desired)
{
if (compares_equal(key,current_entry->value))
rtn {{current_entry},false};
}
rtn emplace_new_key(distance_from_desired,current_entry,std::forward<Key>(key),std::forward<Args>(args)...);
}

std::pair<iterator,bool> insert(const value_type & value)
{
rtn emplace(value);
}
std::pair<iterator,bool> insert(value_type && value)
{
rtn emplace(std::move(value));
}
tpl<tpn... Args>
iterator emplace_hint(const_iterator,Args &&... args)
{
rtn emplace(std::forward<Args>(args)...).first;
}
iterator insert(const_iterator,const value_type & value)
{
rtn emplace(value).first;
}
iterator insert(const_iterator,value_type && value)
{
rtn emplace(std::move(value)).first;
}

tpl<tpn It>
void insert(It begin,It end)
{
for (; begin != end; ++begin)
{
emplace(*begin);
}
}
void insert(std::initializer_list<value_type> il)
{
insert(il.begin(),il.end());
}

void rehash(size_t num_buckets)
{
num_buckets = std::max(num_buckets,static_cast<size_t>(std::ceil(num_elements / static_cast<double>(_max_load_factor))));
if (num_buckets == 0)
{
reset_to_empty_state();
rtn;
}
auto new_prime_index = HASH_POLICY.next_size_over(num_buckets);
if (num_buckets == bucket_count())
rtn;
int8_t new_max_lookups = compute_max_lookups(num_buckets);
EntryPointer new_buckets(AllocatorTraits::allocate(*this,num_buckets + new_max_lookups));
EntryPointer special_end_item = new_buckets + static_cast<ptrdiff_t>(num_buckets + new_max_lookups - 1);
for (EntryPointer it = new_buckets; it != special_end_item; ++it)
it->distance_from_desired = -1;
special_end_item->distance_from_desired = Entry::special_end_value;
std::swap(entries,new_buckets);
std::swap(num_slots_minus_one,num_buckets);
--num_slots_minus_one;
HASH_POLICY.commit(new_prime_index);
int8_t old_max_lookups = max_lookups;
max_lookups = new_max_lookups;
num_elements = 0;
for (EntryPointer it = new_buckets,end = it + static_cast<ptrdiff_t>(num_buckets + old_max_lookups); it != end; ++it)
{
if (it->has_value())
{
emplace(std::move(it->value));
it->destroy_value();
}
}
deallocate_data(new_buckets,num_buckets,old_max_lookups);
}

void reserve(size_t num_elements)
{
size_t required_buckets = num_buckets_for_reserve(num_elements);
if (required_buckets > bucket_count())
rehash(required_buckets);
}

// the rtn value is a type that can be converted to an iterator
// the reason for doing this is that it's not free to find the
// iterator pointing at the next element. if you care about the
// next iterator,turn the rtn value into an iterator
convertible_to_iterator erase(const_iterator to_erase)
{
EntryPointer current = to_erase.current;
current->destroy_value();
--num_elements;
for (EntryPointer next = current + ptrdiff_t(1); !next->is_at_desired_position(); ++current,++next)
{
current->emplace(next->distance_from_desired - 1,std::move(next->value));
next->destroy_value();
}
rtn {to_erase.current};
}

iterator erase(const_iterator begin_it,const_iterator end_it)
{
if (begin_it == end_it)
rtn {begin_it.current};
for (EntryPointer it = begin_it.current,end = end_it.current; it != end; ++it)
{
if (it->has_value())
{
it->destroy_value();
--num_elements;
}
}
if (end_it == this->end())
rtn this->end();
ptrdiff_t num_to_move = std::min(static_cast<ptrdiff_t>(end_it.current->distance_from_desired),end_it.current - begin_it.current);
EntryPointer to_rtn = end_it.current - num_to_move;
for (EntryPointer it = end_it.current; !it->is_at_desired_position();)
{
EntryPointer target = it - num_to_move;
target->emplace(it->distance_from_desired - num_to_move,std::move(it->value));
it->destroy_value();
++it;
num_to_move = std::min(static_cast<ptrdiff_t>(it->distance_from_desired),num_to_move);
}
rtn {to_rtn};
}

size_t erase(const FindKey & key)
{
auto found = find(key);
if (found == end())
rtn 0;
else
{
erase(found);
rtn 1;
}
}

void clear()
{
for (EntryPointer it = entries,end = it + static_cast<ptrdiff_t>(num_slots_minus_one + max_lookups); it != end; ++it)
{
if (it->has_value())
it->destroy_value();
}
num_elements = 0;
}

void shrink_to_fit()
{
rehash_for_other_container(*this);
}

void swap(sv3 & other)
{
using std::swap;
swap_pointers(other);
swap(static_cast<ArgumentHash &>(*this),static_cast<ArgumentHash &>(other));
swap(static_cast<ArgumentEqual &>(*this),static_cast<ArgumentEqual &>(other));
if (AllocatorTraits::propagate_on_container_swap::value)
swap(static_cast<EntryAlloc &>(*this),static_cast<EntryAlloc &>(other));
}

size_t size() const
{
rtn num_elements;
}
size_t max_size() const
{
rtn (AllocatorTraits::max_size(*this)) / sizeof(Entry);
}
size_t bucket_count() const
{
rtn num_slots_minus_one ? num_slots_minus_one + 1 : 0;
}
size_type max_bucket_count() const
{
rtn (AllocatorTraits::max_size(*this) - min_lookups) / sizeof(Entry);
}
size_t bucket(const FindKey & key) const
{
rtn HASH_POLICY.index_for_hash(hash_object(key),num_slots_minus_one);
}
float load_factor() const
{
size_t buckets = bucket_count();
if (buckets)
rtn static_cast<float>(num_elements) / bucket_count();
else
rtn 0;
}
void max_load_factor(float value)
{
_max_load_factor = value;
}
float max_load_factor() const
{
rtn _max_load_factor;
}

bool empty() const
{
rtn num_elements == 0;
}

private:
EntryPointer entries = Entry::empty_default_table();
size_t num_slots_minus_one = 0;
tpn HashPolicySelector<ArgumentHash>::type HASH_POLICY;
int8_t max_lookups = d3::min_lookups - 1;
float _max_load_factor = 0.5f;
size_t num_elements = 0;

static int8_t compute_max_lookups(size_t num_buckets)
{
int8_t desired = d3::log2(num_buckets);
rtn std::max(d3::min_lookups,desired);
}

size_t num_buckets_for_reserve(size_t num_elements) const
{
rtn static_cast<size_t>(std::ceil(num_elements / std::min(0.5,static_cast<double>(_max_load_factor))));
}
void rehash_for_other_container(const sv3 & other)
{
rehash(std::min(num_buckets_for_reserve(other.size()),other.bucket_count()));
}

void swap_pointers(sv3 & other)
{
using std::swap;
swap(HASH_POLICY,other.HASH_POLICY);
swap(entries,other.entries);
swap(num_slots_minus_one,other.num_slots_minus_one);
swap(num_elements,other.num_elements);
swap(max_lookups,other.max_lookups);
swap(_max_load_factor,other._max_load_factor);
}

tpl<tpn Key,tpn... Args>
SKA_NOINLINE(std::pair<iterator,bool>) emplace_new_key(int8_t distance_from_desired,EntryPointer current_entry,Key && key,Args &&... args)
{
using std::swap;
if (num_slots_minus_one == 0 || distance_from_desired == max_lookups || num_elements + 1 > (num_slots_minus_one + 1) * static_cast<double>(_max_load_factor))
{
grow();
rtn emplace(std::forward<Key>(key),std::forward<Args>(args)...);
}
else if (current_entry->is_empty())
{
current_entry->emplace(distance_from_desired,std::forward<Key>(key),std::forward<Args>(args)...);
++num_elements;
rtn {{current_entry},true};
}
value_type to_insert(std::forward<Key>(key),std::forward<Args>(args)...);
swap(distance_from_desired,current_entry->distance_from_desired);
swap(to_insert,current_entry->value);
iterator result = {current_entry};
for (++distance_from_desired,++current_entry;; ++current_entry)
{
if (current_entry->is_empty())
{
current_entry->emplace(distance_from_desired,std::move(to_insert));
++num_elements;
rtn {result,true};
}
else if (current_entry->distance_from_desired < distance_from_desired)
{
swap(distance_from_desired,current_entry->distance_from_desired);
swap(to_insert,current_entry->value);
++distance_from_desired;
}
else
{
++distance_from_desired;
if (distance_from_desired == max_lookups)
{
swap(to_insert,result.current->value);
grow();
rtn emplace(std::move(to_insert));
}
}
}
}

void grow()
{
rehash(std::max(size_t(4),2 * bucket_count()));
}

void deallocate_data(EntryPointer begin,size_t num_slots_minus_one,int8_t max_lookups)
{
if (begin != Entry::empty_default_table())
{
AllocatorTraits::deallocate(*this,begin,num_slots_minus_one + max_lookups + 1);
}
}

void reset_to_empty_state()
{
deallocate_data(entries,num_slots_minus_one,max_lookups);
entries = Entry::empty_default_table();
num_slots_minus_one = 0;
HASH_POLICY.reset();
max_lookups = d3::min_lookups - 1;
}

tpl<tpn U>
size_t hash_object(const U & key)
{
rtn static_cast<HSER &>(*this)(key);
}
tpl<tpn U>
size_t hash_object(const U & key) const
{
rtn static_cast<const HSER &>(*this)(key);
}
tpl<tpn L,tpn R>
bool compares_equal(const L & lhs,const R & rhs)
{
rtn static_cast<Equal &>(*this)(lhs,rhs);
}

struct convertible_to_iterator
{
EntryPointer it;

opr iterator()
{
if (it->has_value())
rtn {it};
else
rtn ++iterator{it};
}
opr const_iterator()
{
if (it->has_value())
rtn {it};
else
rtn ++const_iterator{it};
}
};

};
}

#define sst static size_t
struct phc
{
sst mod0(size_t) {rtn 0llu;}
sst mod2(size_t hash) {rtn hash % 2llu;}
sst mod3(size_t hash) {rtn hash % 3llu;}
sst mod5(size_t hash) {rtn hash % 5llu;}
sst mod7(size_t hash) {rtn hash % 7llu;}
sst mod11(size_t hash) {rtn hash % 11llu;}
sst mod13(size_t hash) {rtn hash % 13llu;}
sst mod17(size_t hash) {rtn hash % 17llu;}
sst mod23(size_t hash) {rtn hash % 23llu;}
sst mod29(size_t hash) {rtn hash % 29llu;}
sst mod37(size_t hash) {rtn hash % 37llu;}
sst mod47(size_t hash) {rtn hash % 47llu;}
sst mod59(size_t hash) {rtn hash % 59llu;}
sst mod73(size_t hash) {rtn hash % 73llu;}
sst mod97(size_t hash) {rtn hash % 97llu;}
sst mod127(size_t hash) {rtn hash % 127llu;}
sst mod151(size_t hash) {rtn hash % 151llu;}
sst mod197(size_t hash) {rtn hash % 197llu;}
sst mod251(size_t hash) {rtn hash % 251llu;}
sst mod313(size_t hash) {rtn hash % 313llu;}
sst mod397(size_t hash) {rtn hash % 397llu;}
sst mod499(size_t hash) {rtn hash % 499llu;}
sst mod631(size_t hash) {rtn hash % 631llu;}
sst mod797(size_t hash) {rtn hash % 797llu;}
sst mod1009(size_t hash) {rtn hash % 1009llu;}
sst mod1259(size_t hash) {rtn hash % 1259llu;}
sst mod1597(size_t hash) {rtn hash % 1597llu;}
sst mod2011(size_t hash) {rtn hash % 2011llu;}
sst mod2539(size_t hash) {rtn hash % 2539llu;}
sst mod3203(size_t hash) {rtn hash % 3203llu;}
sst mod4027(size_t hash) {rtn hash % 4027llu;}
sst mod5087(size_t hash) {rtn hash % 5087llu;}
sst mod6421(size_t hash) {rtn hash % 6421llu;}
sst mod8089(size_t hash) {rtn hash % 8089llu;}
sst mod10193(size_t hash) {rtn hash % 10193llu;}
sst mod12853(size_t hash) {rtn hash % 12853llu;}
sst mod16193(size_t hash) {rtn hash % 16193llu;}
sst mod20399(size_t hash) {rtn hash % 20399llu;}
sst mod25717(size_t hash) {rtn hash % 25717llu;}
sst mod32401(size_t hash) {rtn hash % 32401llu;}
sst mod40823(size_t hash) {rtn hash % 40823llu;}
sst mod51437(size_t hash) {rtn hash % 51437llu;}
sst mod64811(size_t hash) {rtn hash % 64811llu;}
sst mod81649(size_t hash) {rtn hash % 81649llu;}
sst mod102877(size_t hash) {rtn hash % 102877llu;}
sst mod129607(size_t hash) {rtn hash % 129607llu;}
sst mod163307(size_t hash) {rtn hash % 163307llu;}
sst mod205759(size_t hash) {rtn hash % 205759llu;}
sst mod259229(size_t hash) {rtn hash % 259229llu;}
sst mod326617(size_t hash) {rtn hash % 326617llu;}
sst mod411527(size_t hash) {rtn hash % 411527llu;}
sst mod518509(size_t hash) {rtn hash % 518509llu;}
sst mod653267(size_t hash) {rtn hash % 653267llu;}
sst mod823117(size_t hash) {rtn hash % 823117llu;}
sst mod1037059(size_t hash) {rtn hash % 1037059llu;}
sst mod1306601(size_t hash) {rtn hash % 1306601llu;}
sst mod1646237(size_t hash) {rtn hash % 1646237llu;}
sst mod2074129(size_t hash) {rtn hash % 2074129llu;}
sst mod2613229(size_t hash) {rtn hash % 2613229llu;}
sst mod3292489(size_t hash) {rtn hash % 3292489llu;}
sst mod4148279(size_t hash) {rtn hash % 4148279llu;}
sst mod5226491(size_t hash) {rtn hash % 5226491llu;}
sst mod6584983(size_t hash) {rtn hash % 6584983llu;}
sst mod8296553(size_t hash) {rtn hash % 8296553llu;}
sst mod10453007(size_t hash) {rtn hash % 10453007llu;}
sst mod13169977(size_t hash) {rtn hash % 13169977llu;}
sst mod16593127(size_t hash) {rtn hash % 16593127llu;}
sst mod20906033(size_t hash) {rtn hash % 20906033llu;}
sst mod26339969(size_t hash) {rtn hash % 26339969llu;}
sst mod33186281(size_t hash) {rtn hash % 33186281llu;}
sst mod41812097(size_t hash) {rtn hash % 41812097llu;}
sst mod52679969(size_t hash) {rtn hash % 52679969llu;}
sst mod66372617(size_t hash) {rtn hash % 66372617llu;}
sst mod83624237(size_t hash) {rtn hash % 83624237llu;}
sst mod105359939(size_t hash) {rtn hash % 105359939llu;}
sst mod132745199(size_t hash) {rtn hash % 132745199llu;}
sst mod167248483(size_t hash) {rtn hash % 167248483llu;}
sst mod210719881(size_t hash) {rtn hash % 210719881llu;}
sst mod265490441(size_t hash) {rtn hash % 265490441llu;}
sst mod334496971(size_t hash) {rtn hash % 334496971llu;}
sst mod421439783(size_t hash) {rtn hash % 421439783llu;}
sst mod530980861(size_t hash) {rtn hash % 530980861llu;}
sst mod668993977(size_t hash) {rtn hash % 668993977llu;}
sst mod842879579(size_t hash) {rtn hash % 842879579llu;}
sst mod1061961721(size_t hash) {rtn hash % 1061961721llu;}
sst mod1337987929(size_t hash) {rtn hash % 1337987929llu;}
sst mod1685759167(size_t hash) {rtn hash % 1685759167llu;}
sst mod2123923447(size_t hash) {rtn hash % 2123923447llu;}
sst mod2675975881(size_t hash) {rtn hash % 2675975881llu;}
sst mod3371518343(size_t hash) {rtn hash % 3371518343llu;}
sst mod4247846927(size_t hash) {rtn hash % 4247846927llu;}
sst mod5351951779(size_t hash) {rtn hash % 5351951779llu;}
sst mod6743036717(size_t hash) {rtn hash % 6743036717llu;}
sst mod8495693897(size_t hash) {rtn hash % 8495693897llu;}
sst mod10703903591(size_t hash) {rtn hash % 10703903591llu;}
sst mod13486073473(size_t hash) {rtn hash % 13486073473llu;}
sst mod16991387857(size_t hash) {rtn hash % 16991387857llu;}
sst mod21407807219(size_t hash) {rtn hash % 21407807219llu;}
sst mod26972146961(size_t hash) {rtn hash % 26972146961llu;}
sst mod33982775741(size_t hash) {rtn hash % 33982775741llu;}
sst mod42815614441(size_t hash) {rtn hash % 42815614441llu;}
sst mod53944293929(size_t hash) {rtn hash % 53944293929llu;}
sst mod67965551447(size_t hash) {rtn hash % 67965551447llu;}
sst mod85631228929(size_t hash) {rtn hash % 85631228929llu;}
sst mod107888587883(size_t hash) {rtn hash % 107888587883llu;}
sst mod135931102921(size_t hash) {rtn hash % 135931102921llu;}
sst mod171262457903(size_t hash) {rtn hash % 171262457903llu;}
sst mod215777175787(size_t hash) {rtn hash % 215777175787llu;}
sst mod271862205833(size_t hash) {rtn hash % 271862205833llu;}
sst mod342524915839(size_t hash) {rtn hash % 342524915839llu;}
sst mod431554351609(size_t hash) {rtn hash % 431554351609llu;}
sst mod543724411781(size_t hash) {rtn hash % 543724411781llu;}
sst mod685049831731(size_t hash) {rtn hash % 685049831731llu;}
sst mod863108703229(size_t hash) {rtn hash % 863108703229llu;}
sst mod1087448823553(size_t hash) {rtn hash % 1087448823553llu;}
sst mod1370099663459(size_t hash) {rtn hash % 1370099663459llu;}
sst mod1726217406467(size_t hash) {rtn hash % 1726217406467llu;}
sst mod2174897647073(size_t hash) {rtn hash % 2174897647073llu;}
sst mod2740199326961(size_t hash) {rtn hash % 2740199326961llu;}
sst mod3452434812973(size_t hash) {rtn hash % 3452434812973llu;}
sst mod4349795294267(size_t hash) {rtn hash % 4349795294267llu;}
sst mod5480398654009(size_t hash) {rtn hash % 5480398654009llu;}
sst mod6904869625999(size_t hash) {rtn hash % 6904869625999llu;}
sst mod8699590588571(size_t hash) {rtn hash % 8699590588571llu;}
sst mod10960797308051(size_t hash) {rtn hash % 10960797308051llu;}
sst mod13809739252051(size_t hash) {rtn hash % 13809739252051llu;}
sst mod17399181177241(size_t hash) {rtn hash % 17399181177241llu;}
sst mod21921594616111(size_t hash) {rtn hash % 21921594616111llu;}
sst mod27619478504183(size_t hash) {rtn hash % 27619478504183llu;}
sst mod34798362354533(size_t hash) {rtn hash % 34798362354533llu;}
sst mod43843189232363(size_t hash) {rtn hash % 43843189232363llu;}
sst mod55238957008387(size_t hash) {rtn hash % 55238957008387llu;}
sst mod69596724709081(size_t hash) {rtn hash % 69596724709081llu;}
sst mod87686378464759(size_t hash) {rtn hash % 87686378464759llu;}
sst mod110477914016779(size_t hash) {rtn hash % 110477914016779llu;}
sst mod139193449418173(size_t hash) {rtn hash % 139193449418173llu;}
sst mod175372756929481(size_t hash) {rtn hash % 175372756929481llu;}
sst mod220955828033581(size_t hash) {rtn hash % 220955828033581llu;}
sst mod278386898836457(size_t hash) {rtn hash % 278386898836457llu;}
sst mod350745513859007(size_t hash) {rtn hash % 350745513859007llu;}
sst mod441911656067171(size_t hash) {rtn hash % 441911656067171llu;}
sst mod556773797672909(size_t hash) {rtn hash % 556773797672909llu;}
sst mod701491027718027(size_t hash) {rtn hash % 701491027718027llu;}
sst mod883823312134381(size_t hash) {rtn hash % 883823312134381llu;}
sst mod1113547595345903(size_t hash) {rtn hash % 1113547595345903llu;}
sst mod1402982055436147(size_t hash) {rtn hash % 1402982055436147llu;}
sst mod1767646624268779(size_t hash) {rtn hash % 1767646624268779llu;}
sst mod2227095190691797(size_t hash) {rtn hash % 2227095190691797llu;}
sst mod2805964110872297(size_t hash) {rtn hash % 2805964110872297llu;}
sst mod3535293248537579(size_t hash) {rtn hash % 3535293248537579llu;}
sst mod4454190381383713(size_t hash) {rtn hash % 4454190381383713llu;}
sst mod5611928221744609(size_t hash) {rtn hash % 5611928221744609llu;}
sst mod7070586497075177(size_t hash) {rtn hash % 7070586497075177llu;}
sst mod8908380762767489(size_t hash) {rtn hash % 8908380762767489llu;}
sst mod11223856443489329(size_t hash) {rtn hash % 11223856443489329llu;}
sst mod14141172994150357(size_t hash) {rtn hash % 14141172994150357llu;}
sst mod17816761525534927(size_t hash) {rtn hash % 17816761525534927llu;}
sst mod22447712886978529(size_t hash) {rtn hash % 22447712886978529llu;}
sst mod28282345988300791(size_t hash) {rtn hash % 28282345988300791llu;}
sst mod35633523051069991(size_t hash) {rtn hash % 35633523051069991llu;}
sst mod44895425773957261(size_t hash) {rtn hash % 44895425773957261llu;}
sst mod56564691976601587(size_t hash) {rtn hash % 56564691976601587llu;}
sst mod71267046102139967(size_t hash) {rtn hash % 71267046102139967llu;}
sst mod89790851547914507(size_t hash) {rtn hash % 89790851547914507llu;}
sst mod113129383953203213(size_t hash) {rtn hash % 113129383953203213llu;}
sst mod142534092204280003(size_t hash) {rtn hash % 142534092204280003llu;}
sst mod179581703095829107(size_t hash) {rtn hash % 179581703095829107llu;}
sst mod226258767906406483(size_t hash) {rtn hash % 226258767906406483llu;}
sst mod285068184408560057(size_t hash) {rtn hash % 285068184408560057llu;}
sst mod359163406191658253(size_t hash) {rtn hash % 359163406191658253llu;}
sst mod452517535812813007(size_t hash) {rtn hash % 452517535812813007llu;}
sst mod570136368817120201(size_t hash) {rtn hash % 570136368817120201llu;}
sst mod718326812383316683(size_t hash) {rtn hash % 718326812383316683llu;}
sst mod905035071625626043(size_t hash) {rtn hash % 905035071625626043llu;}
sst mod1140272737634240411(size_t hash) {rtn hash % 1140272737634240411llu;}
sst mod1436653624766633509(size_t hash) {rtn hash % 1436653624766633509llu;}
sst mod1810070143251252131(size_t hash) {rtn hash % 1810070143251252131llu;}
sst mod2280545475268481167(size_t hash) {rtn hash % 2280545475268481167llu;}
sst mod2873307249533267101(size_t hash) {rtn hash % 2873307249533267101llu;}
sst mod3620140286502504283(size_t hash) {rtn hash % 3620140286502504283llu;}
sst mod4561090950536962147(size_t hash) {rtn hash % 4561090950536962147llu;}
sst mod5746614499066534157(size_t hash) {rtn hash % 5746614499066534157llu;}
sst mod7240280573005008577(size_t hash) {rtn hash % 7240280573005008577llu;}
sst mod9122181901073924329(size_t hash) {rtn hash % 9122181901073924329llu;}
sst mod11493228998133068689(size_t hash) {rtn hash % 11493228998133068689llu;}
sst mod14480561146010017169(size_t hash) {rtn hash % 14480561146010017169llu;}
sst mod18446744073709551557(size_t hash) {rtn hash % 18446744073709551557llu;}

using mod_function = size_t (*)(size_t);

mod_function next_size_over(size_t & size) const
{
static constexpr const size_t prime_list[] =
{
2llu,3llu,5llu,7llu,11llu,13llu,17llu,23llu,29llu,37llu,47llu,
59llu,73llu,97llu,127llu,151llu,197llu,251llu,313llu,397llu,
499llu,631llu,797llu,1009llu,1259llu,1597llu,2011llu,2539llu,
3203llu,4027llu,5087llu,6421llu,8089llu,10193llu,12853llu,16193llu,
20399llu,25717llu,32401llu,40823llu,51437llu,64811llu,81649llu,
102877llu,129607llu,163307llu,205759llu,259229llu,326617llu,
411527llu,518509llu,653267llu,823117llu,1037059llu,1306601llu,
1646237llu,2074129llu,2613229llu,3292489llu,4148279llu,5226491llu,
6584983llu,8296553llu,10453007llu,13169977llu,16593127llu,20906033llu,
26339969llu,33186281llu,41812097llu,52679969llu,66372617llu,
83624237llu,105359939llu,132745199llu,167248483llu,210719881llu,
265490441llu,334496971llu,421439783llu,530980861llu,668993977llu,
842879579llu,1061961721llu,1337987929llu,1685759167llu,2123923447llu,
2675975881llu,3371518343llu,4247846927llu,5351951779llu,6743036717llu,
8495693897llu,10703903591llu,13486073473llu,16991387857llu,
21407807219llu,26972146961llu,33982775741llu,42815614441llu,
53944293929llu,67965551447llu,85631228929llu,107888587883llu,
135931102921llu,171262457903llu,215777175787llu,271862205833llu,
342524915839llu,431554351609llu,543724411781llu,685049831731llu,
863108703229llu,1087448823553llu,1370099663459llu,1726217406467llu,
2174897647073llu,2740199326961llu,3452434812973llu,4349795294267llu,
5480398654009llu,6904869625999llu,8699590588571llu,10960797308051llu,
13809739252051llu,17399181177241llu,21921594616111llu,27619478504183llu,
34798362354533llu,43843189232363llu,55238957008387llu,69596724709081llu,
87686378464759llu,110477914016779llu,139193449418173llu,
175372756929481llu,220955828033581llu,278386898836457llu,
350745513859007llu,441911656067171llu,556773797672909llu,
701491027718027llu,883823312134381llu,1113547595345903llu,
1402982055436147llu,1767646624268779llu,2227095190691797llu,
2805964110872297llu,3535293248537579llu,4454190381383713llu,
5611928221744609llu,7070586497075177llu,8908380762767489llu,
11223856443489329llu,14141172994150357llu,17816761525534927llu,
22447712886978529llu,28282345988300791llu,35633523051069991llu,
44895425773957261llu,56564691976601587llu,71267046102139967llu,
89790851547914507llu,113129383953203213llu,142534092204280003llu,
179581703095829107llu,226258767906406483llu,285068184408560057llu,
359163406191658253llu,452517535812813007llu,570136368817120201llu,
718326812383316683llu,905035071625626043llu,1140272737634240411llu,
1436653624766633509llu,1810070143251252131llu,2280545475268481167llu,
2873307249533267101llu,3620140286502504283llu,4561090950536962147llu,
5746614499066534157llu,7240280573005008577llu,9122181901073924329llu,
11493228998133068689llu,14480561146010017169llu,18446744073709551557llu
};
static constexpr size_t (* const mod_functions[])(size_t) =
{
&mod0,&mod2,&mod3,&mod5,&mod7,&mod11,&mod13,&mod17,&mod23,&mod29,&mod37,
&mod47,&mod59,&mod73,&mod97,&mod127,&mod151,&mod197,&mod251,&mod313,&mod397,
&mod499,&mod631,&mod797,&mod1009,&mod1259,&mod1597,&mod2011,&mod2539,&mod3203,
&mod4027,&mod5087,&mod6421,&mod8089,&mod10193,&mod12853,&mod16193,&mod20399,
&mod25717,&mod32401,&mod40823,&mod51437,&mod64811,&mod81649,&mod102877,
&mod129607,&mod163307,&mod205759,&mod259229,&mod326617,&mod411527,&mod518509,
&mod653267,&mod823117,&mod1037059,&mod1306601,&mod1646237,&mod2074129,
&mod2613229,&mod3292489,&mod4148279,&mod5226491,&mod6584983,&mod8296553,
&mod10453007,&mod13169977,&mod16593127,&mod20906033,&mod26339969,&mod33186281,
&mod41812097,&mod52679969,&mod66372617,&mod83624237,&mod105359939,&mod132745199,
&mod167248483,&mod210719881,&mod265490441,&mod334496971,&mod421439783,
&mod530980861,&mod668993977,&mod842879579,&mod1061961721,&mod1337987929,
&mod1685759167,&mod2123923447,&mod2675975881,&mod3371518343,&mod4247846927,
&mod5351951779,&mod6743036717,&mod8495693897,&mod10703903591,&mod13486073473,
&mod16991387857,&mod21407807219,&mod26972146961,&mod33982775741,&mod42815614441,
&mod53944293929,&mod67965551447,&mod85631228929,&mod107888587883,&mod135931102921,
&mod171262457903,&mod215777175787,&mod271862205833,&mod342524915839,
&mod431554351609,&mod543724411781,&mod685049831731,&mod863108703229,
&mod1087448823553,&mod1370099663459,&mod1726217406467,&mod2174897647073,
&mod2740199326961,&mod3452434812973,&mod4349795294267,&mod5480398654009,
&mod6904869625999,&mod8699590588571,&mod10960797308051,&mod13809739252051,
&mod17399181177241,&mod21921594616111,&mod27619478504183,&mod34798362354533,
&mod43843189232363,&mod55238957008387,&mod69596724709081,&mod87686378464759,
&mod110477914016779,&mod139193449418173,&mod175372756929481,&mod220955828033581,
&mod278386898836457,&mod350745513859007,&mod441911656067171,&mod556773797672909,
&mod701491027718027,&mod883823312134381,&mod1113547595345903,&mod1402982055436147,
&mod1767646624268779,&mod2227095190691797,&mod2805964110872297,&mod3535293248537579,
&mod4454190381383713,&mod5611928221744609,&mod7070586497075177,&mod8908380762767489,
&mod11223856443489329,&mod14141172994150357,&mod17816761525534927,
&mod22447712886978529,&mod28282345988300791,&mod35633523051069991,
&mod44895425773957261,&mod56564691976601587,&mod71267046102139967,
&mod89790851547914507,&mod113129383953203213,&mod142534092204280003,
&mod179581703095829107,&mod226258767906406483,&mod285068184408560057,
&mod359163406191658253,&mod452517535812813007,&mod570136368817120201,
&mod718326812383316683,&mod905035071625626043,&mod1140272737634240411,
&mod1436653624766633509,&mod1810070143251252131,&mod2280545475268481167,
&mod2873307249533267101,&mod3620140286502504283,&mod4561090950536962147,
&mod5746614499066534157,&mod7240280573005008577,&mod9122181901073924329,
&mod11493228998133068689,&mod14480561146010017169,&mod18446744073709551557
};
const size_t * found = std::lower_bound(std::begin(prime_list),std::end(prime_list) - 1,size);
size = *found;
rtn mod_functions[1 + found - prime_list];
}
void commit(mod_function new_mod_function)
{
current_mod_function = new_mod_function;
}
void reset()
{
current_mod_function = &mod0;
}

size_t index_for_hash(size_t hash,size_t /*num_slots_minus_one*/) const
{
rtn current_mod_function(hash);
}
size_t keep_in_range(size_t index,size_t num_slots_minus_one) const
{
rtn index > num_slots_minus_one ? current_mod_function(index) : index;
}

private:
mod_function current_mod_function = &mod0;
};

struct power_of_two_HASH_POLICY
{
size_t index_for_hash(size_t hash,size_t num_slots_minus_one) const
{
rtn hash & num_slots_minus_one;
}
size_t keep_in_range(size_t index,size_t num_slots_minus_one) const
{
rtn index_for_hash(index,num_slots_minus_one);
}
int8_t next_size_over(size_t & size) const
{
size = d3::next_power_of_two(size);
rtn 0;
}
void commit(int8_t)
{
}
void reset()
{
}

};

struct fibonacci_HASH_POLICY
{
size_t index_for_hash(size_t hash,size_t /*num_slots_minus_one*/) const
{
rtn (11400714819323198485ull * hash) >> shift;
}
size_t keep_in_range(size_t index,size_t num_slots_minus_one) const
{
rtn index & num_slots_minus_one;
}

int8_t next_size_over(size_t & size) const
{
size = std::max(size_t(2),d3::next_power_of_two(size));
rtn 64 - d3::log2(size);
}
void commit(int8_t shift)
{
this->shift = shift;
}
void reset()
{
shift = 63;
}

private:
int8_t shift = 63;
};

tpl<tpn K,tpn V,tpn H = std::hash<K>,tpn E = std::equal_to<K>,tpn A = std::allocator<std::pair<K,V> > >
class flat_hash_map
: public d3::sv3
<
std::pair<K,V>,
K,
H,
d3::KOVHSER<K,std::pair<K,V>,H>,
E,
d3::KOVEquality<K,std::pair<K,V>,E>,
A,
tpn std::allocator_traits<A>::tpl rebind_alloc<d3::sherwood_v3_entry<std::pair<K,V> > >
>
{
using Table = d3::sv3
<
std::pair<K,V>,
K,
H,
d3::KOVHSER<K,std::pair<K,V>,H>,
E,
d3::KOVEquality<K,std::pair<K,V>,E>,
A,
tpn std::allocator_traits<A>::tpl rebind_alloc<d3::sherwood_v3_entry<std::pair<K,V> > >
>;
public:

using key_type = K;
using mapped_type = V;

using Table::Table;
flat_hash_map()
{
}

ile V & opr[](const K & key)
{
rtn emplace(key,convertible_to_value()).first->second;
}
ile V & opr[](K && key)
{
rtn emplace(std::move(key),convertible_to_value()).first->second;
}
V & at(const K & key)
{
auto found = this->find(key);
if (found == this->end())
throw std::out_of_range("Argument passed to at() was not in the map.");
rtn found->second;
}
const V & at(const K & key) const
{
auto found = this->find(key);
if (found == this->end())
throw std::out_of_range("Argument passed to at() was not in the map.");
rtn found->second;
}

using Table::emplace;
std::pair<tpn Table::iterator,bool> emplace()
{
rtn emplace(key_type(),convertible_to_value());
}
tpl<tpn M>
std::pair<tpn Table::iterator,bool> insert_or_assign(const key_type & key,M && m)
{
auto emplace_result = emplace(key,std::forward<M>(m));
if (!emplace_result.second)
emplace_result.first->second = std::forward<M>(m);
rtn emplace_result;
}
tpl<tpn M>
std::pair<tpn Table::iterator,bool> insert_or_assign(key_type && key,M && m)
{
auto emplace_result = emplace(std::move(key),std::forward<M>(m));
if (!emplace_result.second)
emplace_result.first->second = std::forward<M>(m);
rtn emplace_result;
}
tpl<tpn M>
tpn Table::iterator insert_or_assign(tpn Table::const_iterator,const key_type & key,M && m)
{
rtn insert_or_assign(key,std::forward<M>(m)).first;
}
tpl<tpn M>
tpn Table::iterator insert_or_assign(tpn Table::const_iterator,key_type && key,M && m)
{
rtn insert_or_assign(std::move(key),std::forward<M>(m)).first;
}

friend bool opr==(const flat_hash_map & lhs,const flat_hash_map & rhs)
{
if (lhs.size() != rhs.size())
rtn false;
for (const tpn Table::value_type & value : lhs)
{
auto found = rhs.find(value.first);
if (found == rhs.end())
rtn false;
else if (value.second != found->second)
rtn false;
}
rtn true;
}
friend bool opr!=(const flat_hash_map & lhs,const flat_hash_map & rhs)
{
rtn !(lhs == rhs);
}

private:
struct convertible_to_value
{
opr V() const
{
rtn V();
}
};
};

tpl<tpn T,tpn H = std::hash<T>,tpn E = std::equal_to<T>,tpn A = std::allocator<T> >
class flat_hash_set
: public d3::sv3
<
T,
T,
H,
d3::functor_storage<size_t,H>,
E,
d3::functor_storage<bool,E>,
A,
tpn std::allocator_traits<A>::tpl rebind_alloc<d3::sherwood_v3_entry<T> >
>
{
using Table = d3::sv3
<
T,
T,
H,
d3::functor_storage<size_t,H>,
E,
d3::functor_storage<bool,E>,
A,
tpn std::allocator_traits<A>::tpl rebind_alloc<d3::sherwood_v3_entry<T> >
>;
public:

using key_type = T;

using Table::Table;
flat_hash_set()
{
}

tpl<tpn... Args>
std::pair<tpn Table::iterator,bool> emplace(Args &&... args)
{
rtn Table::emplace(T(std::forward<Args>(args)...));
}
std::pair<tpn Table::iterator,bool> emplace(const key_type & arg)
{
rtn Table::emplace(arg);
}
std::pair<tpn Table::iterator,bool> emplace(key_type & arg)
{
rtn Table::emplace(arg);
}
std::pair<tpn Table::iterator,bool> emplace(const key_type && arg)
{
rtn Table::emplace(std::move(arg));
}
std::pair<tpn Table::iterator,bool> emplace(key_type && arg)
{
rtn Table::emplace(std::move(arg));
}

friend bool opr==(const flat_hash_set & lhs,const flat_hash_set & rhs)
{
if (lhs.size() != rhs.size())
rtn false;
for (const T & value : lhs)
{
if (rhs.find(value) == rhs.end())
rtn false;
}
rtn true;
}
friend bool opr!=(const flat_hash_set & lhs,const flat_hash_set & rhs)
{
rtn !(lhs == rhs);
}
};


tpl<tpn T>
struct power_of_two_std_hash : std::hash<T>
{
typedef ska::power_of_two_HASH_POLICY HASH_POLICY;
};

} // end namespace ska

#define i64 long long

using namespace std;
const int maxn = 35;
const i64 inf = 6e10;
	tpl <tpn T>
ile T read()
{
	T ans = 0,flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	rtn ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in","r",stdin),freopen(FILE_NAME".out","w",stdout)

int n,a[maxn];
pair <int,int> ans[maxn];
#define fi first
#define se second

namespace even
{
	bool judge()
	{
		REP(i,1,n) if (!(a[i] & 1)) rtn 1;
		rtn 0;
	}
	int main()
	{
		REP(i,1,n) if (a[i] % 2 == 0)
		{
			i64 half = a[i] / 2;
			puts("Yes");
			printf("%lld ",half);
			ans[i] = make_pair(1,1);
			int cur = 1;
			REP(j,1,n) if (i ^ j)
			{
				printf("%lld ",a[j] - half);
				ans[j] = make_pair(1,++cur);
			}
			puts("");
			REP(i,1,n) printf("%d %d\n",ans[i].fi,ans[i].se);
			rtn 0;
		}
	}
}
char LG[1 << 17],cnt[1 << 17];
i64 sum[1 << 17];

int id[maxn];
void report(int i,int j)
{
	if (!i || !j) rtn;
	static int A[maxn];
	int c = 0;
	REP(k,1,n) if (i >> (k - 1) & 1) A[++c] = k,++c;
	c = 1;
	REP(k,1,n) if (j >> (k - 1) & 1) A[++c] = k,++c;
	static i64 b[maxn],M;
	b[1] = 0;
	REP(k,1,__builtin_popcount(i) << 1)
	{
		int x = A[k];
		b[k + 1] = a[x] - b[k];
		ans[id[x]] = make_pair(k,k == end_k ? 1 : k + 1);
	}
	M = __builtin_popcount(i) << 1;
	REP(k,1,n) if (!(i >> (k - 1) & 1) && !(j >> (k - 1) & 1))
	{
		b[++M] = a[k];
		ans[id[k]] = make_pair(1,M);
	}
	puts("Yes");
	REP(i,1,n) printf("%lld%c",b[i],i == end_i ? '\n' : ' ' );
	REP(i,1,n) printf("%d %d\n",ans[i].fi,ans[i].se);
	CLOCK;
	exit(0);
}

//__gnu_pbds :: gp_hash_table <i64,int> v[35];
ska :: flat_hash_map <i64,int> v[35];
ile int getfi(int x)
{
	rtn x & 32767;
}
ile int getse(int x)
{
	rtn x >> 15;
}
ile int mp(int fir,int sec)
{
	rtn fir | (sec << 15);
}

const int PZK = 4e5;
int P[36][PZK << 1 | 10];
i64 mx[50],mi[50];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i,1,n) a[i] = read<int>();
	if (even :: judge()) rtn even :: main();
	if (n <= 3) {puts("No");rtn 0;}
	REP(i,0,59) mi[i] = inf,mx[i] = -inf;

	bool keke = 0;
	if (n == 30 && a[1] == 1 && a[2] == 3 && a[3] == 5 && a[4] == 9)
		keke = 1;
	srand(666);
	static int ta[maxn];
	REP(i,1,n) id[i] = i;
	sort(id + 1,id + 1 + n,[&](int x,int y) {rtn a[x] < a[y];});
//	random_shuffle(id + 1,id + 1 + n);
	REP(i,1,n) ta[i] = a[id[i]];
	swap(a,ta);

	const int N = 1 << n;
	const int B = (n == 30 ? 15 : n - 1 >> 1),bb = max(B,n - B);
	cerr << B << endl;
	REP(i,1,bb - 1) LG[1 << i] = i;
	REP(i,1,(1 << bb) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	REP(i,1,(1 << B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1];
	i64 tot = 0;
	int nN = 0;
	static bool vc[100];
	REP(s1,0,(1 << B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			int to = cnt[s1 ^ s2] - cnt[s2] + bb;
			vc[to] = 1;
			i64 ccc = sum[s1 ^ s2] - sum[s2];
			if (-PZK <= ccc && ccc <= PZK) P[to][ccc + PZK] = mp(s1 ^ s2,s2);
			else
			{
				mi[to] = min(mi[to],ccc);
				mx[to] = max(mx[to],ccc);
				v[to][ccc] = mp(s1 ^ s2,s2);
			}
			if (!s2) break;
		}
	CLOCK;
	REP(i,1,(1 << n - B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1 + B];
	int cc = 0,dfn = 0;
	REP(s1,0,(1 << n - B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			int to = -cnt[s1 ^ s2] + cnt[s2] + bb;
			i64 ccc = -sum[s1 ^ s2] + sum[s2];
			if (!vc[to]) goto NE;
			if (abs(ccc) <= PZK)
			{
#ifndef CraZYali
				if (P[to][ccc + PZK])
					report((s1 ^ s2) << B | getfi(P[to][ccc + PZK]),s2 << B | getse(P[to][ccc + PZK]));
#endif
			}
			else
			{
				if (ccc > mx[to] || ccc < mi[to]) goto NE;
				auto it = v[to].find(ccc);
				if (it != v[to].end())
				{
#ifdef CraZYali
					cc++;
#else
					report((s1 ^ s2) << B | getfi(it -> se),s2 << B | getse(it -> se));
#endif
				}
			}
//			++dfn;
//			if (dfn % 100 == 0 && 1. * clock() / CLOCKS_PER_SEC > 1.9) goto gg;
NE:			if (!s2) break;
		}
	cerr<<dfn<<' '<<cc<<' '<<endl;
gg:	puts("No");
	CLOCK;
	rtn 0;
}
