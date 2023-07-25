#include "MyString.h"

namespace assignment1
{
	MyString::MyString(const char* s)
		: mLength(getStrLen(s))
	{
		mString = new char[mLength + 1];
		strCopy(mString, s);
	}

	MyString::MyString(const MyString& other)
		: mLength(other.mLength)
	{
		mString = new char[mLength + 1];
		strCopy(mString, other.mString);
	}

	MyString::~MyString()
	{
		delete[] mString;
	}

	unsigned int MyString::GetLength() const
	{
		return mLength;
	}

	const char* MyString::GetCString() const
	{
		return mString;
	}

	void MyString::Append(const char* s)
	{
		unsigned int newStrLen = getAppendStrLen(s);
		if (mLength + 1 == newStrLen)
		{
			return;
		}

		char* newStr = new char[newStrLen];
		strCopy(newStr, mString);
		strCopy(newStr + mLength, s);

		delete[] mString;

		mString = newStr;
		mLength = newStrLen - 1;
	}

	MyString MyString::operator+(const MyString& other) const
	{
		MyString newString(this->mString);
		newString.Append(other.mString);

		return newString;
	}

	int MyString::IndexOf(const char* s)
	{
		if (s == nullptr)
		{
			return -1;
		}

		const char* mStrPtr = mString;
		const char* cmpStrPtr = s;
		unsigned int cmpStrLen = getStrLen(s);

		if (cmpStrLen == 0)
		{
			return 0;
		}

		while (*mStrPtr != '\0')
		{
			if (*mStrPtr++ != *cmpStrPtr++)
			{
				mStrPtr -= cmpStrPtr - s - 1;
				cmpStrPtr = s;
			}
			else if (*cmpStrPtr == '\0')
			{
				return mStrPtr - mString - cmpStrLen;
			}
		}

		return -1;
	}

	int MyString::LastIndexOf(const char* s)
	{
		if (s == nullptr)
		{
			return -1;
		}

		unsigned int cmpStrLen = getStrLen(s);
		const char* cmpStrPtr = s + cmpStrLen - 1;

		unsigned int loopCount = mLength;
		const char* mStrPtr = mString + mLength - 1;

		if (cmpStrLen == 0)
		{
			return mLength;
		}

		while (loopCount-- > 0)
		{
			if (*mStrPtr-- == *cmpStrPtr)
			{
				if (cmpStrPtr == s)
				{
					return mStrPtr - mString + 1;
				}
				--cmpStrPtr;
			}
			else
			{
				mStrPtr += cmpStrLen - (cmpStrPtr - s) - 1;
				cmpStrPtr = s + cmpStrLen - 1;
			}
		}

		return -1;
	}

	void MyString::Interleave(const char* s)
	{
		if (s == nullptr)
		{
			return;
		}
		else if (getStrLen(s) == 0)
		{
			return;
		}

		unsigned int newStrLen = getAppendStrLen(s);
		char* newStr = new char[newStrLen];
		char* newStrPtr = newStr;

		const char* mStrPtr = mString;
		const char* strPtr = s;

		while (true)
		{
			bool bInserted = false;

			if (*mStrPtr != '\0')
			{
				*newStrPtr++ = *mStrPtr++;
				bInserted = true;
			}
			if (*strPtr != '\0')
			{
				*newStrPtr++ = *strPtr++;
				bInserted = true;
			}

			if (bInserted == false)
			{
				break;
			}
		}
		*newStrPtr = '\0';

		delete[] mString;
		mString = newStr;
		mLength = newStrLen - 1;
	}

	bool MyString::RemoveAt(unsigned int i)
	{
		if (mLength > i)
		{
			char* mStrPtr = mString + i;

			while (*mStrPtr != '\0')
			{
				*mStrPtr++ = *(mStrPtr + 1);
			}
			--mLength;
			return true;
		}

		return false;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		PadLeft(totalLength, ' ');
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		if (totalLength > mLength)
		{
			char* newStr = new char[totalLength + 1];
			char* newStrPtr = newStr;

			unsigned int loopCount = totalLength - mLength;
			while (loopCount-- > 0)
			{
				*newStrPtr++ = c;
			}

			strCopy(newStrPtr, mString);

			delete[] mString;
			mString = newStr;
			mLength = totalLength;
		}
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		PadRight(totalLength, ' ');
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		if (totalLength > mLength)
		{
			char* newStr = new char[totalLength + 1];
			char* newStrPtr = newStr;

			strCopy(newStrPtr, mString);

			newStrPtr += mLength;
			unsigned int loopCount = totalLength - mLength;
			while (loopCount-- > 0)
			{
				*newStrPtr++ = c;
			}
			*newStrPtr = '\0';

			delete[] mString;
			mString = newStr;
			mLength = totalLength;
		}
	}

	void MyString::Reverse()
	{
		if (mLength == 0)
		{
			return;
		}

		char* lhsStrPtr = mString;
		char* rhsStrPtr = mString + mLength - 1;

		while (lhsStrPtr < rhsStrPtr)
		{
			*lhsStrPtr ^= *rhsStrPtr;
			*rhsStrPtr ^= *lhsStrPtr;
			*lhsStrPtr ^= *rhsStrPtr;

			++lhsStrPtr;
			--rhsStrPtr;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		const char* mStrPtr = mString;
		const char* cmpStrPtr = rhs.mString;

		while (*mStrPtr == *cmpStrPtr && *mStrPtr != '\0')
		{
			++mStrPtr;
			++cmpStrPtr;
		}

		return *mStrPtr == *cmpStrPtr;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		if (mString == rhs.mString)
		{
			return *this;
		}

		delete[] mString;
		mLength = rhs.mLength;

		mString = new char[mLength + 1];
		strCopy(mString, rhs.mString);

		return *this;
	}

	void MyString::ToLower()
	{
		char* mStrPtr = mString;

		const unsigned int UPPER_ALPHABET_BEGIN = 65;
		const unsigned int UPPER_ALPHABET_END = 90;

		while (*mStrPtr != '\0')
		{
			if (*mStrPtr >= UPPER_ALPHABET_BEGIN && *mStrPtr <= UPPER_ALPHABET_END)
			{
				*mStrPtr += 32;
			}
			++mStrPtr;
		}
	}

	void MyString::ToUpper()
	{
		char* mStrPtr = mString;

		const unsigned int LOWER_ALPHABET_BEGIN = 97;
		const unsigned int LOWER_ALPHABET_END = 122;

		while (*mStrPtr != '\0')
		{
			if (*mStrPtr >= LOWER_ALPHABET_BEGIN && *mStrPtr <= LOWER_ALPHABET_END)
			{
				*mStrPtr -= 32;
			}
			++mStrPtr;
		}
	}

	unsigned int MyString::getStrLen(const char* str) const
	{
		if (str == nullptr)
		{
			return 0;
		}

		const char* strPtr = str;
		while (*strPtr++ != '\0')
		{
		}

		return strPtr - str - 1;
	}

	unsigned int MyString::getAppendStrLen(const char* appendStr) const
	{
		return mLength + getStrLen(appendStr) + 1;
	}

	void MyString::strCopy(char* dest, const char* src) const
	{
		if (src == nullptr)
		{
			*dest = '\0';
			return;
		}

		char* destPtr = dest;
		const char* srcPtr = src;

		while (*srcPtr != '\0')
		{
			*destPtr++ = *srcPtr++;
		}
		*destPtr = '\0';
	}
}