
#include <vector>
#include <functional>

template<class K, class V>
class MapEntry
{
    K key;
    V value;
public:
    MapEntry(K k, V v) : key(k), value(v) {}
    K getKey() const { return key; }
    V getValue() const { return value; }
    void setValue(V v) { value = v; }
};

template<class K, class V>
class HashTable
{
protected:
    std::hash<K> hashFunc;
public:
    HashTable() {}
    virtual V get(K key) const = 0;
    virtual V put(K key, V newValue) const = 0;
    bool exists(K key);
};

template<class K, class V>
bool HashTable<K, V>::exists(K key)
{
    V v = get(key);
    if(v == NULL) return false;
    else return true;
}

template<class K, class V>
class CollisionChainingHashTable : public HashTable<K, V>
{
    const int INITIAL_SIZE = 17;
    std::vector<std::vector<MapEntry<K, V> > * > * values;
public:
    CollisionChainingHashTable();
    V get(K key) const;
    V put(K key, V newValue) const;
};

template<class K, class V>
CollisionChainingHashTable<K, V>::CollisionChainingHashTable()
{
    values = new std::vector<std::vector<MapEntry<K, V> > * >;
    values->resize(INITIAL_SIZE);
    for(typename std::vector<std::vector<MapEntry<K, V> > * >::iterator it = values->begin(); it != values->end(); ++it)
    {
        (*values)[it - values->begin()] = new std::vector<MapEntry<K, V> >;
    }
}

template<class K, class V>
V CollisionChainingHashTable<K, V>::get(K key) const
{
    size_t hashVal = HashTable<K, V>::hashFunc(key);
    int bucket = hashVal % values->size();
    std::vector<MapEntry<K, V> > * bucketVals = values->at(bucket);
    for(typename std::vector<MapEntry<K, V> >::iterator it = bucketVals->begin(); it != bucketVals->end(); ++it)
    {
        MapEntry<K, V> currentMapEntry = *it;
        if(currentMapEntry.getKey() == key)
        {
            return currentMapEntry.getValue();
        }
    }
    return NULL;
}

template<class K, class V>
V CollisionChainingHashTable<K, V>::put(K key, V newValue) const
{
    size_t hashVal = HashTable<K, V>::hashFunc(key);
    int bucket = hashVal % values->size();
    std::vector<MapEntry<K, V> > * bucketVals = values->at(bucket);
    for(typename std::vector<MapEntry<K, V> >::iterator it = bucketVals->begin(); it != bucketVals->end(); ++it)
    {
        MapEntry<K, V> currentMapEntry = *it;
        if(currentMapEntry.getKey() == key)
        {
            V oldValue = currentMapEntry.getValue();
            currentMapEntry.setValue(newValue);
            (*bucketVals)[it - bucketVals->begin()] = currentMapEntry;
            return oldValue;
        }
    }
    MapEntry<K, V> me(key, newValue);
    bucketVals->push_back(me);
    return NULL;
}

