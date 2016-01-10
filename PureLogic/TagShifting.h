#pragma once

#include <cstdint>

#pragma pack(push, 1)

struct packedbyte {
	bool b0 : 1;
	bool b1 : 1;
	bool b2 : 1;
	bool b3 : 1;
	bool b4 : 1;
	bool b5 : 1;
	bool b6 : 1;
	bool b7 : 1;
} ;

#pragma pack(pop)
typedef packedbyte Bits;

template <typename T>
class TagShifting {
	
	public:
		static char bitArray[105];

		typedef union {
			T valueType;
			bool valueBool;
			short valueShort;
			int valueInt;
			float valueFloat;
			char valueChar;
			Bits valueByte[4];
		} tData;


		static enum TagType {
			UNKNOWN = 99,
			Integer = 0,
			Bool = 1

		};

		void setAdress(int newAdress) {
			if (newAdress < 100) {
				bitPlace = newAdress;

				value = reinterpret_cast<tData*>(bitArray + newAdress);
			}
		};


		void setBit(int,bool);
		bool getBit(int);


		TagShifting(){
			if (strcmp(typeid(T).name(), "int") == 0) {
				type = TagType::Integer;
			} else if (strcmp(typeid(T).name(), "bool") == 1){
				for(int i = 0; i < 100; i++){
					bitArray[i] = 0;
				}
			}
		};

		~TagShifting(){};

		TagShifting<T>& operator=(const TagShifting<T>&);
		T& operator=(const T&);
		bool operator==(const T&);
		bool operator!=(const T& v){
			return !operator==(v);
		};

		tData * value;

		operator T const & () const {
			return value->valueType;
		}

	private:
		int bitPlace = 0;
		int type = TagType::UNKNOWN;
};

using namespace System::Windows::Forms;

template<typename T> char TagShifting<T>::bitArray[105];


template<typename T> TagShifting<T>& TagShifting<T>::operator=(const TagShifting<T>& v) {
	
	if(v.type == this->type){
		this->value->valueType = v.value->valueType;
	}
	return *this;
}


template<typename T> T& TagShifting<T>::operator=(const T& v) {
	this->value->valueType = v;
	return this->value->valueType;
}


template<typename T> bool TagShifting<T>::operator==(const T& v) {
	return this->value.valueType == v;
}


template<typename T> bool TagShifting<T>::getBit(int whatbit) {
	int bitplace = whatbit & 7;
	int byteplace = whatbit / 8;
	switch (bitplace) {
		case 0:
			return value->valueByte[byteplace].b0;
			break;
		case 1:
			return value->valueByte[byteplace].b1;
			break;
		case 2:
			return value->valueByte[byteplace].b2;
			break;
		case 3:
			return value->valueByte[byteplace].b3;
			break;
		case 4:
			return value->valueByte[byteplace].b4;
			break;
		case 5:
			return value->valueByte[byteplace].b5;
			break;
		case 6:
			return value->valueByte[byteplace].b6;
			break;
		case 7:
			return value->valueByte[byteplace].b7;
			break;
	}

	return false;
}

template<typename T> void TagShifting<T>::setBit(int whatbit, bool state) {
	int bitplace = whatbit & 7;
	int byteplace = whatbit / 8;
	switch (bitplace) {
		case 0:
			value->valueByte[byteplace].b0 = state;
			break;
		case 1:
			value->valueByte[byteplace].b1 = state;
			break;
		case 2:
			value->valueByte[byteplace].b2 = state;
			break;
		case 3:
			value->valueByte[byteplace].b3 = state;
			break;
		case 4:
			value->valueByte[byteplace].b4 = state;
			break;
		case 5:
			value->valueByte[byteplace].b5 = state;
			break;
		case 6:
			value->valueByte[byteplace].b6 = state;
			break;
		case 7:
			value->valueByte[byteplace].b7 = state;
			break;
	}

}
