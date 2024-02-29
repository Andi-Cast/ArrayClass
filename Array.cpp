#include "Array.h"
#include <stdexcept> //used for std::out_of_range

Array::Array (void)
: data_ (new char[0]),
  cur_size_ (0),
  max_size_ (0)
{
	
}

Array::Array (size_t length)
: data_ (new char[length]),
  cur_size_ (length), 
  max_size_ (length)
{
	
}

Array::Array (size_t length, char fill)
: data_(new char[length]),
  cur_size_ (length), 
  max_size_(length)
{	
	for(int i = 0; i < length; i++) {
		data_[i]= fill;
	}
}


Array::Array (const Array & array)
: data_ (new char[array.max_size_]),
  cur_size_ (array.cur_size_), 
  max_size_ (array.max_size_)
{
    for (int i = 0; i < max_size_; i++) {
	    data_[i]= array.data_[i];
    }
}

Array::~Array (void)
{
	delete [] data_;
}

const Array & Array::operator = (const Array & rhs)
{
    if (this != &rhs) {
    	if (rhs.max_size_ > max_size_) {
		delete [] data_;

		char* copyData_ = new char[rhs.max_size_];

		for (int i = 0; i < rhs.max_size_; i++) {
			copyData_[i] = rhs.data_[i];
		}

		data_ = copyData_;
		cur_size_ = rhs.cur_size_;
		max_size_ = rhs.max_size_;
   	    }
        else {
            for (int j = 0; j < rhs.max_size_; j++) {
                data_[j] = rhs.data_[j];
            }
            cur_size_ = rhs.cur_size_;
        }
    }	
	return *this;
}

char & Array::operator [] (size_t index)
{
	if (index < 0 || index >= cur_size_) {
		throw std::out_of_range("Not in range");
	}
	return data_[index];
}

const char & Array::operator [] (size_t index) const
{
	if (index < 0 || index >= cur_size_) {
		throw std::out_of_range("Not in range");
	}
	return data_[index];
}

char Array::get (size_t index) const
{
	if (index < 0 || index >= cur_size_) {
		throw std::out_of_range("Not in range");
	}
	return data_[index];
}

void Array::set (size_t index, char value)
{
	if (index < 0 || index >= cur_size_) {
		throw std::out_of_range("Not in range");
	}
	else {
		data_[index] = value;
	}
}

void Array::resize (size_t new_size)
{
	if (new_size <=  max_size_) {
            cur_size_ = new_size;
        }
	else if (new_size > max_size_) {
		char * newBiggerData_ = new char[new_size];

		for (int i = 0; i < cur_size_; i++) {
			newBiggerData_[i] = data_[i];
		}
		
		delete [] data_;
		data_ = newBiggerData_;
		cur_size_ = new_size;
		max_size_ = new_size;
	}
}

int Array::find (char ch) const
{
	for (int i = 0; i < cur_size_; i++) {
		if (data_[i] == ch) {
			return i;
		}
	}
	return -1;
}

int Array::find (char ch, size_t start) const
{
	if (start < 0 || start >= cur_size_) {
                throw std::out_of_range("Not in range");
        }
      
        else {
                for (int i = start; i < cur_size_; i++) {
             		if (data_[i] == ch) {
                        	return i;
                	}
       		}
        	return -1;
        }
}

bool Array::operator == (const Array & rhs) const
{
	if (this != &rhs) {
		if (cur_size_ != rhs.cur_size_ || max_size_ != rhs.max_size_) {
			return false;
		}	
		else {
			for (int i = 0; i < cur_size_; i++) {
				if(data_[i] != rhs.data_[i]) {
					return false;
				}
			}
			return true;
		}
	}

	return true;
}

bool Array::operator != (const Array & rhs) const
{
	return !(*this == rhs);
}

void Array::fill (char ch)
{
	for (int i = 0; i < cur_size_; i++) {
	       data_[i] = ch;
	}	       
}

void Array::shrink (void)
{
	if (max_size_ > cur_size_) {
		char * shrinkData_ = new char[cur_size_];
	
		for (int i = 0; i < cur_size_; i ++) {
			shrinkData_[i] = data_[i];
		}
		
		delete [] data_;
		data_ = shrinkData_;
		max_size_ = cur_size_;
	}	
}

void Array::reverse (void)
{
	char * reverseData_ = new char[max_size_];
  	int i = max_size_ - 1;
	
 	 for (int j = 0; j < max_size_; j++) {
		reverseData_[j] = data_[i];
		i--;
	 }

  	delete [] data_;
  	data_ = reverseData_;

}

Array Array::slice (size_t begin) const
{
	Array* tempArray = new Array(*this);
	
	char * sliceData_ = new char[max_size_ - begin];

      	for (int i = begin; i < max_size_; i++) {
		sliceData_[i] = data_[i];		
	}	

	delete [] tempArray->data_; 
	tempArray->data_ = sliceData_;

	return *tempArray;
      		
}

Array Array::slice (size_t begin, size_t end) const
{
 	Array* tempArray = new Array(*this);

	char * sliceData_ = new char[end - begin];

	for (int i = begin; i < end; i++) {
		sliceData_[i] = data_[i];
	}

	delete [] tempArray->data_;
	tempArray->data_ = sliceData_;

	return *tempArray;
}
