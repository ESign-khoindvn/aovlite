
#include "Vector2.h"
#include "Vector3.h"
#include "VInt3.h"
#define LOG_TAG  "PusexPrivate.xyz"
#pragma once

#include <stdio.h>
#include <string>
#include <inttypes.h>
#include <codecvt>
#include <locale>
#include <dlfcn.h>

using namespace std;

typedef void(*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeData
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
};

struct Il2CppType
{
    void* data;
    unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject
{
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData
{
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppType* type;
    Il2CppClass* klass;
};
typedef struct _monoString {
    void* klass;
    void* monitor;
    int length;
    char chars[1];
    int getLength() {
        return length;
    }
    char* getChars() {
        return chars;
    }
} monoString;

typedef struct _StringUnity
{
    void* klass;
    void* monitor;
    int length;
    char chars[1];
    int getLength()
    {
      return length;
    }
    char* getChars()
    {
        return chars;
    }
} StringUnity;
struct Il2CppClass_1
{
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType* byval_arg;
    Il2CppType* this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    void* typeDefinition;
    void* interopData;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    void* interfaceOffsets;
};

struct Il2CppClass_2
{
    Il2CppClass** typeHierarchy;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    uint64_t cctor_thread;
    int32_t genericContainerIndex;
    int32_t customAttributeIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClass
{
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};

typedef int32_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    void* invoker_method;
    const char* name;
    Il2CppClass *declaring_type;
    const Il2CppType *return_type;
    const void* parameters;
    union
    {
        const Il2CppRGCTXData* rgctx_data;
        const void* methodDefinition;
    };
    union
    {
        const void* genericMethod;
        const void* genericContainer;
    };
    int32_t customAttributeIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};
template <typename T>
struct monoArray {
    void* klass;
    void* monitor;
    void* bounds;
    int max_length;
    void* vector[1];
    int getLength() {
        return max_length;
    }
    T getPointer() {
        return (T)vector;
    }
};
template<typename T> struct Il2CppArray {
    Il2CppClass *klass;
    void *monitor;
    void *bounds;
    int max_length;
    T m_Items[65535];

    int getLength() {
        return max_length;
    }

    T *getPointer() {
        return (T *)m_Items;
    }

    T &operator[](int i) {
        return m_Items[i];
    }

    T &operator[](int i) const {
        return m_Items[i];
    }

    std::vector<T> toCPPlist() {
        std::vector<T> ret;
        ret.reserve(max_length);

        for (int i = 0; i < max_length; i++) {
            ret.push_back(m_Items[i]);
        }

        return ret;
    }
};

template<typename T>
using Array = Il2CppArray<T>;

template<typename T> struct Il2CppList {
    Il2CppClass *klass;
    void *unk1;
    Il2CppArray<T> *items;
    int size;
    int version;

    T *getItems() {
        return items->getPointer();
    }

    int getSize() {
        return size;
    }

    int getVersion() {
        return version;
    }

    T &operator[](int i) {
        return items->m_Items[i];
    }

    T &operator[](int i) const {
        return items->m_Items[i];
    }

      std::vector<T> toCPPlist() {
        std::vector<T> ret;
        ret.reserve(size); // Reserve space in the vector for the items.

        for (int i = 0; i < size; i++) {
            ret.push_back(items->m_Items[i]);
        }

        return ret;
    }
};

template<typename T>
using List = Il2CppList<T>;

template<typename K, typename V> struct Il2CppDictionary {
    Il2CppClass *klass;
    void *unk1;
    Il2CppArray<int **> *table;
    Il2CppArray<void **> *linkSlots;
    Il2CppArray<K> *keys;
    Il2CppArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;

    K *getKeys() {
        return keys->getPointer();
    }

    V *getValues() {
        return values->getPointer();
    }

    int getNumKeys() {
        return keys->getLength();
    }

    int getNumValues() {
        return values->getLength();
    }

    int getSize() {
        return size;
    }
};

template<typename K, typename V>
using monoDictionary = Il2CppDictionary<K, V>;

template<typename TKey, typename TValue> 
struct Dictionary 
{
    struct KeysCollection;
    struct ValueCollection;

    struct Entry
    {
        int hashCode; 
        int next;
        TKey key;
        TValue value;
    };

    void *kass;
    void *monitor;
    Array<int> *buckets;
    Array<Entry> *entries;
    int count;
    int version;
    int freeList;
    int freeCount;
    void* comparer;
    KeysCollection *keys;
    ValueCollection *values;
    void *_syncRoot;

    void* get_Comparer()
    {
        return comparer;
    }

    int get_Count()
    {
        return count;
    }

    KeysCollection get_Keys()
    {
        if(!keys) keys = new KeysCollection(this);
        return (*keys);
    }

    ValueCollection get_Values()
    {
        if(!values) values = new ValueCollection(this);
        return (*values);
    }

    TValue operator [] (TKey key) 
    {
        int i = FindEntry(key);
        if (i >= 0) return (*entries)[i].value;
        return TValue();
    }

    const TValue operator [] (TKey key) const 
    {
        int i = FindEntry(key);
        if (i >= 0) return (*entries)[i].value;
        return TValue();
    }
    
    int FindEntry(TKey key) 
    {
        for (int i = 0; i < count; i++)
        {
            if((*entries)[i].key == key) return i;
        }
        return -1;
    }
    
    bool ContainsKey(TKey key) 
    {
        return FindEntry(key) >= 0;
    }
    
    bool ContainsValue(TValue value) 
    {
        for (int i = 0; i < count; i++)
        {
            if((*entries)[i].hashCode >= 0 && 
                    (*entries)[i].value == value) return true;
        }
        return false;
    }

    bool TryGetValue(TKey key, TValue *value) 
    {
        int i = FindEntry(key);
        if (i >= 0) {
            *value = (*entries)[i].value;
            return true;
        }
        *value = TValue();
        return false;
    }

    TValue GetValueOrDefault(TKey key) 
    {
        int i = FindEntry(key);
        if (i >= 0) {
            return (*entries)[i].value;
        }
        return TValue();
    }

    struct KeysCollection 
    {
        Dictionary *dictionary;

        KeysCollection(Dictionary *dictionary)
        {
            this->dictionary = dictionary;
        }

        TKey operator [] (int i) 
        {
            auto entries = dictionary->entries;
            if(!entries) return TKey();
            return (*entries)[i].key;
        }

        const TKey operator [] (int i) const 
        {
            auto entries = dictionary->entries;
            if(!entries) return TKey();
            return (*entries)[i].key;
        }

        int get_Count()
        {
            return dictionary->get_Count();
        }
    };

    struct ValueCollection 
    {
        Dictionary *dictionary;

        ValueCollection(Dictionary *dictionary)
        {
            this->dictionary = dictionary;
        }

        TValue operator [] (int i) 
        {
            auto entries = dictionary->entries;
            if(!entries) return TValue();
            return (*entries)[i].value;
        }

        const TValue operator [] (int i) const 
        {
            auto entries = dictionary->entries;
            if(!entries) return TValue();
            return (*entries)[i].value;
        }

        int get_Count()
        {
            return dictionary->get_Count();
        }
    };
};